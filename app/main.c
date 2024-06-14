#include <stdio.h>
#include <string.h>

int main() {
    // Wait for user input
    char input[101];
    printf("$ ");
    fflush(stdout);

    while (strcmp(input, "exit") != 0) {
        fgets(input, 100, stdin);

        size_t ln = strlen(input) - 1;

        if (input[ln] == '\n') {
            input[ln] = '\0';
        }

        printf("%s: command not found", input);
        printf("\n$ ");
        fflush(stdout);
    }
    return 0;
}
