#include <string.h>
#include "commands.h"
#include "utils.h"

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

        free(command);
        if (params != NULL) {
            free(params);
        }

        readWriteInput(input, 100, true);
    }
    return 0;
}