#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>

static void sighandler(int signo){
  int f, fd, status;

  if(signo == SIGUSR1){
    printf("SIGUSR1 received. Appending output of `who` to whoOut.txt\n");
    fd = open("whoOut.txt", O_APPEND | O_WRONLY | O_CREAT);
    dup2(fd, STDOUT_FILENO);
    close(fd);
    execlp("who","who",NULL);
  }
  else if(signo == SIGUSR2){
    printf("SIGUSR2 received. Appending output of `ps` to psOut.txt\n");
    fd = open("psOut.txt", O_APPEND | O_WRONLY | O_CREAT);
    dup2(fd, STDOUT_FILENO);
    close(fd);
    execlp("ps","ps",NULL);
  }
  else if(signo == SIGINT){
    f = fork();

    if (!f){
      printf("\n\nPrinting whoOut.txt (who):\n");
      execlp("cat","cat","whoOut.txt",NULL);
    }else{
      wait(&status);
      printf("\n\nPrinting psOut.txt (ps):\n");
      execlp("cat","cat","psOut.txt",NULL);
    }
  }
}

int main(){
  signal(SIGUSR1,sighandler);
  signal(SIGUSR2,sighandler);
  signal(SIGINT,sighandler);
  while (1){
    printf("running with pid:    %d\n", getpid());
    sleep(1);
  }
}

