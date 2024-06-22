#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "commands.h"

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

    char *path = getenv("PATH");
    char separator = ':';
    char **paths = NULL;
    int rows = 1;

    if (path != NULL) {
        char *t;

        for (t = path; *t != '\0'; t++) {
            if (*t == separator) {
                rows++;
            }
        }

        paths = (char **) malloc(sizeof(char *) * rows);

        int i = 0;
        int r = 0;
        int c = 0;
        for (t = path; *t != '\0'; t++, i++) {
            if (*t == separator || *(t + 1) == '\0') {
                // if we're almost at the end we're adding to length + 1
                // so, we should add +1 to i to get correct length
                size_t len = *(t + 1) == '\0' ? i + 1 : i;

                paths[r] = (char *) malloc(sizeof(char) * len);

                // Remove separator but not at the start
                int separator_fix = r == 0 ? 0 : 1;
                char *src_step = path + c + separator_fix;
                size_t copy_num = len - separator_fix;

                strncpy(paths[r], src_step, copy_num);
                paths[r][len] = '\0';

                c += i;
                i = 0;
                r++;
            }
        }
    }

    for (int i = 0; i < COMMANDS_LEN; i++) {
        if (strcmp(params, commands[i].name) == 0) {
            printf("%s is a shell builtin", params);
            free(paths);
            return CMD_OK;
        }
    }

    if (paths != NULL) {
        for (int j = 0; j < rows; j++) {
            printf("%s\n", paths[j]);
            DIR *d = opendir(paths[j]);
            struct dirent *dir;
            if (d) {
                while ((dir = readdir(d)) != NULL) {
                    if (strcmp(dir->d_name, params) == 0) {
                        printf("%s is %s/%s", params, paths[j], params);
                        free(paths);
                        return CMD_OK;
                    }
                }
            }
        }
    }

    printf("%s: not found", params);
    free(paths);
    return CMD_OK;
}

Command commands[COMMANDS_LEN] = {
        {"echo", &cmd_echo},
        {"exit", &cmd_exit},
        {"type", &cmd_type}
};