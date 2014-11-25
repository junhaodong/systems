#include <stdio.h>
#include <stdlib.h>
#include "llist.h"

void print_list(Node *h){
  while (h){
    printf("%d, ", h->data);
    h=h->next;
  }
  printf("\n");
}

Node * insert_front(Node *h, int data){
  Node *new = (Node *)malloc(sizeof(Node));
  new->data = data;
  new->next = h;
  return new;
}

Node * free_list(Node *h){
  Node *tmp;
  while (h){
    tmp = h->next;
    free(h);
    h = tmp;
  }
  return h;
}

// Testing
int main(){
  Node * h = 0;
  int i;

  for (i=0; i<5; i++)
    h = insert_front(h,i);

  printf("Printing h\n");
  print_list(h);

  printf("Print *h Before free(): %p\n", h);
  h = free_list(h);
  printf("Print *h after free(): %p\n", h);

  printf("Printing h\n");
  print_list(h);
  return 0;
}
