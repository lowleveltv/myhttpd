#ifndef TCP_H
#define TCP_H

#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

typedef enum {
    SERVER_OK,
    SERVER_SOCKET_ERROR,
    SERVER_BIND_ERROR,
    SERVER_LISTEN_ERROR,
    SERVER_ACCEPT_ERROR
} server_status_e;

typedef struct {
    int socket_fd;
    struct sockaddr_in address;
} tcp_server;

server_status_e bind_tcp_port(tcp_server *server, int port);
int accept_client(int server_fd);

#endif // TCP_H
