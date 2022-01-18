#include <stdio.h>

#include <winsock2.h>

void error_handler(char *);
int main(int argc, char *argv[])
{
    WSADATA  wsaData;

    SOCKET  this_serv_socket;
    SOCKET  req_clnt_socket;
    
    SOCKADDR_IN  this_serv_addr;  
    SOCKADDR_IN  req_clnt_addr;

    int  req_clnt_addr_len;

    char  answer_msg[] = "Hello, network!";

    if (2 != argc)
    {
        printf("Usage: %s <port>", argv[0]);
        exit(1);
    }

    if (0 != WSAStartup(MAKEWORD(2, 2), &wsaData))
    {
        error_handler("Fail to call WSAStartup()!");
    }

    this_serv_socket = socket(PF_INET, SOCK_STREAM, 0);
    if (INVALID_SOCKET == this_serv_socket)
    {
        error_handler("Fail to call socket()!");
    }


    this_serv_addr.sin_family = AF_INET;
    this_serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    this_serv_addr.sin_port = htons(atoi(argv[1]));

    if (SOCKET_ERROR == bind(this_serv_socket, (struct sockaddr *) &this_serv_addr, sizeof(this_serv_addr)))
    {
        error_handler("Fail to call bind()!");
    }

    if (SOCKET_ERROR == listen(this_serv_socket, 5))
    {
        error_handler("Fail to call listen()!");
    }

    req_clnt_addr_len = sizeof(req_clnt_addr);
    req_clnt_socket = accept(this_serv_socket, (struct sockaddr *) &req_clnt_addr, &req_clnt_addr_len);
    if (INVALID_SOCKET == req_clnt_socket)
    {
        error_handler("Fail to call accept()!");
    }

    send(req_clnt_socket, answer_msg, sizeof(answer_msg), 0);
    closesocket(req_clnt_socket);
    closesocket(this_serv_socket);
    WSACleanup();
    return 0;
}

void error_handler(char *msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}
