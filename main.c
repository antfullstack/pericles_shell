#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "path_track.h"

int isbuiltin(char* name);
int avalidate(char* argument, char* command, int argc, int expected_argc); 
char* const* split(char* command, int *actualsize);

int main(int argc, char *argv[]) {
  while (1) {
    fflush(stdout);

    printf("A: ");
    char command[1056]; 
    int command_capacity = sizeof(command);
    fgets(command, command_capacity, stdin);

    int argc;
    char* const* argv = split(command, &argc);

    short found_command = 0;

    if (avalidate(argv[1], "exit", argc, 2) == 0) {
      found_command = 1;
      printf("Terminating...\n");
      break;
    }

    if (avalidate(argv[1], "ostream", argc, 3) == 0) {
      found_command = 1;
      printf("%s\n", argv[2]);
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

    if(isbuiltin(argv[1]) != 0 && findexec(argv[1]) == 0 && argc > 1) {
      int id = fork();
      if (id == -1) {
        printf("Could not create child process to execute program\n");
      }
      if (id == 0) {
        int exec_code = execvp(argv[1], argv + 1);
        if (exec_code == -1) {
          printf("Could not execute\n");
        }
      } if (id != 0) {
        wait(NULL);
      }
      found_command = 1;
    }

    if (found_command == 0) {
      printf("Command not found\n");
    }

    free((void*)argv);
  }
  return 0;
}

int avalidate(char* argument, char* command, int argc, int expected_argc) {
  if (strcmp(argument, command) == 0 && argc == expected_argc) {
    return 0;
  } else {
    return -1;
  }
}

int isbuiltin(char* name) {
  //NEEDS HASH TABLE SEARCHING (WHICH NEEDS HASH TABLE IMPLEMENTATION)
  if (strcmp(name, "exit") == 0 || strcmp(name, "ostream") == 0 || strcmp(name, "typeof") == 0) {
    return 0;
  }
  return -1;
}

// Allocates memory through malloc()
char* const* split(char* command, int *actualsize) {
  char** args = malloc(sizeof(char*) * 1056);
  args[0] = "./periclesshell";
  int counter = 1;
  char* buf = strtok(command, " \n");
  while (buf != NULL && counter < 1056) {
    args[counter] = buf;
    buf = strtok(NULL, " \n");
    counter++;
  }
  args[counter] = NULL;
  *actualsize = counter;
  return args;
}