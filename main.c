#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "path_track.h"

int main(int argc, char *argv[]) {
  while (1) {
    setbuf(stdout, NULL);
    printf("A: ");

    char command[1024];
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = '\0';

    if (strcmp(command, "exit") == 0) {
      break;
      
    } else if (strncmp(command,"stream ",7) == 0){
      printf("%s\n", command + 7);

    } else if (strncmp(command,"typeof ",7) == 0){
      char *buffer = command + 7;

      if ((buffer != NULL) == 0 || strcmp(buffer, "exit") == 0 || strcmp(buffer, "stream") == 0 ) {
        printf("%s is a shell builtin\n", buffer);
      } else if (findexec(buffer) == 0){
        printf("%s is an outside executable file\n", buffer);
      } else {
        printf("%s is not a shell builtin nor a recognised executable in PATH\n", buffer);
      }

    } else if (strncmp(command,"launch ", 7) == 0){
      char *buffer = command + 7;
      if (findexec(buffer) == 0) {
        system(buffer);
      } else {
        printf("%s: command not found\n",command);
      }
    } else if (strcmp(command, "clear") == 0) {
      system("clear");
    } else {
      if (findexec(command) == 0) {
        system(command);
      } else {
        printf("%s: command not found\n",command);
      }
    }
  }
  return 0;
}
