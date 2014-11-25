#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>


int getDirSize(DIR *dir){
  struct dirent * entry;
  struct stat sb;
  long size = 0;
  while (entry = readdir(dir)){
    stat(entry->d_name, &sb);
    size+= sb.st_size;
  }
  rewinddir(dir);
  return size;
}

void printFileType(DIR *dir, int type){
  struct dirent * entry;
  while (entry = readdir(dir)){
    if (entry->d_type == type){
      printf("\t%s\n", entry->d_name);
    }
  }
  rewinddir(dir);
}

void printAll(char * path){
  struct stat sb;
  stat(path, &sb);

  if (S_ISDIR(sb.st_mode)){
    DIR *dir = opendir(path);
    long size = getDirSize(dir);
    printf("Total Directory Size: %lu\n", size);
    
    printf("Directories:\n");
    printFileType(dir, 4);
    
    printf("Regular files:\n");
    printFileType(dir, 8);
    
    closedir(dir);
  }else{
    printf("======Not a valid path======\n");
  }
}

// Prints contents of current directory if no arguments or multiple
// arguments are given
int main(int argc, char *argv[]){
  if (argc==2){
    printf("Statistics for directory: %s\n", argv[1]);
    printAll(argv[1]);
  }
  else{
    if (argc>2){
      printf("WARNING: Input contains more than 1 directory\n");
    }
    printf("Statistics for directory: .\n");
    printAll(".");
  }
}
