// this file executes the pwd command
// pwd prints the working directory
#include <stdio.h>
#include <unistd.h>

void execute_pwd() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("getcwd() error");
    }
}
