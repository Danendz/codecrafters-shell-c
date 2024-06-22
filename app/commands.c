#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include "commands.h"
#include "utils.h"

int cmd_echo(const char *command, char *params) {
    if (params == NULL) return CMD_NOT_FOUND;

    printf("%s", params);

    return CMD_OK;
}

int cmd_exit(const char *command, char *params) {
    return CMD_BREAK;
}

int cmd_type(const char *command, char *params) {
    if (params == NULL) return CMD_NOT_FOUND;

    for (int i = 0; i < COMMANDS_LEN; i++) {
        if (strcmp(params, commands[i].name) == 0) {
            printf("%s is a shell builtin", params);
            return CMD_OK;
        }
    }

    char *command_path = find_command_path_by_PATH(params);

    if (command_path != NULL) {
        printf("%s is %s", params, command_path);
        free(command_path);
        return CMD_OK;
    }

    printf("%s: not found", params);
    return CMD_OK;
}

int cmd_pwd(const char *command, char *params) {
    char cwd[256];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s", cwd);
    }
    return CMD_OK;
}

int cmd_cd(const char *command, char *params) {
    if (*params == '~') {
        char* home = getenv("HOME");
        if (home != NULL) {
            chdir(home);
            return CMD_OK_WITHOUT_NEW_LINE;
        }
    }

    DIR *d = opendir(params);

    if (d) {
        chdir(params);
        return CMD_OK_WITHOUT_NEW_LINE;
    }

    printf("cd: %s: No such file or directory", params);
    return CMD_OK;
}

Command commands[COMMANDS_LEN] = {
        {"echo", &cmd_echo},
        {"exit", &cmd_exit},
        {"type", &cmd_type},
        {"pwd",  &cmd_pwd},
        {"cd",   &cmd_cd}
};