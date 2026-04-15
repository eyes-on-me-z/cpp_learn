#pragma once

#include <fcntl.h>

class Util
{
public:
    static bool SetNonBlock(int fd) // 把一个文件描述符（socket）设置为非阻塞模式
    {
        int flag = fcntl(fd, F_GETFL);
        if (flag == -1)
            return false;
            
        // 在原有基础上加 NONBLOCK
        if (fcntl(fd, F_SETFL, flag | O_NONBLOCK) == -1)
            return false;

        return true;
    }
};