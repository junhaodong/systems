#ifndef INCLUDE_H
#define INCLUDE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define LINE_LEN 256
#define STORY_LEN 2048

// Works on Linux
union semun {
  int val;
  struct semid_ds *buf;    // for getting metadata: IPC_STAT, IPC_SET
  unsigned short  *array;  // for operations with collections
};

#endif
