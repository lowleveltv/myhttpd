#ifndef ROUTE_H
#define ROUTE_H

#include "http.h"
#include <string.h>

#define MAX_ROUTES 100

typedef struct {
    http_method_e method;
    char path[128];
    void (*handler)(http_request *, http_response *);
} Route;

#endif
