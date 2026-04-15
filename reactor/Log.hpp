#pragma once

#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdarg>

#define DEBUG 0
#define NORMAL 1
#define WARNING 2
#define ERROR 3
#define FATAL 4

static const char*to_leverstr(int level)
{
    switch(level)
    {
    case 0: return "DEBUG";
    case 1: return "NORMAL";
    case 2: return "WARNING";
    case 3: return "ERROR";
    case 4: return "FATAL";
    default : return nullptr;
    }
}

void logMessage(int level, const char *format, ...)
{
#define NUM 1024
    char prefix[NUM];
    time_t now = time(0);
    tm *t = localtime(&now);
    snprintf(prefix, NUM, "[%s][%d-%d-%d][pid: %d]", to_leverstr(level),
            t->tm_hour, t->tm_min, t->tm_sec, getpid());

    char logcontent[NUM];
    va_list arg;
    va_start(arg, format);
    vsnprintf(logcontent, NUM, format, arg);
    std::cout << prefix << logcontent << std::endl;
}