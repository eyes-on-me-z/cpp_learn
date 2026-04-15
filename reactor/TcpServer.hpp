#pragma once

#include <string>
#include <unistd.h>
#include <functional>
#include <cassert>
#include <unordered_map>

#include "Sock.hpp"
#include "Epoller.hpp"
#include "Protocol.hpp"
#include "Util.hpp"
#include "Common.hpp"


static const int defaultnum = 64;
static const int defaultport = 8080;

class Connection;
class TcpServer;

using func_t = std::function<void(Connection*)>;

// 一个套接字创建一个Connection对象
class Connection
{
public:
    Connection(int sock = defaultfd) : _sock(sock)
    {}

    void Register(func_t recver, func_t sender, func_t excepter)
    {
        _recver = recver;
        _sender = sender;
        _excepter = excepter;
    }

    ~Connection()
    {
        if (_sock != defaultfd) close(_sock);
    }
public:
    int _sock;
    std::string _inbuffer;  // 每个套接字都有自己的输入输出缓冲区
    std::string _outbuffer;

    func_t _recver; // 每个套接字所绑定的方法，从外部传入
    func_t _sender;
    func_t _excepter;
};

class TcpServer
{
public:
    TcpServer(func_t service, uint16_t port = defaultport, int num = defaultnum)
            : _port(port), _num(num), _revs(nullptr), _service(service)
    {}

    void Init()
    {
        _sock.Socket();
        _sock.Bind(_port);
        _sock.Listen();
        _epoller.Create();
        AddConnection(_sock.Fd(), EPOLLET | EPOLLIN,
                    std::bind(&TcpServer::Accepter, this, std::placeholders::_1), nullptr, nullptr);
        
        _revs = new struct epoll_event[_num];
    }

    void Dispatcher()
    {
        int timeout = 1000;
        for(;;)
        {
            OneLoop(timeout);
        }
    }

    ~TcpServer()
    {
        if (_revs)
            delete[] _revs;
    }

private:
    // 创建Connection对象，并设置进epoll模型，对event事件进行关心
    void AddConnection(int sock, uint32_t events, func_t recver, func_t sender, func_t excepter)
    {
        if (events & EPOLLET)
            Util::SetNonBlock(sock);
        
        Connection *conn = new Connection(sock);
        conn->Register(recver, sender, excepter);
        _connections[sock] = conn;
        
        bool r = _epoller.AddEvent(sock, events);
        assert(r);
        (void)r;
    }

    // listen套接字的读方法
    void Accepter(Connection*)
    {
        for(;;)
        {
            std::string clientip;
            uint16_t clientport;
            int err;
            int sock = _sock.Accept(&clientip, &clientport, &err);
            if (sock != -1)
            {
                AddConnection(sock, EPOLLIN | EPOLLET,
                        std::bind(&TcpServer::Recver, this, std::placeholders::_1),
                        std::bind(&TcpServer::Sender, this, std::placeholders::_1),
                        std::bind(&TcpServer::Excepter, this, std::placeholders::_1));
            }
            else
            {
                if (err == EAGAIN || err == EWOULDBLOCK) // 当前没有数据可读
                    break;
                else if (err == EINTR)
                    continue;
                else
                    break;
            }
        }
    }

    void OneLoop(int timeout)
    {
        int n = _epoller.Wait(_revs, _num, timeout);
        for (int i = 0; i < n; ++i)
        {
            int sock = _revs[i].data.fd;
            uint32_t events = _revs[i].events;
            
            if (events & EPOLLERR)  // 发生了错误
            {
                events |= (EPOLLIN | EPOLLOUT);
            }
            if (events & EPOLLHUP)  // 对端断开连接（挂起）
            {
                events |= (EPOLLIN | EPOLLOUT);
            }

            if ((events & EPOLLIN) && IsConnectionExist(sock) && _connections[sock]->_recver)
            {
                _connections[sock]->_recver(_connections[sock]);
            }
            if ((events & EPOLLOUT) && IsConnectionExist(sock) && _connections[sock]->_sender)
            {
                _connections[sock]->_sender(_connections[sock]);
            }
        }
    }

    void Recver(Connection *conn)   // OK
    {
        char buffer[1024];
        while(true)
        {
            ssize_t n = recv(conn->_sock, buffer, sizeof(buffer) - 1, 0);
            if (n > 0)
            {
                buffer[n] = 0;
                conn->_inbuffer += buffer;
            }
            else if (n == 0)    // 对方关闭连接
            {
                if (conn->_excepter)
                {
                    conn->_excepter(conn);
                }
                return;
            }
            else
            {
                if (errno == EAGAIN || errno == EWOULDBLOCK) // 没数据
                    break;
                else if (errno == EINTR) // 被信号中断
                    continue;
                else
                {    
                    if (conn->_excepter)
                    {
                        conn->_excepter(conn);
                    }
                    return;
                }
            }
        }
        logMessage(DEBUG, conn->_inbuffer.c_str());
        _service(conn);
        // conn->_outbuffer = conn->_inbuffer;
        // conn->_sender(conn);
    }
    
    void Sender(Connection *conn)
    {
        // logMessage(DEBUG, "Sender in...");
        while(true)
        {
            ssize_t n = send(conn->_sock, conn->_outbuffer.c_str(), conn->_outbuffer.size(), 0);
            if (n > 0)
            {
                conn->_outbuffer.erase(0, n);
            }
            else
            {
                if (errno == EAGAIN || errno == EWOULDBLOCK)    //发送缓冲区满（非阻塞）
                    break;
                else if (errno == EINTR)    // 被信号打断
                    continue;
                else
                {
                    if (conn->_excepter)
                        conn->_excepter(conn);
                    return;
                }
            }
        }

        if (!conn->_outbuffer.empty())
        {
            EnableReadWrite(conn, true, true);
        }
        else
        {
            EnableReadWrite(conn, true, false);
        }
    }
    void Excepter(Connection *conn)
    {
        _epoller.Control(0, conn->_sock, EPOLL_CTL_DEL);
        _connections.erase(conn->_sock);
        delete conn;
        conn = nullptr;
    }
    
    bool IsConnectionExist(int sock)
    {
        auto it = _connections.find(sock);
        return it != _connections.end();
    }

    void EnableReadWrite(Connection *conn, bool readable, bool writeable)
    {
        uint32_t events = (readable ? EPOLLIN : 0) | (writeable ? EPOLLOUT : 0) | EPOLLET;
        _epoller.Control(events, conn->_sock, EPOLL_CTL_MOD);
    }

private:
    uint16_t _port;
    Sock _sock; // 管理listen套接字
    std::unordered_map<int, Connection*> _connections;  // 管理所有套接字
    Epoller _epoller;
    int _num;
    struct epoll_event *_revs;
    func_t _service;    // 怎么处理收到的数据
};