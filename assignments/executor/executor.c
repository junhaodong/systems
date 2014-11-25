#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void execute(){
  char *input = (char *) malloc(256);
  fgets(input, 256, stdin);

  int argc = 0;
  char *argv[256];
  char *arg;
  
  for (arg = strsep(&input," \n"); *arg; arg = strsep(&input, " \n"), argc++)
      argv[argc] = arg;

  argv[argc] = NULL;
  
  execvp(argv[0], argv);
}

int main(){
  printf("Enter a command...\n");
  printf("$ ");
  execute();
}
