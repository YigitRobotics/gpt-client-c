#include <stdio.h>
#include <cjson/cJSON.h>
#ifndef MAIN_H
#define MAIN_H

typedef struct 
{
    char *return_message;
    cJSON *root;
    char *json_payload;
    int file_size;
} response_t;

typedef struct {
    char *data;
    size_t size;
} response_buffer_t;

typedef struct
{
    char *message;
    char *api_key;
} request_t;

typedef enum {
    MSG_SUCCESS,
    MSG_FAIL
} status_code_t; // For free_all_function now

void save_api_key();
void check_api_key(request_t *req, response_t *res);
FILE* open_api_file(int open_selection);
void send_response(request_t *req, response_t *res);
void parse_ask(request_t *req, response_t *res);
status_code_t free_all(request_t *req, response_t *res);

#endif