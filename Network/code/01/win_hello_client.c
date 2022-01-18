#include <stdio.h>

#include <winsock2.h>

void error_handler(char *);
int main(int argc, char *argv[])
{
    WSADATA  wsaData;

    SOCKET  req_serv_socket;
     
    SOCKADDR_IN  req_serv_addr;

    int  req_serv_addr_len;

    char  answer_msg[30];
    memset(answer_msg, 0x00, sizeof(answer_msg));

    if (3 != argc)
    {
        printf("Usage: %s <port>", argv[0]);
        exit(1);
    }

    if (0 != WSAStartup(MAKEWORD(2, 2), &wsaData))
    {
        error_handler("Fail to call WSAStartup()!");
    }

    req_serv_socket = socket(PF_INET, SOCK_STREAM, 0);
    if (INVALID_SOCKET == req_serv_socket)
    {
        error_handler("Fail to call socket()!");
    }

    memset(&req_serv_addr, 0x00, sizeof(req_serv_addr));
    req_serv_addr.sin_family = AF_INET;
    req_serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    req_serv_addr.sin_port = htons(atoi(argv[2]));

    if(SOCKET_ERROR == connect(req_serv_socket, (struct sockaddr *) &req_serv_addr, sizeof(req_serv_addr)))
    {
        error_handler("Fail to call accept()!");
    }

    if (-1 == recv(req_serv_socket, answer_msg, sizeof(answer_msg) - 1, 0))
    {
        error_handler("Fail to call recv()!");
    }
    printf("Message from server is:%s\n", answer_msg);

    closesocket(req_serv_socket);
    WSACleanup();
    return 0;
}

void error_handler(char *msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}
