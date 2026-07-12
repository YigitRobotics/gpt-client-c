#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include "../include/main.h"

void write_response() {

}

void send_response(char *message) {
    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    
    if(curl) {
        struct curl_slist *headers = NULL;

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.openai.com/v1/responses");

        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, "Authorization: Bearer: nnnnnn");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        const char *json_payload = "{\n"
                                   "    \"model\": \"gpt-5.4-mini\",\n"
                                   "    \"input\": \"write a haiku about ai\",\n"
                                   "    \"store\": true\n"
                                   "}";
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_payload);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_slist_free_all(headers); 
        curl_easy_cleanup(curl);  
    }


    curl_global_cleanup();

    return;
}
