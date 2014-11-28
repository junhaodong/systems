#ifndef SONG_H
#define SONG_H

typedef struct s{
  char artist[256];
  char name[256];
  struct s *next;
} Song;

void printAll(Song *);

Song * createSong(char *, char *);

int compareTo(Song *, Song *);

void addFront(Song **, Song *);

void add(Song **, Song *);

Song * findByName(Song *, char *);

Song * findByArtist(Song *, char *);

int len(Song *);

Song * findRandom(Song *);

void removeSong(Song **, Song *);

void freeAll(Song **);

#endif
