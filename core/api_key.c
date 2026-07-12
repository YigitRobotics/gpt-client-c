#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/main.h"

int is_apikey_exists;

FILE* open_api_file(int open_selection) { 
    FILE *api_key_file;

    if (open_selection == 0) { // selection : 0 => read_key
        api_key_file = fopen("api_key.txt", "r");
    }

    else if (open_selection == 1) { // selection : 1 => write_key
        api_key_file = fopen("api_key.txt", "w");
    }
    
    return api_key_file;
}

void save_api_key() {
    FILE *api_key_file = open_api_file(1);

    if (!api_key_file) {
        perror("dosya açılamadı!");
        exit(EXIT_FAILURE);
    }

    char api_key_input_buff[120];

    if (is_apikey_exists == 0) {
        printf("API Anahtarını giriniz: ");

        fgets(api_key_input_buff, sizeof(api_key_input_buff), stdin);
        fprintf(api_key_file, "%s", api_key_input_buff);
    }

    is_apikey_exists = 1;
    fclose(api_key_file);
    return;
}

void check_api_key(request_t *req) {
    FILE *api_key_file = open_api_file(0);

    if (!api_key_file) {
        is_apikey_exists = 0;
        save_api_key();
        return;
    }

    fseek(api_key_file, 0, SEEK_END);
    size_t file_size = (unsigned long)ftell(api_key_file);

    if (file_size <= 10) {
        is_apikey_exists = 0;
        save_api_key();
    }

    else {
        printf("API anahtarı zaten var.");
        is_apikey_exists = 1;
    }

    fclose(api_key_file);
    api_key_file = open_api_file(0);

    if (!api_key_file) {
        perror("File açılmadı");
        exit(1);
    }

    fseek(api_key_file, 0, SEEK_END);
    file_size = (unsigned long)ftell(api_key_file);

    if (is_apikey_exists == 1) {
        rewind(api_key_file);

        char *api_key_file_content = malloc(file_size + 1);

        if (!api_key_file_content) {
            fprintf(stderr, "%s", "Allocation NULL döndürdü!");
            exit(1);
        }

        fread(api_key_file_content, 1, file_size, api_key_file);
        api_key_file_content[file_size] = '\0';
        api_key_file_content[strcspn(api_key_file_content, "\n")] = '\0';

        req->api_key = malloc(file_size + 1);
        memcpy(req->api_key, api_key_file_content, file_size);

        // for debugging
        printf("%s\n", req->api_key);
        printf("%s\n", api_key_file_content);
        printf("%s\n", req->message);
    
        free(req->api_key);
        free(api_key_file_content);
        free(req->message);
    }

    fclose(api_key_file);

    return;
}