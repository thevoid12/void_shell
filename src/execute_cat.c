// this file executes the cat command
//  cat reads and prints all the content in a file

#include <stdio.h>

void execute_cat(char *filename) {
    FILE *file = fopen(filename, "r");  // Open the file in read mode
    if (file == NULL) {
        perror("cat");  // Print error if file cannot be opened
        return;
    }

    int c;
    while ((c = fgetc(file)) != EOF) {  // Read and print each character until EOF
        putchar(c);
    }

    fclose(file);  // Close the file after reading
}
