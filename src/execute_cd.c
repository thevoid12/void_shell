// this file executes the cd command
//  cd denotes change working directory
// This function changes the directory using the chdir() system call.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // For chdir()
#include "headers.h"

void execute_cd(char *path) {
    if (path == NULL || strcmp(path, "") == 0) {
        path = getenv("HOME");  // Default to home directory
    }
    
    if (chdir(path) != 0) {
        perror("cd");
    }
}
