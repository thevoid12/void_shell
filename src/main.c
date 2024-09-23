 //main.c is the entry point of my shell 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"
#include "get_prompt.c"

#define BUFFER_SIZE 1024

int main() {
    char command[256];
    char prompt[BUFFER_SIZE];
    while (1) {
       // Update the prompt based on the current working directory
        get_prompt(prompt);
        // Print the prompt
        printf("%s", prompt);

        if (fgets(command, sizeof(command), stdin) == NULL) {
            break; // Exit on EOF
        }

        // Remove newline character
        command[strcspn(command, "\n")] = 0;

        // Exit shell on "exit" or ".exit"
        if (strcmp(command, "exit") == 0 || strcmp(command, ".exit") == 0 || strcmp(command, "quit") == 0 || strcmp(command, ".quit") == 0){
            execute_exit();
        } 
        // Change directory with the "cd" command
        else if (strncmp(command, "cd", 2) == 0) {
            char *dir = command + 3; // Skip "cd "
            execute_cd(dir);
        } 
        // Handle "ls" command and flags
        else if (strncmp(command, "ls", 2) == 0) {
            char *flags = command + 3; // Get flags (e.g., "-lah")
            execute_ls(flags);
        } 
        // Handle "pwd" command
        else if (strcmp(command, "pwd") == 0) {
            execute_pwd();
        } 
        // Unrecognized commands
        else {
            printf("Command not found: %s\n", command);
        }
    }

    return 0;
}
