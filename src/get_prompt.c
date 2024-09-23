// This function generates the prompt by 
// fetching the current working directory using getcwd()
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

void get_prompt(char *prompt) {
    char cwd[PATH_MAX];
    
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        snprintf(prompt, PATH_MAX, "vinod_shell>%s> ", cwd);
    } else {
        perror("getcwd");
        snprintf(prompt, PATH_MAX, "vinod_shell> ");
    }
}
