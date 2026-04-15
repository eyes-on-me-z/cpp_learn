#pragma once

#include <sys/epoll.h>
#include <cstring>
#include <unistd.h>

#include "Log.hpp"
#include "Err.hpp"
#include "Common.hpp"

static const int size = 128;

class Epoller
{
public:
    Epoller() : _epfd(defaultfd)
    {}

    void Create()
    {
        _epfd = epoll_create(size);
        if (_epfd == -1)
        {
            logMessage(ERROR, "create epoll fail: %s", strerror(errno));
            exit(EPOLL_CREATE_ERR);
        }
        logMessage(NORMAL, "create epoll success: %d", _epfd);
    }

    bool AddEvent(int sock, uint32_t event) // 添加对套接字的关心
    {
        struct epoll_event ev;
        ev.data.fd = sock;
        ev.events = event;
        int n = epoll_ctl(_epfd, EPOLL_CTL_ADD, sock, &ev);
        
        return n == 0;
    }

    int Wait(struct epoll_event *revs, int num, int timeout)
    {
        return epoll_wait(_epfd, revs, num, timeout);
    }

    bool Control(uint32_t event, int sock, int action)  // 修改/删除对套接字的关心
    {
        int n = 0;
        if (action == EPOLL_CTL_MOD)
        {
            struct epoll_event ev;
            ev.data.fd = sock;
            ev.events = event;
            n = epoll_ctl(_epfd, EPOLL_CTL_MOD, sock, &ev);
        }
        else if (action == EPOLL_CTL_DEL)
        {
            n = epoll_ctl(_epfd, EPOLL_CTL_DEL, sock, nullptr);
        }
        else
        {
            n = -1;
        }

        return n == 0;
    }

    ~Epoller()
    {
        if (_epfd != defaultfd) close(_epfd);
    }
private:
    int _epfd;
};