#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 1024

static void remove_trailing_newline(char *input, size_t length);

int main(void) {
    setbuf(stdout, NULL);
    printf("CSHELL V%s\n", CSHELL_VERSION);

    char command[MAX_COMMAND_LENGTH];
    while (true) {
        printf("> ");
        if (fgets(command, sizeof(command), stdin) != NULL) {
            remove_trailing_newline(command, strlen(command));
            printf("%s: command not found\n", command);
        }
    }

    return 0;
}

static void remove_trailing_newline(char *input, const size_t length) {
    const size_t n = strcspn(input, "\r\n");
    if (n < length) {
        input[n] = '\0';
    }
}
