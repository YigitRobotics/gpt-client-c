#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "../include/main.h"

unsigned long write_response_callback(
    char *contents,
    size_t data_size,
    size_t nmemb,
    void *userp
) {
    size_t real_size = nmemb * data_size;
    response_buffer_t *buffer = userp;

    char *new_data = realloc(
        buffer->data,
        buffer->size + real_size + 1 // 1 byte is null-terminator
    );

    if (!new_data) {
        fprintf(stderr, "Reallocation başarısız!");
        return 0;
    }

    buffer->data = new_data;

    memcpy(
        &buffer->data[buffer->size],
        contents,
        real_size
    );

    buffer->size += real_size;
    buffer->data[buffer->size] = '\0';

    return real_size;
}   

void send_response(request_t *req, response_t *res) {
    CURL *curl;
    CURLcode curlres;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    
    if (curl) {
        response_buffer_t response_buffer_callback;

        response_buffer_callback.data = malloc(sizeof(char));
        response_buffer_callback.size = 0;

        struct curl_slist *headers = NULL;

        char auth_api_token_payload[res->file_size + 23]; // Starting of auth header: 22 bytes + null-termimator.
        strcpy(auth_api_token_payload, "Authorization: Bearer ");

        strcat(auth_api_token_payload, req->api_key);

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/responses");

        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, auth_api_token_payload);

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_response_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_buffer_callback);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, res->json_payload);

        curlres = curl_easy_perform(curl);

        if (curlres != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(curlres));
        }

        curl_slist_free_all(headers); 
        curl_easy_cleanup(curl);  

        cJSON *response_json =
            cJSON_Parse(response_buffer_callback.data);

        cJSON *output =
            cJSON_GetObjectItem(response_json, "output");

        cJSON *message =
            cJSON_GetArrayItem(output, 0);

        cJSON *content =
            cJSON_GetObjectItem(message, "content");

        cJSON *text_obj =
            cJSON_GetArrayItem(content, 0);

        cJSON *text =
            cJSON_GetObjectItem(text_obj, "text");

        res->return_message = malloc(strlen(response_buffer_callback.data) + 1);
        if (cJSON_IsString(text) && text->valuestring) {
            res->return_message = malloc(strlen(text->valuestring) + 1);
            strcpy(res->return_message, text->valuestring);
        }

        res->return_message_parsed = malloc(strlen(response_buffer_callback.data) + 1);
        strcpy(res->return_message_parsed, markdown_to_ansi(res->return_message));

        cJSON_Delete(response_json);
    }

    else {
        fprintf(stderr, "cURL başlatılamadı!\n");
        free_all(req, res);
        exit(1);
    }

    curl_global_cleanup();


    return;
}
