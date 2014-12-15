#include "control.h"


int main() {
  int key = ftok("makefile", 1);
  int shmd = shmget(key, LINE_LEN, 0664);
  if (shmd < 0){
    printf("No shared mem or semaphore.");
    printf("Create with `./control [--create|-c]`\n");
    exit(EXIT_FAILURE);
  }
  int *size = shmat(shmd, 0, 0);
  int semd = semget(key, 1, 0664);
  if (semd < 0){
    printf("No shared mem or semaphore.");
    printf("Create with `./control [--create|-c]`\n");
    exit(EXIT_FAILURE);
  }
  struct sembuf sb;  
  int story = open("story.txt", O_APPEND|O_RDWR);
  char lastLine[LINE_LEN];
  char newLine[LINE_LEN];
  // Access the semaphore
  printf("Attempting to access the story...\n");
  sb.sem_num = 0;
  sb.sem_flg = SEM_UNDO;
  sb.sem_op = -1;
  semop(semd, &sb, 1);
  printf("Access granted.\n");

  // Read and print the last line
  printf("\nLast line:\n");
  //printf("%d\n",*size);
  lseek(story, *size*-1, SEEK_END);
  read(story, lastLine, *size);
  strtok(lastLine,"\n");
  printf("%s", lastLine);

  // Read and write the new line; Update size shm
  printf("\nEnter the next line:\n");
  fgets(newLine, LINE_LEN, stdin);  
  *size = strlen(newLine);
  newLine[*size] = '\n';
  write(story, newLine, *size);
  
  // Close file descriptor, detatch shm, release access to semaphore
  close(story);
  shmdt(size);
  sb.sem_op = 1;
  semop(semd, &sb, 1);
  return 0;
}
