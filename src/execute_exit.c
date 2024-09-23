// this file executes the .exit or exit or quit or .quit command
// exits out of the shell
#include <stdlib.h>
#include <stdio.h>
#include "headers.h"

void execute_exit() {
    printf("Exiting shell...\n");
    exit(0);
}
