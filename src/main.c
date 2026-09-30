#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 1024

static constexpr char ECHO_COMMAND[] = "echo ";

static void remove_trailing_newline(char *input, size_t length);

int main() {
    if (setvbuf(stdout, nullptr, _IONBF, 0) != 0) {
        perror("setvbuf failed");
        return EXIT_FAILURE;
    }
    printf("CSHELL V%s\n", CSHELL_VERSION);

    char input[MAX_INPUT_LENGTH];
    while (true) {
        printf("$ ");
        if (fgets(input, sizeof(input), stdin) != NULL) {
            remove_trailing_newline(input, strlen(input));
            if (strcmp(input, "exit") == 0) {
                break;
            }
            if (strncmp(input, ECHO_COMMAND, strlen(ECHO_COMMAND)) == 0) {
                printf("%s\n", input + strlen(ECHO_COMMAND));
            } else {
                printf("%s: command not found\n", input);
            }
        }
    }

    return 0;
}

static void remove_trailing_newline(char *input, const size_t length) {
    const size_t index = strcspn(input, "\r\n");
    if (index < length) {
        input[index] = '\0';
    }
}
