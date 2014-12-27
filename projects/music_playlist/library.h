#ifndef LIBRARY_H
#define LIBRARY_H

#include "song.h"

void add_song(Song **,Song *);

Song * find_song(Song *, char *);

Song * find_artist(Song **, char *);

void print_letter(Song **, char);

void print_songs_by_artist(Song **, char *);

void print_lib(Song *);

void shuffle(Song **, int);

int size(Song **);

int delete_song(Song **, char *, char *);

void delete_all(Song **);

#endif
