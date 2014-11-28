#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "song.h"

void printAll(Song *head){
  while (head){
    printf("%s - %s\n", head->artist, head->name);
    head=head->next;
  }
}

Song * createSong(char *artist, char *name){
  Song *new = (Song *)malloc(sizeof(Song));
  strcpy(new->artist, artist);
  strcpy(new->name, name);
  new->next = NULL;

  return new;
}

/* Null pointers are greater than everything else
 * because they're at the end of the list (increasing order head->null).
 * Assume no duplicates
 * Return <0 if s1 < s2; 0 if s1 == s2; >0 if s1 > s2
 */ 
int compareTo(Song *s1, Song *s2){
  if (!s1 && s2)
    return 1;
  else if (s1 && !s2)
    return -1;
  else{
    int compareArtists = strcmp(s1->artist,s2->artist);
    if (!compareArtists)
      return strcmp(s1->name,s2->name);
    else
      return compareArtists;
  }
}

// Assume no duplicates
void addFront(Song **head, Song *new){
  new->next = *head;
  *head = new;
}

// Assume no duplicates
void add(Song **head, Song *new){
  if (compareTo(new,*head) < 0){
    addFront(head,new);
  }
  else{
    Song *current = *head;
    while (compareTo(current->next,new) < 0)
      current = current->next;
    new->next = current->next;
    current->next = new;
  }
}

Song * findByName(Song *head, char *name){
  while (head){
    if (!strcmp(head->name,name))
      return head;
    head = head->next;
  }
  return 0;
}

Song * findByArtist(Song *head, char *artist){
  while (head){
    if (!strcmp(head->artist,artist))
      return head;
    head = head->next;
  }
  return 0;
}

int len(Song *head){
  int len=0;
  while (head){
    len++;
    head=head->next;
  }
  return len;
}

Song * findRandom(Song *head){
  if (!head)
    return 0;

  srand(time(NULL));
  int r = rand() % len(head);
  for (; r>0; r--)
    head=head->next;

  return head;
}

void removeSong(Song **head, Song *target){
  if (!compareTo(*head,target)){
    *head = (*head)->next;
    free(target);
  }
  else{
    Song *current = (*head)->next;
    Song *prev = *head;
    while (current){ // Set current to the target 
      if (!compareTo(current,target)){
	prev->next = current->next;
	free(current);
	return;
      }
      prev = current;
      current = current->next;
    }
  }
}

void freeAll(Song **head){
  Song *tmp;
  while (*head){
    tmp = (*head)->next;
    free(*head);
    *head = tmp;
  }
}
