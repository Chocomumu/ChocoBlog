#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int this_serv_socket;
    int req_clnt_socket;

    struct sockaddr_in this_serv_addr;
    struct sockaddr_in req_clnt_addr;
    

    this_serv_socket = socket(PF_INET, SOCK_STREAM, 0);
    if (-1 == this_serv_socket)
    {
        error_handler("Fail to call socket()!");
    }

    memset(&this_serv_addr, 0x00, sizeof(this_serv_addr));
    this_serv_addr.sin_family = AF_INET;
    this_serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    this_serv_addr.sin_port = htons(atoi(argv[1]));

    bind

    return 0;
}