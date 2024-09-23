//main.c is the entry point of my shell 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"

int main() {
    char command[256];

    while (1) {
        printf("vinod_shell> ");
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break; // Exit on EOF
        }

        // Remove newline character
        command[strcspn(command, "\n")] = 0;

        if (strcmp(command, "exit") == 0) {
            break; // Exit the shell
        } else if (strcmp(command, "ls") == 0) {
            execute_ls();
        } else if (strcmp(command, "pwd") == 0) {
            execute_pwd();
        } else {
            printf("Command not found: %s\n", command);
        }
    }

    return 0;
}
