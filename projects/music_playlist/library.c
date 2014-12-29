#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "library.h"

// ASCII 'A' = 65, 'a' = 97
// Deals with upper and lower cases
void add_song(Song **lib,Song *s) {
  char *artist = s->artist;
  int i;
  for (i=65;i<91;i++){
    if (artist[0] == i || artist[0] == i+32){
      add(lib+i-65,s);
    }
  }
}

Song * find_song(Song * lib, char *name) {
  int i=0;
  for (;i<26;i++) {
    Song * current_node = lib[i]; //start at the first song in a row
    while (current_node) {
      if (!strcmp(current_node->name,name)) { //song names are the same
	return current_node;
      }
      current_node = current_node->next;
    }
  }
  return NULL;
}

Song * find_artist(Song ** lib, char *name) { //I wonder
  int i=0;
  for (;i<26;i++) {
    Song * current_node = lib[i]; //start at the first song in a row
    while (current_node) {
      if (!strcmp(current_node->artist,name)) { //artist names are the same
	return current_node;
      }
      current_node = current_node->next;
    }
  }
  return NULL;
}

void print_letter(Song ** lib, char letter) {
  Song * row = lib[letter-97];
  printf("All songs filed under %c:",letter);
  while (row) {
    printf("%s by %s",row->name,row->artist);
  }
}

void print_songs_by_artist(Song ** lib, char* artist) {
  char firstchar = artist[0];
  Song * row = lib[firstchar-97];
  printf("All songs by %s:",artist);
  while (row) {
    if (!strcmp(row->artist,artist)) {
      printf("%s by %s",row->name,row->artist);
    }
  }
}

void print_lib(Song * lib) {
  int i;
  for (i=0;i<26;i++) {
    printf("%c: ", i+65);
    printAll(lib+i);
  }
}

int size(Song ** lib) {
  int i=0;
  int size = 0;
  for (;i<26;i++) {
    Song * node = lib[i];
    while (node) {
      size++;
      node = node->next;
    }
  }
  return size;
}

void shuffle(Song ** lib, int n){ //prints out n random songs including repeats
  int s = size(lib);
  if (n < s) {
    srand(time(NULL));
    int i=0;
    for(;i<n;i++) {
      int r = rand() % s;
      int j=0;
      for(;j<26;j++) {
	Song * node = lib[j];
	while (node) {
	  r--;
	  if (r == 0) {
	    printf("%s by %s",node->name,node->artist);
	    break;
	  }
	}
      }
    }
  }
}

int delete_song(Song ** lib, char *name, char *artist) {
  char firstchar = artist[0];
  Song * row = lib[firstchar-97];
  if (!strcmp(row->name, name) && !strcmp(row->artist, artist)) { //special case for first node since there's nothing before it
    Song * temp = row->next;
    printf("Removing %s by %s",name,artist);
    free(row);
    lib[firstchar-97] = temp;
    return 1;
  }
  while (row->next) { //every other node is dealt with in terms of previous node
    Song * next_song = row->next;
    if (!strcmp(next_song->name, name) && !strcmp(next_song->artist, artist)) {
      Song * temp = next_song->next;
      printf("Removing %s by %s",name,artist);
      free(next_song);
      row->next = temp;
      return 1;
    }
  }
  printf("Could not find %s by %s",name,artist);
  return 0;
}

void delete_all(Song ** lib) {
  int i=0;
  for (;i<26;i++) {
    Song * row = lib[i];
    while (row->next) {
      Song * next_song = row->next;
      free(row);
      row = next_song;
    }
    //last node is not covered
    free(row);
  }
}   
