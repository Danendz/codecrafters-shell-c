#ifndef CODECRAFTERS_SHELL_C_UTILS_H
#define CODECRAFTERS_SHELL_C_UTILS_H

#include <stdbool.h>
#include <malloc.h>

void read_write_input(char *input, int count, bool newLine);

void get_command_and_params(const char *input, char *command, char **params, size_t ln);

int read_command(const char *command, char *params);

char* find_command_path_by_PATH(const char*command);

int execute_and_read_system_command(const char *command, char *params);

#endif //CODECRAFTERS_SHELL_C_UTILS_H
