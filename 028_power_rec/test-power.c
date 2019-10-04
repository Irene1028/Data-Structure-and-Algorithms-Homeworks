#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);
void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned ans = power(x, y);
  if (ans != expected_ans)  //printf("catch a problem!");
    exit(EXIT_FAILURE);
}
int main() {
  run_check(0, 0, 1);
  run_check(1, 0, 1);
  run_check(0, 100, 0);
  run_check(1, 1, 1);
  run_check(1, 100, 1);
  run_check(-1, 3, -1);
  run_check(2, 0, 1);
  run_check(2, 3, 8);
  //run_check(2, -3, 0.125);  //not 10
  //run_check(9, 0.5, 3);     //not 10
  //run_check(2.2, 2, 4.84);  //not 10
  printf("You passed all tests!\n");
  return EXIT_SUCCESS;
}
