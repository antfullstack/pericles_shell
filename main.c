#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "path_track.h"

int main(int argc, char *argv[]) {
  while (1) {
    short found_command = 0;

    if (avalidate(argv[1], "exit", argc, 2) == 0) {
      found_command = 1;
      printf("Terminating...");
      break;
    }

    if (avalidate(argv[1], "ostream", argc, 3) == 0) {
      found_command = 1;
      printf("%s", argv[2]);
    }

    if(avalidate(argv[1], "typeof", argc, 3) == 0) {
      found_command = 1;
      if (strcmp(argv[2], "exit") == 0 || strcmp(argv[2], "ostream") == 0 || strcmp(argv[2], "typeof") == 0) { //NEEDS HASH TABLE SEARCHING (WHICH NEEDS HASH TABLE IMPLEMENTATION)
        printf("%s is a shell builtin.", argv[2]);
      } else if (findexec(argv[2]) == 0){
        printf("%s is an executable file in PATH.", argv[2]);
      } else {
        printf("%s doesn't seem to be a shell builtin or an executable in PATH.");
      }
    }

    if(isbuiltin(argv[1]) != 0 && findexec(argv[1]) == 0) {
      int id = fork();
      if (id == 0) {
        execvp(argv[1], argv);
      }
    }
  }
  return 0;
}

int avalidate(char* argument, char* command, int argc, int expected_argc) {
  if (strcmp(argument, command) && argc == expected_argc) {
    return 0;
  } else {
    return -1;
  }
}

int isbuiltin(char* name) {
  if (strcmp(name, "exit") == 0 || strcmp(name, "ostream") == 0 || strcmp(name, "typeof") == 0) {
    return 0;
  }

  return -1;
}