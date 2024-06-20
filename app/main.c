#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

#define COMMANDS_LEN 3

#define CMD_OK 0
#define CMD_CONTINUE 1
#define CMD_BREAK 2
#define CMD_FAILED 3

typedef struct Command {
    char *name;

    int (*action)(const char *command, char *params);
} Command;

extern Command commands[COMMANDS_LEN];

int cmd_echo(const char *command, char *params) {
    if (params == NULL) return CMD_FAILED;

    printf("%s", params);

    return CMD_OK;
}

int cmd_exit(const char *command, char *params) {
    return CMD_BREAK;
}

int cmd_type(const char *command, char *params) {
    if (params == NULL) return CMD_FAILED;

    for (int i = 0; i < COMMANDS_LEN; i++) {
        if (strcmp(params, commands[i].name) == 0) {
            printf("%s is a shell builtin", params);
            return CMD_OK;
        }
    }

    printf("%s: not found", params);
    return CMD_OK;
}

Command commands[COMMANDS_LEN] = {
        {"echo", &cmd_echo},
        {"exit", &cmd_exit},
        {"type", &cmd_type}
};

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

int main() {
    char input[101];
    readWriteInput(input, 100, false);

    while (true) {
        size_t ln = strlen(input) - 1;

        if (input[ln] == '\n') {
            input[ln] = '\0';
        }

        char *command = (char *) malloc(sizeof(char) * ln);
        char *params = NULL;

        getCommandAndParams(input, command, &params, ln);

        int res = readCommand(command, params);

        if (res == CMD_BREAK) {
            break;
        } else if (res == CMD_CONTINUE) {
            continue;
        }

        readWriteInput(input, 100, true);
    }
    return 0;
}