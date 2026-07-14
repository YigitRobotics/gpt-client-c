#include "../include/main.h"
#include <cjson/cJSON.h>
#include <stdlib.h>

status_code_t free_all(request_t *req, response_t *res) {
    free(req->api_key);
    free(req->message);
    free(res->json_payload);
    free(res->return_message);
    cJSON_Delete(res->root);

    req->api_key = NULL;
    req->message = NULL;
    res->json_payload = NULL;
    res->return_message = NULL;

    return MSG_SUCCESS;
}