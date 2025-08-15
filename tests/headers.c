#include "http.h"
#include <stdio.h>
#include <string.h>

int main() {
    const char *raw_request =
        "GET /index.html HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "User-Agent: curl/7.68.0\r\n"
        "Accept: */*\r\n"
        "\r\n";

    http_request request = {0};
    parse_http_headers(raw_request, &request);

    printf("Parsed HTTP Headers:\n");
    for (size_t i = 0; i < request.header_count; i++) {
        printf("%s: %s\n", request.headers[i].key, request.headers[i].value);
    }

    free_http_headers(&request);
    return 0;
}
