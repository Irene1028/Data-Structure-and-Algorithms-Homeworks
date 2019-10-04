// This file is for Step 3.
// You should do
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
//
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>

int seq3(int x, int y) {
  return (y - 3) * x + 2 * y;
}

void check_seq3(int x, int y, int expectans) {
  printf("seq3(%d, %d) = %d\n", x, y, seq3(x, y));
  if (expectans != seq3(x, y)) {
    exit(EXIT_FAILURE);
  }
}

int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi) {
  int countNum = 0;
  for (int i = xLow; i < xHi; i++) {
    for (int j = yLow; j < yHi; j++) {
      if (seq3(i, j) % 2 == 0)
        countNum++;
    }
  }
  return countNum;
}

void check_count(int xLow, int xHi, int yLow, int yHi, int expectans) {
  int ans = countEvenInSeq3Range(xLow, xHi, yLow, yHi);
  printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", xLow, xHi, yLow, yHi, ans);
  if (expectans != ans)
    exit(EXIT_FAILURE);
}
int main() {
  check_seq3(0, 0, 0);
  check_seq3(0, -5, -10);
  check_seq3(0, 3, 6);
  check_seq3(-4, -5, 22);
  check_seq3(3, -3, -24);
  check_seq3(5, 5, 20);
  check_seq3(-2, 1, 6);
  check_seq3(6, 6, 30);

  check_count(0, 2, 0, 3, 4);
  check_count(-2, 2, -5, -3, 6);
  check_count(-2, 2, -3, -5, 0);
  check_count(0, 0, -2, 2, 0);
  check_count(-5, 5, -5, -4, 10);
  //printf("succeed!\n");
  return EXIT_SUCCESS;
}
