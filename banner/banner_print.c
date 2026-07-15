#include "../include/main.h"
#include <stdlib.h>
#include <stdio.h>

void print_banner(char *banner_content) {
    printf(CYAN_COLOR "\n%s\n", banner_content);
    printf(RESET_COLOR "");
}

void open_and_read_banner_file() {
    FILE *banner_file = fopen("banner/banner.txt", "r"); 

    if (!banner_file) {
        perror("fopen: ");
        exit(1);
    }

    fseek(banner_file, 0, SEEK_END);
    long banner_size = ftell(banner_file);

    if (banner_size < 0) {
        fprintf(stderr, "File size smaller than 0\n");
        fclose(banner_file);
        exit(EXIT_FAILURE);
    }
    rewind(banner_file);

    char *content_buffer = malloc(banner_size + 1);

    if (!content_buffer) {
        fclose(banner_file);
        fprintf(stderr, "Allocaton failed!");
        exit(1);
    }
    size_t bytes_readed = fread(content_buffer, 1, banner_size, banner_file);

    if (bytes_readed != banner_size) {
        if (ferror(banner_file)) 
            perror("fread: ");
        else 
            fprintf(stderr, "Unexpected EOF\n");

        fclose(banner_file);
        free(content_buffer);
        exit(1);
    }

    content_buffer[banner_size] = '\0';

    fclose(banner_file);

    print_banner(content_buffer);
    free(content_buffer);
}