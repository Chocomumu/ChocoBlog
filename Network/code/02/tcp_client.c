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
    int serv_rep_str_len = 0;
    int idx = 0;
    int cur_read_len = 0;

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

    while (cur_read_len = read(req_serv_socket, &answer_msg[idx ++], 1))
    {
        if (-1 == cur_read_len)
        {
            error_handler("Fail to call read()!");
        }
        serv_rep_str_len += cur_read_len;
    }
    printf("Message from serve is:%s\n", answer_msg);
    printf("The length of message from server is:%d\n", serv_rep_str_len);
    close(req_serv_socket);
    return 0;
}

void error_handler(char *msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}