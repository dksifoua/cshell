#include "cshell/command.h"

#include "cshell/utils.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

const char *BUILTIN_COMMAND_NAMES[] = { "echo", "exit", "type" };
const size_t BUILTIN_COMMAND_NAME_COUNT = sizeof(BUILTIN_COMMAND_NAMES) / sizeof(BUILTIN_COMMAND_NAMES[0]);

struct command parse_command(const char *user_input, size_t user_input_length) {
    struct command command = { .name[0] = '\0', .arguments[0] = '\0', .fullpath[0] = '\0', .type = UNKNOWN };
    if (str_null_or_empty(user_input)) {
        return command;
    }

    const char *delimiter = strchr(user_input, ' ');
    const bool delimiter_found = delimiter != nullptr;

    size_t command_name_length = delimiter_found ? delimiter - user_input : user_input_length;
    if (command_name_length >= sizeof(command.name)) {
        command_name_length = sizeof(command.name) - 1;
    }
    memcpy(command.name, user_input, command_name_length);
    command.name[command_name_length] = '\0';

    if (delimiter_found) {
        size_t command_arguments_length = user_input_length - (size_t) (delimiter - user_input) - 1;
        if (command_arguments_length >= sizeof(command.arguments)) {
            command_arguments_length = sizeof(command.arguments) - 1;
        }
        memcpy(command.arguments, delimiter + 1, command_arguments_length);
        command.arguments[command_arguments_length] = '\0';
    }

    return command;
}

bool is_command_name_builtin(const char *name) {
    if (str_null_or_empty(name)) {
        return false;
    }

    for (size_t index = 0; index < BUILTIN_COMMAND_NAME_COUNT; ++index) {
        if (strcmp(name, BUILTIN_COMMAND_NAMES[index]) == 0) {
            return true;
        }
    }

    return false;
}

bool is_command_name_executable(const char *name, char *full_path, size_t full_path_length) {
    if (str_null_or_empty(name)) {
        return false;
    }

    const char *PATH = getenv("PATH");
    if (PATH == nullptr) {
        perror("getenv()");
        return false;
    }

    char env_path[strlen(PATH) + 1];
    strcpy(env_path, PATH);

    for (char *path = strtok(env_path, ":"); path != nullptr; path = strtok(nullptr, ":")) {
        snprintf(full_path, full_path_length, "%s/%s", path, name);

        struct stat stat_buffer;
        if (stat(full_path, &stat_buffer) == 0 && S_ISREG(stat_buffer.st_mode) && access(full_path, X_OK) == 0) {
            return true;
        }
    }
    return false;
}

void execute_command(const char *input) {
    if (str_null_or_empty(input)) {
        return;
    }

    FILE *fd = popen(input, "r");
    if (fd == nullptr) {
        perror("popen()");
        return;
    }

    char command_output_buffer[1024];
    while (fgets(command_output_buffer, sizeof(command_output_buffer), fd) != nullptr) {
        printf("%s", command_output_buffer);
    }

    if (pclose(fd) == -1) {
        perror("pclose()");
    }
    return;
}
