#ifndef CODECRAFTERS_SHELL_C_UTILS_H
#define CODECRAFTERS_SHELL_C_UTILS_H

#include <stdbool.h>
#include <malloc.h>

void readWriteInput(char *input, int count, bool newLine);

void getCommandAndParams(const char *input, char *command, char **params, size_t ln);

int readCommand(const char *command, char *params);

#endif //CODECRAFTERS_SHELL_C_UTILS_H
