#include "cshell/utils.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void disable_stdout_buffering(void) {
    if (setvbuf(stdout, nullptr, _IONBF, 0) != 0) {
        perror("setvbuf()");
        exit(EXIT_FAILURE);
    }
}

void remove_leading_whitespace(char *user_input) {
    if (user_input == nullptr) {
        return;
    }

    char *current_character = user_input;
    while (*current_character != '\0' && isspace((unsigned char) *current_character) != 0) {
        current_character += 1;
    }

    if (current_character != user_input) {
        memmove(user_input, current_character, strlen(current_character) + 1);
    }
}

void remove_trailing_newline(char *user_input) {
    if (user_input == nullptr) {
        return;
    }

    const size_t index = strcspn(user_input, "\n");
    if (index < strlen(user_input)) {
        user_input[index] = '\0';
    }

    // TODO(dksifoua): remove_trailing_newline doesn't handle CRLF. "ls\r\n" becomes "ls\r". Strip \r as well, e.g. strcspn(user_input, "\r\n").
}

bool str_null_or_empty(const char *input) {
    if (input == nullptr) {
        return true;
    }

    for (size_t index = 0; input[index] != '\0'; ++index) {
        if (isspace((unsigned char) input[index]) == 0) {
            return false;
        }
    }

    return true;
}
