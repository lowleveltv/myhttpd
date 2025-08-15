#ifndef HTTP_H
#define HTTP_H

#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

#define HTTP_MAX_REQUEST_LEN 8192*4
#define HTTP_METHOD_MAX_LEN 8 
#define HTTP_PATH_MAX_LEN 2048 
#define HTTP_PROTOCOL_MAX_LEN 16 

#define HTTP_MAX_HEADER_KEY_LEN 256
#define HTTP_MAX_HEADER_VAL_LEN 256

#define HTTP_MAX_REASON_LEN 64

typedef enum {
    HTTP_PARSE_OK,
    HTTP_PARSE_INVALID,
} http_parse_e;

typedef enum {
    HTTP_METHOD_GET,
    HTTP_METHOD_POST,
    HTTP_METHOD_PUT,
    HTTP_METHOD_UNK,
} http_method_e;

typedef struct {
    char key[HTTP_MAX_HEADER_KEY_LEN];
    char value[HTTP_MAX_HEADER_VAL_LEN];
} http_header_t;

typedef struct {
    char method[HTTP_METHOD_MAX_LEN];
    http_method_e methode;
    char path[HTTP_PATH_MAX_LEN];
    char protocol[HTTP_PROTOCOL_MAX_LEN];
    http_header_t *headers;
    size_t header_count;
    char buffer[HTTP_MAX_REQUEST_LEN];
} http_request;

typedef struct {
    int status_code;
    char reason_phrase[HTTP_MAX_REASON_LEN];
    http_header_t *headers;
    size_t header_count;
    char *body;
    size_t body_length;
} http_response;

char *construct_http_response(const http_response *response, size_t *response_length);
void free_http_response(http_response *response);
void add_http_header(http_response *response, const char *key, const char *value);
void init_http_response(http_response *response);
void free_http_headers(http_request *request);
http_parse_e read_http_request(int socket_fd, http_request *request);
http_parse_e parse_http_headers(const char *raw_request, http_request *request);
http_method_e http_method_to_enum(char *method);
bool handle_request(http_request *req, http_response *res);


#endif // HTTP_H
