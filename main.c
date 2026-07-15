#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/main.h"

int main(int argc, char *argv[]) {
    request_t request = {0};
    response_t response = {0};

    if (argc < 2) {
        fprintf(stderr, "Usage: ./canis <command>\n");
        return 1;
    }

    open_and_read_banner_file();

    if (strcmp(argv[1], "ask") == 0) {
        if (argc < 3) {
            fprintf(stderr, "Usage: ./canis ask <question>\n");
            return 1;
        }

        request.message = strdup(argv[2]);

        if (!request.message) {
            perror("strdup");
            return 1;
        }

        check_api_key(&request, &response);
        parse_ask(&request, &response);
        send_response(&request, &response);
    }

    else if (strcmp(argv[1], "help") == 0) {
        printf("\e[0;32mUSAGE: ./canis ask <question>\n\n");
        fputs(RESET_COLOR, stdout);
    }

    else {
        fprintf(stderr, RED_COLOR "\nCommand not found - Exiting.\n\n");
        fputs(RESET_COLOR, stdout);
        return 1;
    }

    if (response.return_message) {
        printf("\n\n%s", response.return_message_parsed);
    }

    free_all(&request, &response);

    printf("Task completed.\n");

    return 0;
}