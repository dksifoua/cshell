#include <stdbool.h>
#include <stdio.h>

int main(void) {
    setbuf(stdout, NULL);
    printf("CSHELL V%s\n", CSHELL_VERSION);
    printf("> ");

    return 0;
}
