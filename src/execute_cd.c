// this file executes the cd command
//  cd denotes change working directory

#include <unistd.h>
#include <stdio.h>
#include "headers.h"

void execute_cd(char *dir) {
    if (chdir(dir) != 0) {
        perror("cd failed");
    }
}
