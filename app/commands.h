#ifndef CODECRAFTERS_SHELL_C_COMMANDS_H
#define CODECRAFTERS_SHELL_C_COMMANDS_H

#define COMMANDS_LEN 3

#define CMD_OK 0
#define CMD_CONTINUE 1
#define CMD_BREAK 2
#define CMD_NOT_FOUND 3
#define CMD_OK_WITHOUT_NEW_LINE 4

typedef struct Command {
    char *name;

    int (*action)(const char *command, char *params);
} Command;

int cmd_echo(const char *command, char *params);

int cmd_exit(const char *command, char *params);

int cmd_type(const char *command, char *params);

extern Command commands[COMMANDS_LEN];

#endif //CODECRAFTERS_SHELL_C_COMMANDS_H
