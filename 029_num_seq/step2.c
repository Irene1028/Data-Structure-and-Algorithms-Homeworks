// This file is for Step 2.
// You should do
//  Step 2 (A): write seq2
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sumSeq2
//  Step 2 (D): add test cases to main to test sumSeq2
//
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>

int seq2(int x) {
  return x * (x + 3) + 1;
}
void check_seq2(int x, int expectans) {
  printf("seq2(%d) = %d\n", x, seq2(x));
  if (expectans != seq2(x)) {
    exit(EXIT_FAILURE);
  }
}

int sumSeq2(int low, int high) {
  int ans = 0;
  for (int i = low; i < high; i++) {
    ans += seq2(i);
  }
  return ans;
}
void check_sum(int low, int high, int expectans) {
  printf("sumSeq2(%d, %d) = %d\n", low, high, sumSeq2(low, high));
  if (expectans != sumSeq2(low, high)) {
    exit(EXIT_FAILURE);
  }
}
int main() {
  check_seq2(-4, 5);
  check_seq2(-3, 1);
  check_seq2(-2, -1);
  check_seq2(-1, -1);
  check_seq2(0, 1);
  check_seq2(1, 5);
  check_seq2(2, 11);
  check_seq2(3, 19);
  check_seq2(4, 29);
  check_seq2(5, 41);
  check_seq2(6, 55);
  check_seq2(7, 71);
  check_seq2(8, 89);
  check_seq2(9, 109);
  check_seq2(10, 131);
  check_seq2(11, 155);
  check_seq2(12, 181);
  check_seq2(13, 209);
  check_seq2(14, 239);

  check_sum(0, 2, 6);
  check_sum(3, 6, 89);
  check_sum(9, 7, 0);

  return EXIT_SUCCESS;
}
