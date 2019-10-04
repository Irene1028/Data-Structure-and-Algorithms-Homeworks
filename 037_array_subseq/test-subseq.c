#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void check_seq(int * array, size_t n, size_t expectans) {
  printf("array get!");
  size_t ans = maxSeq(array, n);
  printf("ans = %ld\n", ans);
  if (ans != expectans) {
    exit(EXIT_FAILURE);
  }
}
int main() {
  int array1[] = {1, 2, 1, 3, 5, 8, 2, 4, 6, 9};
  int array2[] = {-4, -3, -1, 0, 3, -3, -5, 5};
  int array3[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int array4[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  int array5[] = {0};
  check_seq(array1, 10, 4);
  check_seq(array2, 8, 5);
  check_seq(array3, 11, 1);
  check_seq(array4, 9, 1);
  check_seq(array5, 0, 0);
  return EXIT_SUCCESS;
}
