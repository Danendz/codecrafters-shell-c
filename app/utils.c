#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "utils.h"
#include "commands.h"

void read_write_input(char *input, int count, bool new_line) {
    if (new_line) {
        printf("\n");
    }
    printf("$ ");
    fflush(stdout);
    fgets(input, count, stdin);
}

void get_command_and_params(const char *input, char *command, char **params, size_t ln) {
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

int execute_and_read_system_command(const char *command, char *params) {
    char *command_path = find_command_path_by_PATH(command);

    if (command_path == NULL) {
        return CMD_NOT_FOUND;
    }

    char *command_with_params = NULL;

    if (params != NULL) {
        command_with_params = malloc(sizeof(char) * (strlen(command_path) + 1 + strlen(params)));
        sprintf(command_with_params, "%s %s", command_path, params);
    }

    FILE *fp;
    fp = popen(command_with_params == NULL ? command_path : command_with_params, "r");

    free(command_path);
    free(command_with_params);

    if (fp != NULL) {
        char out[256];

        while (fgets(out, sizeof(out), fp) != NULL) {
            printf("%s", out);
        }

        pclose(fp);

        return CMD_OK_WITHOUT_NEW_LINE;
    }

    pclose(fp);
    return CMD_NOT_FOUND;
}

int read_command(const char *command, char *params) {
    int code = CMD_NOT_FOUND;
    for (int i = 0; i < COMMANDS_LEN; i++) {
        char *name = commands[i].name;
        if (strcmp(command, name) == 0) {
            code = commands[i].action(command, params);
        }
    }

    if (code == CMD_NOT_FOUND) {
        code = execute_and_read_system_command(command, params);
    }

    if (code == CMD_NOT_FOUND) {
        printf("%s: command not found", command);
        return CMD_OK;
    }

    return code;
}

char *find_command_path_by_PATH(const char *command) {
    char *result = NULL;
    char *path = getenv("PATH");

    if (path == NULL) {
        return NULL;
    }

    char separator = ':';
    char **paths = NULL;
    int rows = 1;

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
            // Remove separator but not at the start
            int separator_fix = r == 0 ? 0 : 1;

            // if we're almost at the end we're adding to length + 1
            // so, we should add +1 to i to get correct length
            size_t len = *(t + 1) == '\0' ? i + 1 - separator_fix : i - separator_fix;

            paths[r] = (char *) malloc(sizeof(char) * len);

            char *src_step = path + c + separator_fix;
            size_t copy_num = len;

            strncpy(paths[r], src_step, copy_num);

            paths[r][len] = '\0';

            c += i;
            i = 0;
            r++;
        }
    }

    if (paths == NULL) {
        goto end;
    }

    for (int j = 0; j < rows; j++) {
        DIR *d = opendir(paths[j]);
        struct dirent *dir;
        if (d) {
            while ((dir = readdir(d)) != NULL) {
                if (strcmp(dir->d_name, command) == 0) {
                    result = malloc(sizeof(char) * (strlen(paths[j]) + strlen(dir->d_name)));

                    sprintf(result, "%s/%s", paths[j], command);
                    free(paths);
                    return result;
                }
            }
        }
    }

    end:
    free(paths);
    return result;
}