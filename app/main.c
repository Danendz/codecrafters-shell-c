#include <string.h>
#include "commands.h"
#include "utils.h"

int main() {
    char input[101];
    read_write_input(input, 100, false);

    while (true) {
        size_t ln = strlen(input) - 1;

        if (input[ln] == '\n') {
            input[ln] = '\0';
        }

        char *command = (char *) malloc(sizeof(char) * ln);
        char *params = NULL;

        get_command_and_params(input, command, &params, ln);

        int res = read_command(command, params);
        bool new_line = true;

        if (res == CMD_BREAK) {
            break;
        } else if (res == CMD_CONTINUE) {
            continue;
        } else if(res == CMD_OK_WITHOUT_NEW_LINE) {
            new_line = false;
        }

        free(command);
        if (params != NULL) {
            free(params);
        }

        read_write_input(input, 100, new_line);
    }
    return 0;
}