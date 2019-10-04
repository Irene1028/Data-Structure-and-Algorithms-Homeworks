#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  long unsigned int max = 0;
  if (n != 0) {
    long unsigned int count = 1;
    for (long unsigned int i = 1; i < n; i++) {
      if (array[i] - array[i - 1] > 0)
        count++;
      else {
        if (count > max) {
          max = count;
          //  count = 1;
        }
        count = 1;
      }
    }
    if (count > max) {
      max = count;
      //count = 1;
    }
  }
  return max;
}
