#include <unistd.h>
#include <malloc.h>
#include "globals.h"

char *cwd = "";

void init_cwd() {
    cwd = malloc(sizeof(char) * MAX_PATH_SIZE);
    getcwd(cwd, MAX_PATH_SIZE);
}
