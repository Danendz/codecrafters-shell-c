#include <stdio.h>
#include <string.h>
#include <malloc.h>

int main() {
    // Wait for user input
    char input[101];
    printf("$ ");
    fflush(stdout);

    while (1) {
        fgets(input, 100, stdin);

        size_t ln = strlen(input) - 1;

        if (input[ln] == '\n') {
            input[ln] = '\0';
        }

        char *command = (char*)malloc(sizeof(char) * ln);
        int len = 0;

        for (int i = 0; i < ln; i++) {
            if (input[i] == ' ') {
                break;
            }

            command[i] = input[i];
            len++;
        }
        command[len] = '\0';

        if (strcmp(command, "exit") == 0) {
            break;
        }

        printf("%s: command not found", input);
        printf("\n$ ");
        fflush(stdout);
    }
    return 0;
}
