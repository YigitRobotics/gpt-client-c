#include <cjson/cJSON.h>
#include <stdio.h>
#include "../include/main.h"

void parse_ask(request_t *req, response_t *res) {
    res->root = cJSON_CreateObject();

    cJSON_AddStringToObject(res->root, "model", "gpt-5.4-mini");
    cJSON_AddStringToObject(res->root, "input", req->message);
    cJSON_AddBoolToObject(res->root, "store", 1);

    res->json_payload = cJSON_PrintUnformatted(res->root);
    
    return;
}