#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "pericles_fs.h"

//Searches through the system's PATH for a given name. Returns 0 if file is in path, -1 otherwise. 
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

//Opens a file at a specified path and reads one char at a time. Returns a char* if the file was indeed found, NULL otherwise. 
char* sneak(char* path, int number_of_lines) {
    char ch;
    FILE *fptr = fopen(path, "r");

    if (fptr == NULL) {
        return NULL;
    }

    int newlines_encountered = 1;
    int counter = 0;

    while((ch = fgetc(fptr)) != EOF && newlines_encountered <= number_of_lines) counter++;
    char *result = malloc(sizeof(char) * counter + 1);

    rewind(fptr);
    counter = 0;
    while((ch = fgetc(fptr)) != EOF && newlines_encountered <= number_of_lines) {
        result[counter] = ch;
        if (ch == '\n') {
            newlines_encountered++;
        }
        counter++;
    }
    result[counter] = '\0';
    return result;
} 

char* scanall(char* path) {
    char ch;
    FILE *fptr = fopen(path, "r");

    if (fptr == NULL) {
        return NULL;
    }

    int counter = 0;
    while((ch = fgetc(fptr)) != EOF) counter++ ;
    char *result = malloc(sizeof(char) * counter + 1);

    rewind(fptr);
    counter = 0;
    while((ch = fgetc(fptr)) != EOF) {
        result[counter] = ch;
        counter++;
    }
    result[counter] = '\0';
    return result;
} 

char* env(char* env) {
    if (getenv(env) == NULL) {
        return NULL;
    }
    return getenv(env); 
}