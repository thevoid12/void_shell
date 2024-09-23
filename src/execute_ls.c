#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

void execute_ls(char *flags) {
    struct dirent *de;
    DIR *dr = opendir(".");
    struct stat file_stat;

    if (dr == NULL) {
        perror("Could not open current directory");
        return;
    }

    int show_hidden = 0, detailed = 0;

    // Parse flags
    if (strstr(flags, "-a")) {
        show_hidden = 1;
    }
    if (strstr(flags, "-l")) {
        detailed = 1;
    }

    while ((de = readdir(dr)) != NULL) {
        if (!show_hidden && de->d_name[0] == '.') {
            continue;  // Skip hidden files if "-a" is not provided
        }

        if (detailed) {
            // Get detailed file information
            stat(de->d_name, &file_stat);
            printf("%c%c%c%c%c%c%c%c%c%c %u %s\n",
                   (S_ISDIR(file_stat.st_mode)) ? 'd' : '-',
                   (file_stat.st_mode & S_IRUSR) ? 'r' : '-',
                   (file_stat.st_mode & S_IWUSR) ? 'w' : '-',
                   (file_stat.st_mode & S_IXUSR) ? 'x' : '-',
                   (file_stat.st_mode & S_IRGRP) ? 'r' : '-',
                   (file_stat.st_mode & S_IWGRP) ? 'w' : '-',
                   (file_stat.st_mode & S_IXGRP) ? 'x' : '-',
                   (file_stat.st_mode & S_IROTH) ? 'r' : '-',
                   (file_stat.st_mode & S_IWOTH) ? 'w' : '-',
                   (file_stat.st_mode & S_IXOTH) ? 'x' : '-',
                   file_stat.st_nlink,           // Use %u for nlink_t type
                   de->d_name);
        } else {
            // Print only the file name
            printf("%s\n", de->d_name);
        }
    }

    closedir(dr);
}
