#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>


typedef struct{
  int num;
  char * word;
} Data;


int main(){
  Data data[10], tmp;
  int fd, i, bytes, totalBytes, input;

  fd = open("data.txt", O_CREAT | O_RDWR, 0644);

  char *words[10] = {"Reeve","Wife of Bath","Pardoner","Miller","Knight", "Summoner","Host","Clerk","Merchant","Friar"};
  
  // create data
  for (i=0; i<10; i++){
    data[i].word = words[i];
    data[i].num = i*2-3;
  }
  
  // write
  totalBytes=0;
  for (i=0; i<10; i++){
    bytes = write(fd,&data[i],sizeof(data));
    totalBytes+= bytes;
  }
  printf("Bytes written: %d\n", totalBytes);

  // read
  lseek(fd,0,SEEK_SET);
  for (i=0; i<10; i++){
    bytes = read(fd,&tmp,sizeof(data));
    printf("%d: Bytes Read = %d, Word = %s, Num = %d\n",i,bytes,tmp.word,tmp.num);
  }
  
  // retrieve
  printf("\nEntry to retrieve: \n");
  scanf("%d", &input);
  lseek(fd,input*sizeof(data),SEEK_SET);
  bytes = read(fd,&tmp,sizeof(data));
  printf("%d: Bytes Read = %d, Word = %s, Num = %d\n",input,bytes,tmp.word,tmp.num);

  // modify
  printf("\nEntry to modify: \n");
  scanf("%d", &input);
  data[input].num = 314159;
  data[input].word = "NEW CHARACTER!";
  
  lseek(fd,input*sizeof(data),SEEK_SET); 
  write(fd,&data[input],sizeof(data));
  bytes = read(fd,&tmp,sizeof(data));
  printf("%d: Bytes Read = %d, Word = %s, Num = %d\n\n",input,bytes,tmp.word,tmp.num);

  // read
  lseek(fd,0,SEEK_SET);
  for (i=0; i<10; i++){
    bytes = read(fd,&tmp,sizeof(data));
    printf("%d: Bytes Read = %d, Word = %s, Num = %d\n",i,bytes,tmp.word,tmp.num);
  }

  close(fd);
}
