#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
void error_handler(char *);
int main(int argc, char *argv[])
{
    int this_serv_socket;
    int req_clnt_socket;

    struct sockaddr_in this_serv_addr;
    struct sockaddr_in req_clnt_addr;

    socklen_t req_clnt_addr_len;

    char  answer_msg[] = "Hello, network!";

    if (2 != argc)
    {
        printf("Usage: %s <port>", argv[0]);
        exit(1);
    }

    this_serv_socket = socket(PF_INET, SOCK_STREAM, 0);
    if (-1 == this_serv_socket)
    {
        error_handler("Fail to call socket()!");
    }

    memset(&this_serv_addr, 0x00, sizeof(this_serv_addr));
    this_serv_addr.sin_family = AF_INET;
    this_serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    this_serv_addr.sin_port = htons(atoi(argv[1]));

    if (-1 == bind(this_serv_socket, (struct sockaddr *) &this_serv_addr, sizeof(this_serv_addr)))
    {
        error_handler("Fail to call bind()!");
    }

    if (-1 == listen(this_serv_socket, 5))
    {
        error_handler("Fail to call listen()!");
    }

    req_clnt_addr_len = sizeof(req_clnt_addr);
    req_clnt_socket = accept(this_serv_socket, (struct sockaddr *) &req_clnt_addr, &req_clnt_addr_len);
    if (-1 == req_clnt_socket)
    {
        error_handler("Fail to call accept()!");
    }

    write(req_clnt_socket, answer_msg, sizeof(answer_msg));
    close(req_clnt_socket);
    close(this_serv_socket);

    return 0;
}

void error_handler(char *msg)
{
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}