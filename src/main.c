#include <dirent.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 128
#define MAX_INPUT_LENGTH 1024

struct command {
    char name[MAX_COMMAND_LENGTH];
    size_t length;
};

static void remove_trailing_newline(char *input);
static struct command extract_command(const char *input);
static bool is_command_builtin(struct command command);
static bool is_command_executable(struct command command, char *full_command_path);

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
                if (is_command_builtin(argument_command)) {
                    printf("%s is a shell builtin\n", argument_command.name);
                } else {
                    char full_command_path[PATH_MAX];
                    if (is_command_executable(argument_command, full_command_path)) {
                        printf("%s is %s\n", argument_command.name, full_command_path);
                    } else {
                        printf("%s: not found\n", argument_command.name);
                    }
                }
            } else {
                fprintf(stderr, "\n");
            }
            continue;
        }

        char full_command_path[PATH_MAX];
        if (is_command_executable(command, full_command_path)) {
            FILE *fd = popen(input, "r");
            if (fd == nullptr) {
                perror("popen() failed");
            } else {
                char output_buffer[1024];
                while (fgets(output_buffer, sizeof(output_buffer), fd) != nullptr) {
                    printf("%s", output_buffer);
                }
                if (pclose(fd) != 0) {
                    perror("pclose() failed");
                }
            }
            continue;
        }

        printf("%s: command not found\n", command.name);
    }

    return 0;
}

static void remove_trailing_newline(char *input) {
    if (input == nullptr) {
        return;
    }
    const size_t index = strcspn(input, "\n");
    if (index < strlen(input)) {
        input[index] = '\0';
    }
}

static struct command extract_command(const char *input) {
    struct command command = {.name[0] = '\0', .length = 0};
    if (input == nullptr) {
        return command;
    }

    const char *delimiter = strchr(input, ' ');
    size_t full_length = delimiter == nullptr ? strlen(input) : delimiter - input;

    command.length = full_length >= MAX_COMMAND_LENGTH ? MAX_COMMAND_LENGTH - 1 : full_length;
    memcpy(command.name, input, command.length);
    command.name[command.length] = '\0';
    return command;
}

static bool is_command_builtin(const struct command command) {
    if (strcmp(command.name, "echo") == 0 || strcmp(command.name, "exit") == 0 || strcmp(command.name, "type") == 0) {
        return true;
    }

    return false;
}

static bool is_command_executable(const struct command command, char *full_command_path) {
    const char *env_path = getenv("PATH");
    if (env_path == nullptr) {
        return false;
    }

    const size_t env_path_length = strlen(env_path);
    char env_path_copy[env_path_length + 1];
    memcpy(env_path_copy, env_path, env_path_length);
    env_path_copy[env_path_length] = '\0';

    for (char *current_path = strtok(env_path_copy, ":"); current_path != nullptr; current_path = strtok(nullptr, ":")) {
        snprintf(full_command_path, PATH_MAX, "%s/%s", current_path, command.name);

        struct stat stat_buffer;
        if (stat(full_command_path, &stat_buffer) == 0 && access(full_command_path, X_OK) == 0) {
            return true;
        }
    }

    return false;
}
