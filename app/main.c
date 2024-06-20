#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

void readWriteInput(char *input, int count, bool newLine) {
    if (newLine) {
        printf("\n");
    }
    printf("$ ");
    fflush(stdout);
    fgets(input, count, stdin);
}

void getCommandAndParams(const char *input, char *command, char **params, size_t ln) {
    int len = 0;
    int space_i = -1;

    for (int i = 0; i < ln; i++) {
        if (input[i] == ' ') {
            space_i = i + 1;
            break;
        }

        command[i] = input[i];
        len++;
    }

    command[len] = '\0';

    if (space_i != -1) {
        size_t params_len = ln - space_i;
        *params = (char *) malloc(sizeof(char) * params_len);

        for (int i = space_i, j = 0; i < ln; i++, j++) {
            (*params)[j] = input[i];
        }

        (*params)[params_len] = '\0';
    }
}

int readCommand(const char *command, char *params) {
    if (strcmp(command, "exit") == 0) {
        return -1;
    } else if(strcmp(command, "echo") == 0 && params != NULL) {
        printf("%s", params);
    } else if(strcmp(command, "type") == 0 && params != NULL) {
        printf("%s", params);
    } else {
        printf("%s: command not found", command);
    }

    return 0;
}

int main() {
    char input[101];
    readWriteInput(input, 100, false);

    while (1) {
        size_t ln = strlen(input) - 1;

        if (input[ln] == '\n') {
            input[ln] = '\0';
        }

        char *command = (char *) malloc(sizeof(char) * ln);
        char *params = NULL;

        getCommandAndParams(input, command, &params, ln);

        int res = readCommand(command, params);

        if (res == -1) {
            break;
        }

        readWriteInput(input, 100, true);
    }
    return 0;
}