#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 1024

struct command {
    const char *name;
    const size_t length;
};

static void remove_trailing_newline(char *input);
static struct command extract_command(char *input);

int main() {
    if (setvbuf(stdout, nullptr, _IONBF, 0) != 0) {
        perror("setvbuf() failed");
        return EXIT_FAILURE;
    }
    printf("CSHELL V%s\n", CSHELL_VERSION);

    char input[MAX_INPUT_LENGTH];
    while (true) {
        printf("$ ");

        if (fgets(input, sizeof(input), stdin) == nullptr) {
            perror("fgets() failed");
            return EXIT_FAILURE;
        }
        remove_trailing_newline(input);

        const size_t input_length = strlen(input);
        const struct command command = extract_command(input);

        if (strcmp(command.name, "exit") == 0) {
            break;
        }

        if (strcmp(command.name, "echo") == 0) {
            if (input_length > command.length) {
                printf("%s\n", input + command.length + 1);
            } else {
                printf("\n");
            }
            continue;
        }

        if (strcmp(command.name, "type") == 0) {
            if (input_length > command.length) {
                const struct command argument_command = extract_command(input + command.length + 1);
                if (strcmp(argument_command.name, "echo") == 0) {
                    printf("echo is a shell builtin\n");
                } else if (strcmp(argument_command.name, "exit") == 0) {
                    printf("exit is a shell builtin\n");
                } else if (strcmp(argument_command.name, "type") == 0) {
                    printf("type is a shell builtin\n");
                } else {
                    printf("%s: not found\n", argument_command.name);
                }
            } else {
                fprintf(stderr, "\n");
            }
            continue;
        }

        printf("%s: command not found\n", command.name);
    }

    return 0;
}

static void remove_trailing_newline(char *input) {
    const size_t index = strcspn(input, "\n");
    if (index < strlen(input)) {
        input[index] = '\0';
    }
}

static struct command extract_command(char *input) {
    const char *delimiter = strchr(input, ' ');
    const bool delimiter_found = delimiter == nullptr;

    const size_t length = delimiter_found ? strlen(input) : delimiter - input;
    const char *name = delimiter_found ? input : strndup(input, length);

    return (struct command){.name = name, .length = length};
}
