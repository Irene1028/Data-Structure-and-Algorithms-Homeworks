#include "function.h"
//#include <cstdio>
#include <cstdlib>
#include <iostream>

int helper(Function<int, int> * f, int low, int high) {
  int mid;
  int ans;
  while (low <= high) {
    mid = (high + low) / 2;
    ans = f->invoke(mid);
    if (ans == 0)
      return mid;
    if (ans > 0) {
      high = mid - 1;
    }
    else {
      low = mid + 1;
    }
  }
  if (mid > high) {
    return mid - 1;
  }
  return mid;
}
int binarySearchForZero(Function<int, int> * f, int low, int high) {
  std::cout << "check range : " << low << "~" << high << std::endl;
  if (low == high)
    return low;
  if (f->invoke(low) >= 0)
    return low;
  if (f->invoke(high - 1) <= 0)
    return high - 1;
  return helper(f, low, high - 1);
  //return EXIT_FAILURE;
}
