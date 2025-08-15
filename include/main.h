#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

char *loadfile(const char *path);

#define debug_log(s) fprintf(stderr, "[%s] %s\n", __FILE__, s)

#endif // MAIN_H
