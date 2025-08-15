#include "tcp.h"
#include "main.h"

server_status_e bind_tcp_port(tcp_server *server, int port) {
    memset(server, 0, sizeof(*server));
    server->socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server->socket_fd == -1) {
        debug_log("Socket creation failed");
        return SERVER_SOCKET_ERROR;
    }

    server->address.sin_family = AF_INET;
    server->address.sin_addr.s_addr = INADDR_ANY;
    server->address.sin_port = htons(port);

    if (bind(server->socket_fd, (struct sockaddr *)&server->address, sizeof(server->address)) < 0) {
        debug_log("Bind failed");
        close(server->socket_fd);
        return SERVER_BIND_ERROR;
    }

    if (listen(server->socket_fd, 5) < 0) {
        debug_log("Listen failed");
        close(server->socket_fd);
        return SERVER_LISTEN_ERROR;
    }

    debug_log("Server bound and listening");
    return SERVER_OK;
}

int accept_client(int server_fd) {
    struct sockaddr_in client_address = {0};
    socklen_t client_len = sizeof(client_address);

    int client_fd = accept(server_fd, (struct sockaddr *)&client_address, &client_len);
    if (client_fd < 0) {
        debug_log("Accept failed");
        return -1;
    }

    return client_fd;
}

