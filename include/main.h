#include <stdio.h>
#ifndef MAIN_H
#define MAIN_H

typedef struct 
{
    char *return_message;
} response_message_t;

typedef struct
{
    char *message;
    char *api_key;
} request_t;

void save_api_key();
void check_api_key(request_t *req);
FILE* open_api_file(int open_selection);

#endif