#ifndef COMMAND_H
#define COMMAND_H

#include <limits.h>
#include <stdbool.h>
#include <stddef.h>

#define MAX_COMMAND_NAME_LENGTH 1024
#define MAX_COMMAND_ARGS_LENGTH 3072

enum command_t {
    BUILTIN,
    EXECUTABLE,
    UNKNOWN,
};

struct command {
    char name[MAX_COMMAND_NAME_LENGTH + 1];
    char arguments[MAX_COMMAND_ARGS_LENGTH + 1];
    char fullpath[PATH_MAX + 1];
    enum command_t type;
};

struct command parse_command(const char *user_input, size_t user_input_length);
bool is_command_name_builtin(const char *name);
bool is_command_name_executable(const char *name, char *full_path, size_t full_path_length);
void execute_command(const char *input);

#endif
