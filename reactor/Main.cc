#include "TcpServer.hpp"

static void usage(const std::string &proc)
{
    std::cout << "Usage:\n\t" << proc << " port\n" << std::endl;
}

void cal(const Request &req, Response &resp)
{
    int x = req._x, y = req._y;
    char op = req._op;
    switch(op)
    {
    case '+':
        resp._result = x + y;
        break;
    case '-':
        resp._result = x - y;
        break;
    case '*':
        resp._result = x * y;
        break;
    case '/':
        if (y == 0)
        {
            resp._exitcode = DIV_ZERO;
        }
        else
        {
            resp._result = x / y;
        }
        break;
    case '%':
        if (y == 0)
        {
            resp._exitcode = MOD_ZERO;
        }
        else
        {
            resp._result = x % y;
        }
        break;
    default:
        resp._exitcode = OP_ERROR;
        break;
    }
}

void calculate(Connection *conn)
{
    std::string text;
    while(ReadOnePackage(conn->_inbuffer, &text))
    {
        Request req;
        Response resp;
        deLength(text);
        req.deserialize(text);
        cal(req, resp);
        resp.serialize(&text);
        enLength(text);
        conn->_outbuffer += text;
    }

    if (conn->_sender)
    {
        conn->_sender(conn);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        usage(argv[0]);
        exit(USAGE_ERR);
    }

    uint16_t port = atoi(argv[1]);
    std::unique_ptr<TcpServer> server(new TcpServer(calculate, port));
    server->Init();
    server->Dispatcher();

    return 0;
}