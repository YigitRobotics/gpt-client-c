#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/main.h"

int main(int argc, char *argv[]) {
    request_t request = {0};
    response_t response = {0};

    if (argc < 3) {
        fprintf(stderr, "Lütfen iki argüman giriniz.");
        return 1;
    }

    if (strcmp(argv[1], "ask") == 0) {
        request.message = malloc(strlen(argv[2]) + 1);
        strcpy(request.message, argv[2]);
        
        check_api_key(&request, &response);
        parse_ask(&request, &response);
        send_response(&request, &response);
    }

    printf("\n\n%s", response.return_message);
    free_all(&request, &response);
    printf("%s", "Task completed.\n");

    return 0;
}