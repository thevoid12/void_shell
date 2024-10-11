#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include "headers.h"
#include "get_prompt.c"

#define BUFFER_SIZE 1024
#define HISTORY_SIZE 100 // Max number of history commands

char *history[HISTORY_SIZE]; // Array to store command history
int history_count = 0; // Number of commands in history
int history_index = -1; // Current index for navigating history

// Function to add a command to history
void add_to_history(const char *command) {
    if (history_count < HISTORY_SIZE) {
        history[history_count++] = strdup(command); // Duplicate the command and store
    } else {
        // If history is full, overwrite the oldest command
        free(history[0]); // Free the oldest command
        for (int i = 1; i < HISTORY_SIZE; i++) {
            history[i - 1] = history[i]; // Shift commands left
        }
        history[HISTORY_SIZE - 1] = strdup(command); // Add the new command at the end
    }
}

// Function to handle special key inputs (like the up arrow)
int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ICANON;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

// Function to read the command input, including history navigation
void read_command(char *command, size_t size, const char *prompt) {
    int pos = 0;
    command[0] = '\0'; // Clear the command buffer
    while (1) {
        int ch = getch();

        // Handle special keys
        if (ch == 27) { // Escape sequence for arrow keys
            ch = getch(); // Get the next character
            if (ch == 91) { // CSI sequence
                ch = getch(); // Get the next character
                if (ch == 65) { // Up arrow key
                    if (history_index < history_count - 1) {
                        history_index++;
                        strcpy(command, history[history_count - 1 - history_index]);
                        printf("\r%s%s", prompt, command); // Clear line and print the command
                        pos = strlen(command); // Update cursor position
                    }
                }
            }
        } else if (ch == '\n') { // Enter key
            command[pos] = '\0'; // Null-terminate the command
            break; // Exit loop
        } else if (ch == 127) { // Backspace
            if (pos > 0) {
                pos--;
                command[pos] = '\0'; // Null-terminate after deleting a character
                printf("\r%s%s ", prompt, command); // Redraw the command
                fflush(stdout);
            }
        } else { // Regular character
            if (pos < size - 1) {
                command[pos++] = ch; // Add character to command
                command[pos] = '\0'; // Null-terminate the command
                printf("%c", ch); // Echo the character
            }
        }
    }
    if (strlen(command) > 0) {
        add_to_history(command); // Add command to history if not empty
        history_index = -1; // Reset history index after command execution
    }
}

int main() {
    char command[256];
    char prompt[BUFFER_SIZE];
    while (1) {
        // Update the prompt based on the current working directory
        get_prompt(prompt);
        // Print the prompt
        printf("%s", prompt);

        // Read the command from user input, including history handling
        read_command(command, sizeof(command), prompt);

        // Exit shell on "exit" or ".exit"
        if (strcmp(command, "exit") == 0 || strcmp(command, ".exit") == 0 || strcmp(command, "quit") == 0 || strcmp(command, ".quit") == 0) {
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
        } else if (strncmp(command, "touch", 5) == 0) {
            // Skip "touch " (5 characters + 1 space) to get the filename
            char *filename = command + 6;  
            execute_touch(filename);
        } else if (strncmp(command, "cat", 3) == 0) {
            // Skip "cat " (3 characters + 1 space) to get the filename
            char *filename = command + 4;  
            if (*filename == '\0') {
                printf("cat: missing file operand\n");  // Handle missing filename
            } else {
                execute_cat(filename);
            }
        } else if (strncmp(command, "echo", 4) == 0) {
            // Skip "echo " (4 characters) to get the arguments
            char *args = command + 5; 
            if (*args == '\0') {
                printf("\n");  // Print a new line if no arguments are passed
            } else {
                execute_echo(args);
            }
        } else if (strcmp(command, "psinfo") == 0) { // Handle "psinfo" command
            execute_psinfo();
        } else {
            // Unrecognized commands
            printf("Command not found: %s\n", command);
        }
    }

    // Free history commands
    for (int i = 0; i < history_count; i++) {
        free(history[i]);
    }

    return 0;
}
