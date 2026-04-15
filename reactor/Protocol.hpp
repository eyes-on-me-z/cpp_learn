#pragma once

#include <string>
#include <cstring>
#include <jsoncpp/json/json.h>

#define SEP " "
#define SEP_LEN strlen(SEP)
#define LINE_SEP "\r\n"
#define LINE_SEP_LEN strlen(LINE_SEP)

enum
{
    OK = 0,
    DIV_ZERO,
    MOD_ZERO,
    OP_ERROR
};

// x op y  ——>  content_len \r\n x op y \r\n
void enLength(std::string &str)
{
    int len = str.size();
    std::string len_str = std::to_string(len);
    str = len_str + LINE_SEP + str + LINE_SEP;
}

bool deLength(std::string &str)
{
    size_t pos = str.find(LINE_SEP);
    if (pos == std::string::npos)
        return false;
    else
    {
        std::string len_str = str.substr(0, pos);
        int len = atoi(len_str.c_str());
        str = str.substr(pos + LINE_SEP_LEN, len);
        return true;
    }
}

class Request
{
public:
    Request(int x = 0, int y = 0, int op = 0) : _x(x), _y(y), _op(op)
    {}

    void serialize(std::string *str)
    {
#ifdef MYSELF
        *str = std::to_string(_x) + SEP + _op + SEP + std::to_string(_y);
#else
        Json::Value root;
        root["first"] = _x;
        root["second"] = _y;
        root["op"] = _op;

        Json::FastWriter writer;
        *str = writer.write(root);
#endif
    }

    // 给我的一定是一个完整的报文
    bool deserialize(const std::string &str)
    {
#ifdef MYSELF
        size_t left = str.find(SEP);
        size_t right = str.rfind(SEP);
        if (left == std::string::npos || right == std::string::npos)
            return false;
        if (right - (left + SEP_LEN) != 1)
            return false;
        if (left == right)
            return false;
        
        std::string x_str = str.substr(0, left);
        std::string y_str = str.substr(right + SEP_LEN);
        if (x_str.empty()) return false;
        if (y_str.empty()) return false;

        _x = std::stoi(x_str);
        _y = std::stoi(y_str);
        _op = str[left + SEP_LEN];
#else
        Json::Value root;
        Json::Reader reader;
        reader.parse(str, root);

        _x = root["first"].asInt();
        _y = root["second"].asInt();
        _op = root["op"].asInt();
#endif
        return true;
    }

public:
    int _x;
    int _y;
    char _op;
};

class Response
{
public:
    Response(int result = 0, int exitcode = 0) : _result(result), _exitcode(exitcode)
    {}

    void serialize(std::string *out)
    {
#ifdef MYSELF
        *out = std::to_string(_exitcode) + SEP + std::to_string(_result);
#else
        Json::Value root;
        root["exitcode"] = _exitcode;
        root["result"] = _result;

        Json::FastWriter writer;
        writer.write(root);
#endif
    }

    bool deserialize(const std::string &in)
    {
#ifdef MYSELF
        size_t pos = in.find(SEP);
        if (pos == std::string::npos)
            return false;
        
        _exitcode = std::stoi(in.substr(0, pos));
        _result = std::stoi(in.substr(pos + SEP_LEN));
#else
        Json::Value root;
        Json::Reader reader;
        reader.parse(in, root);
        _exitcode = root["exitcode"].asInt();
        _result = root["result"].asInt();
#endif
        return true;
    }

public:
    int _result;
    int _exitcode;
};

// x op y  ——>  content_len \r\n x op y \r\n
bool ReadOnePackage(std::string &inbuffer, std::string *text)
{
    size_t pos = inbuffer.find(LINE_SEP);
    if (pos == std::string::npos)
        return false;
    
    std::string len_str = inbuffer.substr(0, pos);
    int total_len = pos + LINE_SEP_LEN * 2 + std::stoi(len_str);
    if (inbuffer.size() < total_len)
        return false;

    *text = inbuffer.substr(0, total_len);
    inbuffer.erase(0, total_len);
    return true;
}