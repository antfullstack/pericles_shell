#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//Takes an expected command with a string argument, runs it through strcmp(), and a pair of integers (argc and expected argc) and compares them. Returns 0 if all checks passed -1 otherwise.
int avalidate(char* argument, char* command, int argc, int expected_argc) {
  if (strcmp(argument, command) == 0 && argc == expected_argc) {
    return 0;
  } else {
    return -1;
  }
}

//Checks if a command is a recognised periclesshell builtin, returns 0 if found, -1 otherwise. 
int isbuiltin(char* name) {
  //NEEDS HASH TABLE SEARCHING (WHICH NEEDS HASH TABLE IMPLEMENTATION)
  if (strcmp(name, "exit") == 0 || strcmp(name, "fenv") == 0 || strcmp(name, "scanall") == 0 || strcmp(name, "ostream") == 0 || strcmp(name, "typeof") == 0 || strcmp(name, "sneak") == 0) {
    return 0;
  }
  return -1;
}

//Returns dynamic a char* const*, dynamic memory pointer from a char*, and writes the number of elements at the adress of the second argument (int type)
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



