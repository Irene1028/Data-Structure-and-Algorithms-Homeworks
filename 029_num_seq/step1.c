// This file is for Step 1.
// You should do
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
//
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>

int seq1(int x) {
  return 4 * x - 3;
}
void check_seq(int x, int expectans) {
  if (expectans != seq1(x)) {
    printf("seq1(%d) = %d\n", x, seq1(x));
    exit(EXIT_FAILURE);
  }
  else
    printf("seq1(%d) = %d\n", x, seq1(x));
}

void printSeq1Range(int low, int high) {
  for (int i = low; i < high; i++) {
    printf("%d", seq1(i));
    if (i < high - 1)
      printf(", ");
  }
  printf("\n");
}

//void check_printRange(int x, int )
int main() {
  check_seq(-4, -19);
  check_seq(-3, -15);
  check_seq(-2, -11);
  check_seq(-1, -7);
  check_seq(0, -3);
  check_seq(1, 1);
  check_seq(2, 5);
  check_seq(3, 9);
  check_seq(4, 13);
  check_seq(5, 17);
  check_seq(6, 21);
  check_seq(7, 25);
  printf("printfSeq1Range(%d, %d)\n", -2, 6);
  printSeq1Range(-2, 6);
  printf("printfSeq1Range(%d, %d)\n", 7, 3);
  printSeq1Range(7, 3);
  printf("printfSeq1Range(%d, %d)\n", -4, 1);
  printSeq1Range(-4, 1);

  return EXIT_SUCCESS;
}
