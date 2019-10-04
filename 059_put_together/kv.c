#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parseLine(char * line, kvpair_t * pair) {
  char * p = NULL;
  char * q = NULL;
  p = strchr(line, '=');
  if (p == NULL) {
    fprintf(stderr, "There's no '=' in the input!\n");
    exit(EXIT_FAILURE);
  }
  else {
    pair->key = strndup(line, p - line);
  }
  p++;
  q = strchr(p, '\n');
  if (q == NULL) {
    fprintf(stderr, "Only a line in the input!\n");
    exit(EXIT_FAILURE);
  }
  else {
    pair->value = strndup(p, q - p);
  }
  return;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  char * line = NULL;
  kvpair_t * pairs = NULL;
  kvarray_t * kv_array = NULL;
  size_t len = 5;
  size_t i = 0;
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "Can not open the file!\n");
    exit(EXIT_FAILURE);
  }
  else {
    while (getline(&line, &len, f) >= 0) {
      pairs = realloc(pairs, (i + 1) * sizeof(*kv_array));
      if (pairs == NULL) {
        exit(EXIT_FAILURE);
      }
      else {
        parseLine(line, &pairs[i]);
      }
      i++;
    }
    if (fclose(f) != 0) {
      fprintf(stderr, "Can not close file!\n");
      exit(EXIT_FAILURE);
    }
  }
  kv_array = malloc(sizeof(*kv_array));
  kv_array->length = i;
  kv_array->kvarray = pairs;
  free(line);
  //free(pairs);//should not free here!

  return kv_array;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  size_t i = 0;
  for (i = 0; i < pairs->length; i++) {
    free(pairs->kvarray[i].key);
    free(pairs->kvarray[i].value);
  }
  free(pairs->kvarray);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  size_t n = pairs->length;
  for (size_t i = 0; i < n; i++) {
    printf("key = '%s' value = '%s'\n", pairs->kvarray[i].key, pairs->kvarray[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  size_t n = pairs->length;
  for (size_t i = 0; i < n; i++) {
    if (strcmp(key, pairs->kvarray[i].key) == 0)
      return pairs->kvarray[i].value;
  }
  return NULL;
}
