#include "cshell/command.h"
#include "cshell/utils.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USER_INPUT_MAX_LENGTH 4096

int main() {
    disable_stdout_buffering();
    printf("Welcome to cshell v%s\n", CSHELL_VERSION);

    char user_input[USER_INPUT_MAX_LENGTH];
    size_t user_input_length = 0;
    struct command command;
    while (true) {
        printf("$ ");

        if (fgets(user_input, sizeof(user_input), stdin) == nullptr) {
            if (ferror(stdin) != 0) {
                perror("fgets()");
            }
            putchar('\n');
            break;
        }

        remove_trailing_newline(user_input);
        remove_leading_whitespace(user_input);

        user_input_length = strlen(user_input);
        if (user_input_length == 0) {
            continue;
        }

        command = parse_command(user_input, user_input_length);
        if (strcmp(command.name, "exit") == 0) {
            exit(EXIT_SUCCESS);
        }

        if (strcmp(command.name, "echo") == 0) {
            printf("%s\n", command.arguments);
            continue;
        }

        if (strcmp(command.name, "type") == 0) {
            if (is_command_name_builtin(command.arguments)) {
                printf("%s is a shell builtin\n", command.arguments);
                continue;
            }

            if (is_command_name_executable(command.arguments, command.fullpath, sizeof(command.fullpath))) {
                printf("%s is %s\n", command.arguments, command.fullpath);
                continue;
            }

            printf("%s: command not found\n", command.arguments);
            continue;
        }

        if (is_command_name_executable(command.name, command.fullpath, sizeof(command.fullpath))) {
            execute_command(user_input);
            continue;
        }

        printf("%s: command not found\n", command.name);
    }
    return 0;
}
