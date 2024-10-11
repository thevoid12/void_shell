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
        }else if (strncmp(command,"touch",5) ==0){
         // Skip "touch " (5 characters + 1 space) to get the filename
            char *filename = command + 6;  
            execute_touch(filename);
        }else if (strncmp(command, "cat", 3) == 0) {
          // Skip "cat " (3 characters + 1 space) to get the filename
          char *filename = command + 4;  
          if (*filename == '\0') {
              printf("cat: missing file operand\n");  // Handle missing filename
          } else {
              execute_cat(filename);
          }
        }else if (strncmp(command, "echo", 4) == 0) {
        // Skip "echo " (4 characters) to get the arguments
        char *args = command + 5; 
        if (*args == '\0') {
            printf("\n");  // Print a new line if no arguments are passed
        } else {
            execute_echo(args);
        }
        }else if (strcmp(command, "psinfo") == 0) {// Handle "psinfo" command
            execute_psinfo();
        } else if (strncmp(command, "remaindme", 8) == 0) {
            int time;
            char *time_str = strtok(command + 9, " "); // Get the time (next token)
            char *message = strtok(NULL, ""); // Get the rest of the string as the message
            
            if (time_str && message) {
                time = atoi(time_str);
                execute_remindme(time, message);
            } else {
                printf("Usage: remaindme [time] [message]\n");
            }
        }
        // Unrecognized commands
        else {
            printf("Command not found: %s\n", command);
        }
    }

    return 0;
}
