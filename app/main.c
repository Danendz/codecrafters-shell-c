#include <stdio.h>
#include <string.h>

int main() {
    // Uncomment this block to pass the first stage
    printf("$ ");
    fflush(stdout);

    // Wait for user input
    char input[101];
    fgets(input, 100, stdin);

    size_t ln = strlen(input) - 1;

    if (input[ln] == '\n') {
        input[ln] = '\0';
    }

    printf("%s: command not found", input);
    return 0;
}
