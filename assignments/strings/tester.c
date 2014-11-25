#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringy.h"

void test_strlen(){
  char s1[] = "";
  char s2[] = "1";
  char s3[] = "hello";
  if (mystrlen(s1) != strlen(s1))
    printf("strlen 0 FAIL\n");
  if (mystrlen(s1) != strlen(s1))
    printf("strlen 1 FAIL\n");
  if (mystrlen(s1) != strlen(s1))
    printf("strlen > 1 FAIL\n");
}

void test_strcpy(){
  char src[]="source";
  char dest[]="dest";
  if (mystrcpy(dest, src) != strcpy(dest, src))
    printf("strcpy FAIL\n");
}

void test_strcat(){
  char src[]="source";
  char dest[]="dest";
  if (mystrcat(dest, src) != strcat(dest, src))
    printf("strcat FAIL\n");
}

void test_strcmp(){
  char s11[]="a";
  char s12[]="ab";
  char s21[]="xyz";
  char s22[]="abc";
  char s31[]="same";
  char s32[]="same";
  if (mystrcmp(s11,s12) != strcmp(s11,s12))
    printf("strcmp FAIL: 'a', 'ab'\n");
  if (mystrcmp(s21,s22) != strcmp(s21,s22))
    printf("strcmp FAIL: 'xyz', 'abc'\n");
  if (mystrcmp(s31,s32) != strcmp(s31,s32))
    printf("strcmp FAIL: 'same', 'same'\n");
}

void test_strchr(){
  char s[]="i am reborn";
  if (mystrchr(s,'r') != strchr(s,'r'))
    printf("strchr FAIL: chr in str\n");
  if (mystrchr(s,'x') != strchr(s,'x'))
    printf("strchr FAIL: chr not in str\n");
}

void test_strstr(){
  char s[]="i am reborn";
  char s2[]="born";
  char s3[]="boring";
  if (mystrstr(s,s2) != strstr(s,s2))
    printf("strstr FAIL: substr in str; mystrstr:%p, strstr:%p\n",
	   mystrstr(s,s2),strstr(s,s2));

  if (mystrstr(s,s3) != strstr(s,s3))
    printf("strstr FAIL: substr NOT in str; mystrstr:%p, strstr:%p\n",
	   mystrstr(s,s3),strstr(s,s3));
}


int main(){
  printf("Beginning tests: failures will be printed\n");
  test_strlen();
  test_strcpy();
  test_strcat();
  test_strcmp();
  test_strchr();
  test_strstr();
  printf("END-----------------\n");
}
