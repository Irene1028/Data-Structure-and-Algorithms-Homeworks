#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * cnt = malloc(sizeof(*cnt));
  cnt->length = 0;
  cnt->unknown = 0;
  cnt->count_arr = NULL;
  return cnt;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  size_t i = 0;
  if (name == NULL) {
    c->unknown++;
  }
  else {
    for (i = 0; i < c->length; i++) {
      if (strcmp(c->count_arr[i].key, name) == 0) {
        break;
      }
    }
    if (i == c->length) {  //did not find the same key, so add new one
      c->count_arr = realloc(c->count_arr, (i + 1) * sizeof(*(c->count_arr)));
      c->length++;

      c->count_arr[i].key = strdup(name);
      c->count_arr[i].count = 0;
    }
    c->count_arr[i].count++;
  }
  return;
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (size_t i = 0; i < c->length; i++) {
    fprintf(outFile, "%s: %d\n", c->count_arr[i].key, c->count_arr[i].count);
  }
  if (c->unknown > 0) {
    fprintf(outFile, "<unknown> : %ld\n", c->unknown);
  }
  return;
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (size_t i = 0; i < c->length; i++) {
    free(c->count_arr[i].key);
  }
  free(c->count_arr);
  free(c);
  return;
}
