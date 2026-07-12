#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/main.h"

int main(int argc, char *argv[]) {
    request_t request;
    if (argc < 3) {
        fprintf(stderr, "Lütfen iki argüman giriniz.");
        return 1;
    }

    if (strcmp(argv[1], "ask") == 0) {
        request.message = malloc(sizeof(argv[2]) + 1);
        strcpy(request.message, argv[2]);
        
        check_api_key(&request);
    }

    return 0;
}