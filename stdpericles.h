#ifndef STDPERICLES_H
#define STDPERICLES_H

int avalidate(char* argument, char* command, int argc, int expected_argc);
int isbuiltin(char* name);
char* const* split(char* command, int *actualsize); 

#endif