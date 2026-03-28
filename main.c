#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "pericles_fs.h"
#include "stdpericles.h"

int isbuiltin(char* name);
int avalidate(char* argument, char* command, int argc, int expected_argc); 
char* const* split(char* command, int *actualsize);

int main() {
  while (1) {
    fflush(stdout);

    printf("A: ");
    char command[1056]; 
    int command_capacity = sizeof(command);
    fgets(command, command_capacity, stdin);

    int argc;
    char* const* argv = split(command, &argc);
    
    if (argc > 2) {

        short found_command = 0;

        if (avalidate(argv[1], "exit", argc, 2) == 0) {
        found_command = 1;
        printf("Terminating...\n");
        break;
        }

        if (strcmp(argv[1], "ostream")== 0 && argc > 2) {
        found_command = 1;
        for (int i = 2; i < argc; i++) {
            printf("%s ", argv[i]);
        }
        printf("\n");
        }

        if (argc > 2 && (avalidate(argv[1], "sneak", argc, 3) == 0 || avalidate(argv[1], "sneak", argc, 4) == 0)) {
        found_command = 1;

        if (argc == 3) {
            char* result = scanall(argv[2]);
            if (result == NULL) {
            printf("Could not fetch file.");
            } else {        
            printf("%s\n", result);
            free(result);
            }
        } else {
            if (atoi(argv[3]) <= 0) {
            printf("Invalid number of lines provided.");
            } else {
            int argc_final = atoi(argv[3]);
            if (argc_final > 1) {
                char* result = sneak(argv[2], argc_final);
                if (result == NULL) {
                printf("Could not fetch file.");
                } else {        
                printf("%s\n", result);
                free(result);
                }
            } else {
                printf("Number of lines must be at least 1.");
            }
            }
        }
        }

        if (avalidate(argv[1], "scanall", argc, 3) == 0) {
        found_command = 1;
        char* result = scanall(argv[2]);
        if (result == NULL) {
            printf("Could not fetch file.");
        } else {        
            printf("%s\n", result);
            free(result);
        }
        }

        if (avalidate(argv[1], "fenv", argc, 3) == 0 && argv) {
        found_command = 1;
        if (argv[2] != NULL && getenv(argv[2]) != NULL) {
            char* env = getenv(argv[2]);
            printf("Value of %s is %s\n", argv[2], env);
        }
        }

        if(avalidate(argv[1], "typeof", argc, 3) == 0) {
        found_command = 1;
        if (isbuiltin(argv[2]) == 0) {
            printf("%s is a shell builtin.\n", argv[2]);
        } else if (findexec(argv[2]) == 0){
            printf("%s is an executable file in PATH.\n", argv[2]);
        } else {
            printf("%s doesn't seem to be a shell builtin or an executable in PATH.\n", argv[2]);
        }
        }

        if(argc > 1 && isbuiltin(argv[1]) != 0 && findexec(argv[1]) == 0) {
        found_command = 1;
        int exec_code = execvp(argv[1], argv + 1);
        if (exec_code == -1) {
            printf("Could not execute\n");
        } 
        }

        if (found_command == 0) {
        printf("Command not found\n");
        }

    } else {
        printf("Too few arguments\n");
    }
    free((void*)argv);
}
  return 0;
}