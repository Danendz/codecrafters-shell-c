#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "commands.h"

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
    int code = CMD_FAILED;
    for (int i = 0; i < COMMANDS_LEN; i++) {
        char *name = commands[i].name;
        if (strcmp(command, name) == 0) {
            code = commands[i].action(command, params);
        }
    }

    if (code == CMD_FAILED) {
        printf("%s: command not found", command);
        return CMD_OK;
    }

    return code;
}

