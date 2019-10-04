#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  char * line = NULL;
  size_t size = 0;
  size_t line_len = 0;
  counts_t * c = createCounts();
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Could not open the file!\n");
    exit(EXIT_FAILURE);
  }
  while (getline(&line, &size, f) >= 0) {
    line_len = strlen(line);
    line[line_len - 1] = '\0';
    addCount(c, lookupValue(kvPairs, line));
    free(line);
    line = NULL;
    size = 0;  //added
  }
  free(line);
  line = NULL;  //free line for the last time loop;

  if (fclose(f) != 0) {
    fprintf(stderr, "can not close the file!\n");
    exit(EXIT_FAILURE);
  }
  f = NULL;  //added
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc <= 2) {
    fprintf(stderr, "the number of arguments is wrong!\n");
    exit(EXIT_FAILURE);
  }
  kvarray_t * kv = readKVs(argv[1]);
  char * outName = NULL;
  FILE * f = NULL;
  counts_t * c = NULL;
  for (int i = 2; i < argc; i++) {
    //count from 2 to argc (call the number you count i)

    c = countFile(argv[i], kv);
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)

    outName = computeOutputFileName(argv[i]);
    //compute the output file name from argv[i] (call this outName)

    f = fopen(outName, "w+");  //w+, not w;
    //open the file named by outName (call that f)

    printCounts(c, f);
    //print the counts from c into the FILE f

    if (fclose(f) != 0) {
      fprintf(stderr, "Can not close the file!\n");
      exit(EXIT_FAILURE);
    }
    //close f

    freeCounts(c);
    free(outName);
    //free the memory for outName and c
  }
  freeKVs(kv);
  //free the memory for kv

  return EXIT_SUCCESS;
}
