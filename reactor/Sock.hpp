#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>

#include "Log.hpp"
#include "Err.hpp"
#include "Common.hpp"

static const int backlog = 32;

class Sock
{
public:
    Sock() : _listensock(defaultfd)
    {}

    void Socket()
    {
        _listensock = socket(AF_INET, SOCK_STREAM, 0);
        if (_listensock == defaultfd)
        {
            logMessage(ERROR, "create socket fail");
            exit(SOCKET_ERR);
        }
        logMessage(NORMAL, "create socket success: %d", _listensock);

        // 防止服务器异常中断进入time wait状态
        int opt = 1;
        setsockopt(_listensock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    }

    void Bind(uint16_t port)
    {
        struct sockaddr_in local;
        memset(&local, 0, sizeof(local));
        local.sin_family = AF_INET;
        local.sin_addr.s_addr = INADDR_ANY;
        local.sin_port = htons(port);
        int n = bind(_listensock, (struct sockaddr*)&local, sizeof(local));
        if (n == -1)
        {
            logMessage(ERROR, "bind socket fail");
            exit(BIND_ERR);
        }
        logMessage(NORMAL, "bind socket success");
    }

    void Listen()
    {
        int n = listen(_listensock,backlog);
        if (n == -1)
        {
            logMessage(ERROR, "listen socket fail");
            exit(LISTEN_ERR);
        }
        logMessage(NORMAL, "listen success");
    }

    int Accept(std::string *clientip, uint16_t *clientport, int *err)
    {
        struct sockaddr_in peer;
        socklen_t len = sizeof(peer);
        int sock = accept(_listensock, (struct sockaddr*)&peer, &len);
        *err = errno;
        if (sock == -1)
        {
            // logMessage(WARNING, "accept fail");
        }
        else
        {
            *clientip = inet_ntoa(peer.sin_addr);
            *clientport = ntohs(peer.sin_port);
            logMessage(NORMAL, "accept sock: %d", sock);
        }

        return sock;
    }

    int Fd()
    {
        return _listensock;
    }

    ~Sock()
    {
        if (_listensock != defaultfd) close(_listensock);
    }

private:
    int _listensock;
};