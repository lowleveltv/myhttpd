#include "main.h"
#include "tcp.h"
#include "http.h"

#include <cjson/cJSON.h>

typedef struct {
  short port;
} server_config;

int loadConfig(server_config *config) {
    int status = 0;

    char* configdata = loadfile("config.json");
    if (!configdata) {
      debug_log("Failed to load config, what happened?");
    }

    cJSON *config_json = cJSON_Parse(configdata);
    if (config_json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        status = 0;
        goto end;
    }

    cJSON *port = cJSON_GetObjectItemCaseSensitive(config_json, "portnumber");
    if (!cJSON_IsNumber(port)) {
        status = 0;
        goto end;
    }

    
    if (port->valueint > 65535 || port->valueint < 0) {
        debug_log("Invalid port number specified in config.");
        status = 0;
        goto end;
    }

    config->port = (short)port->valueint;

    end:
      cJSON_Delete(config_json);
      return status;
}

int main() {
    tcp_server server = {0};

    server_config config = {
      .port = 8080,
    };

    if (loadConfig(&config) == 0) {
      debug_log("failed to load config, using default values.");
    }

    server_status_e status = bind_tcp_port(&server, config.port);
    if (status != SERVER_OK) {
        debug_log("Server initialization failed");
        exit(EXIT_FAILURE);
    }

    
    for (;;) {
        int client_fd = accept_client(server.socket_fd);
        if (client_fd == -1) {
            debug_log("Failed to accept client connection");
            close(server.socket_fd);
            exit(EXIT_FAILURE);
        }

        debug_log("Client connected");

        http_request req = {0};
        http_response res = {0};

        init_http_response(&res);

        if (read_http_request(client_fd, &req) != HTTP_PARSE_OK) {
            debug_log("Failed to read or parse HTTP request");
            close(client_fd);
            return 0;
        }

        if (parse_http_headers(req.buffer, &req) != HTTP_PARSE_OK) {
            debug_log("Failed to read or parse HTTP request");
            close(client_fd);
            return 0;
        }

        char sanitized_path[1024] = {0};
        sanitize_path(req.path, sanitized_path, sizeof(sanitized_path));
        
        if (!handle_request(&req, &res)) 
          serve_file(sanitized_path, &res);

        send_http_response(client_fd, &res);

        close(client_fd);

    }
    close(server.socket_fd);
    return 0;
}
