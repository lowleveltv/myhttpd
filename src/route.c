#include "route.h"
#include "http.h"

Route routes[MAX_ROUTES];
int route_count = 0;

size_t install_route(http_method_e method, const char *path, void (*handler)(http_request *req, http_response *res)) {
    if (route_count < MAX_ROUTES) {
        routes[route_count].method = method;
        strcpy(routes[route_count].path, path);
        routes[route_count].handler = handler;
        return ++route_count;
    }

    return route_count;
}


