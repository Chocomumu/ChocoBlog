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
    char msg_buffer[1024 + 1];
    int msg_str_len = 0;
    int idx = 0;
    int str_len = 0;

    int rcv_len = 0, rcv_cnt = 0;

    memset(msg_buffer, 0x00, sizeof(msg_buffer));

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
    else
    {
        puts("Connected ......");
    }
    while (1)
    {
        fputs("Press Q to quit\n", stdout);
        fgets(msg_buffer, 1024, stdin);

        if (0 == strcmp(msg_buffer, "q\n") || 0 == strcmp(msg_buffer, "Q\n"))
        {
            break;
        }
        str_len = write(req_serv_socket, msg_buffer, strlen(msg_buffer));
        while (rcv_len < str_len)
        {
            rcv_cnt = read(req_serv_socket, &msg_buffer[rcv_len], 1024 - rcv_len);
            rcv_len += rcv_cnt;
        }
        msg_buffer[rcv_len] = 0;
        printf("Message from server is \"%s\".\n", msg_buffer);
    }
    close(req_serv_socket);
    return 0;
}

void error_handler(char *msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}