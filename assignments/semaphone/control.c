#include "control.h"

/** TODO (for this and writer.c)
 * dynamically allocate mem
 * abstract/break up into methods
 * create a log of past stories rather than truncating the txt file
*/

int main(int argc, char **argv){
  int fd;
  int shmd, semd;
  char *shm_buf;
  int key = ftok("makefile", 1);
  if (argc < 2){
    printf("Usage: `./control [--create|-c]` or `./control [--remove|-r]`\n");
    exit(EXIT_FAILURE);
  }
  if (!strcmp(argv[1], "--create") || !strcmp(argv[1], "-c")){
    printf("Creating file: story.txt\n");
    fd = open("story.txt", O_CREAT, 0644);
    close(fd);

    printf("Creating shared memory\n");
    shmd = shmget(key, LINE_LEN, IPC_CREAT|IPC_EXCL|0644);
    shm_buf = shmat(shmd, 0, 0);

    printf("Creating semaphore\n");
    union semun su;
    su.val = 1;
    semd = semget(key, 1, IPC_CREAT|0644);
    semctl(semd, 0, SETVAL, su);
  }
  else if (!strcmp(argv[1], "--remove") || !strcmp(argv[1], "-r")){
    fd = open("story.txt", O_RDONLY, 0644);
    if (fd < 0){
      printf("ERROR: file not found: story.txt\n");
    }
    else{
      char story[STORY_LEN];
      read(fd, story, STORY_LEN);
      printf("=======Begin-story=======\n%s", story);
      printf("========End-story========\n");
      printf("Removing file content\n");
      fd = open("story.txt", O_TRUNC);
      close(fd);
    }
    printf("Removing shared memory\n");
    struct shmid_ds d;
    shmd = shmget(key, LINE_LEN, 0644);    
    shmdt(shm_buf);
    shmctl(shmd, IPC_RMID, &d);

    printf("Removing semaphore\n");
    semd = semget(key, 1, 0644);
    semctl(semd, 0, IPC_RMID);
  }
  else{
    printf("Usage: `./control [--create|-c]` or `./control [--remove|-r]`\n");
  }
  return 0;
}

