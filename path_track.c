#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int findexec(char *name) {
    char *PATH = getenv("PATH");
    if (!PATH) return -1; 

    char *path_cpy = strdup(PATH);
    char *path_dir = strtok(path_cpy, ":");
    
    while (path_dir != NULL) {
        DIR *d = opendir(path_dir);

        if (d) {
            struct dirent *dir;

            while ((dir = readdir(d)) != NULL)
            {
                if (dir -> d_name[0] != '.') {
                    if (strcmp(dir->d_name, name) == 0) {
                        closedir(d);
                        free(path_cpy);
                        return 0;
                    }
                }
            }
            closedir(d);
        }
        path_dir = strtok(NULL, ":");
    }    

    return -1;
}