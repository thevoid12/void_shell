#include <stdio.h>
#include <string.h>  

void execute_echo(char *args) {
    // Check if the string starts with a double quote
    if (args[0] == '"') {
        char *start = args + 1;  // Skip the opening double quote
        char *end = strrchr(start, '"');  // Find the last closing double quote
        if (end != NULL) {
            // Temporarily replace the closing quote with a null terminator to print the value inside the quotes
            *end = '\0';
            printf("%s\n", start);
        } else {
            // No closing quote found, so just print the argument as is
            printf("echo: missing closing double quote\n");
        }
    } else {
        // No quotes, print the arguments as they are
        printf("%s\n", args);
    }
}
