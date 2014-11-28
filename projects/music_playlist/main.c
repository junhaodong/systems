#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "library.h"

int main() {
  printf("==========\nSONG TESTS\n==========\n\n");
  Song *h = createSong("The Quick Brown Fox","The Big Black");
  Song *tmp = createSong("Team Nekokan","Can't Defeat Airman");

  printf("Created head, printing...\n");
  printAll(h);
  printf("\n");

  printf("Added to front 'Team Nekokan - Can't Defeat Airman':\n");
  addFront(&h,tmp);
  printAll(h);
  printf("\n");

  printf("Added in order 'Gas - asdf':\n");
  printf("Added in order 'Wzdf - Nmwoef':\n");
  add(&h,createSong("Gas","asdf"));
  add(&h,createSong("Wzdf","mwoef"));
  printf("\n");
  
  printf("Printing list...");
  printAll(h);
  printf("\n");

  printf("Find by name 'The Big Black':\n");
  printf("%s - The Big Black\n",findByName(h,"The Big Black")->artist);
  printf("\n");

  printf("Find by artist 'Team Nekokan':\n");
  printf("Team Nekokan - %s\n",findByArtist(h,"Team Nekokan")->name);
  printf("\n");

  printf("Find random:\n");
  Song * rand = findRandom(h);
  printf("%s - %s\n", rand->artist, rand->name);
  printf("\n");

  printf("Removed 'The Quick Brown Fox - The Big Black':\n");
  removeSong(&h,createSong("The Quick Brown Fox","The Big Black"));
  printAll(h);
  printf("\n");

  printf("Before free() h = %p\n", h);
  freeAll(&h);
  printf("After free() h = %p\n", h);
  printf("\n\n");


  printf("==========\nLIBRARY TESTS\n==========\n\n");
  Song ** lib = (Song **)calloc(26,sizeof(Song));
  Song * s1 = createSong("The Quick Brown Fox","The Big Black");
  Song * s2 = createSong("Team Nekokan","Can't Defeat Airman");
  Song * s3 = createSong("Xi","Freedom Dive");
  Song * s4 = createSong("Dragonforce","Through the Fire and the Flames");
  Song * s5 = createSong("Dragonforce","Heroes of Our Time");

  printf("Adding 5 Songs\n");
  add_song(lib, s1);
  add_song(lib, s2);
  add_song(lib, s3);
  add_song(lib, s4);
  add_song(lib, s5);

  printf("Printing Library...:\n");
  print_lib(*lib);
  
  return 0;
}
