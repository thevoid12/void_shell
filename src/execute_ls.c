// this file executes the ls command
// ls lists the files in the folder
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

void execute_ls() {
    struct dirent *de;
    DIR *dr = opendir(".");

    if (dr == NULL) {
        perror("Could not open current directory");
        return;
    }

    while ((de = readdir(dr)) != NULL) {
        printf("%s\n", de->d_name);
    }

    closedir(dr);
}
