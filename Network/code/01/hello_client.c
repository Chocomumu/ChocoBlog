#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void error_handler(char *);

int main(int argc, char *argv[])
{
    int req_serv_socket;

    struct sockaddr_in req_serv_addr;
    char  answer_msg[30];
    int serv_rep_str_len;

    memset(answer_msg, 0x00, sizeof(answer_msg));

    if (3 != argc)
    {
        printf("Usage: %s <ip> <port>\n", argv[0]);
        exit(1);
    }

    req_serv_socket = socket(PF_INET, SOCK_STREAM, 0);
    if (-1 == req_serv_socket)
    {
        error_handler("Fail to call socket()!");
    }

    memset(&req_serv_addr, 0x00, sizeof(req_serv_addr));
    req_serv_addr.sin_family = AF_INET;
    req_serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    req_serv_addr.sin_port = htons(atoi(argv[2]));

    if (-1 == connect(req_serv_socket, (struct sockaddr *) &req_serv_addr, sizeof(req_serv_addr)))
    {
        error_handler("Fail to call connect()!");
    }

    serv_rep_str_len = read(req_serv_socket, answer_msg, sizeof(answer_msg) - 1);
    if (-1 == serv_rep_str_len)
    {
        error_handler("Fail to call read()!");
    }

    printf("Message from server is:%s\n", answer_msg);
    close(req_serv_socket);
    return 0;
}

void error_handler(char *msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}