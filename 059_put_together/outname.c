#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  char * outputname = malloc(sizeof(*outputname));
  size_t i = 0;
  while (inputName[i] != '\0') {
    outputname = realloc(outputname, (i + 1) * sizeof(*outputname));
    outputname[i] = inputName[i];
    i++;
  }
  outputname = realloc(outputname, (i + 8) * sizeof(*outputname));
  //char * p = outputname + i;
  memcpy(outputname + i, ".counts", 8);

  //free(p);
  return outputname;
}
