#include <stdio.h>
#include <stdlib.h>
#include "stringy.h"

size_t mystrlen(char *s){
  if (s[0]){
    return 1 + mystrlen(s+1);
  }else{
    return 0;
  }
}

char * mystrcpy(char *dest, char *src){
  int i = 0;
  while (src[i]){
    dest[i]=src[i];
    i++;
  }
  dest[i] = 0;
  return dest;
}

char * mystrcat(char *dest, char *src){
  int i = 0;
  int len = mystrlen(dest);
  while (src[i]){
    dest[i+len] = src[i];
    i++;
  }
  return dest;
}

int mystrcmp(char *s1, char *s2){
  int i=0;
  while (s1[i] == s2[i] && s1[i])
    i++;
  return s1[i] - s2[i];
}

char * mystrchr(char *s, int c){
  int i=0;
  while (s[i] && s[i] != c)
    i++;
  if (s[i] == c)
    return s+i;
  else
    return NULL;
}


char * mystrstr(char *s1, char *s2){
  int i=0, j=0;
  int found = 1;
  while (s1[i]){
    if (s1[i] == s2[j]){
      int iTmp=i+1;
      int jTmp=j+1;
      for (; iTmp < i+mystrlen(s2) && s1[iTmp]; iTmp++,jTmp++){
	if (s1[iTmp] != s2[jTmp]){
	  found=0;
	  break;
	}
      }
      if (found)
	return s1+i;
    }
    i++;
  }
  return NULL;
}
