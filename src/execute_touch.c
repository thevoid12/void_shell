#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <utime.h>
#include <string.h>
#include <unistd.h>
#include "headers.h"


void execute_touch(char *filename) {

// Try to open the file; if it doesn't exist, create it.
    int fd = open(filename, O_WRONLY | O_CREAT, 0644);
    if (fd < 0) {
        perror("Failed to create or open the file");
       
    }

    close(fd);

    // Update the last access and modification times of the file
    if (utime(filename, NULL) < 0) {
        perror("Failed to update file timestamp");
        
    }

    printf("File '%s' created.\n", filename);
}
