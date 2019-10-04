int max(int x, int y) {
  int m = 0;
  if (x > y) {
    m = x;
  }
  else {
    m = y;
  }
  return m;
}

int is_between(int x_offset, int y_offset, int size1, int size2, int x, int y) {
  //check if  EITHER
  int a = 0;
  int b = 0;
  //int c = 0;
  if ((x >= x_offset) && (x < x_offset + size2)) {
    //    ((x is between x_offset  and x_offset +size2) AND
    if ((y == y_offset) || (y == y_offset + size2 - 1)) {
      //     y is equal to either y_offset OR y_offset + size2 - 1 )
      a = 1;
    }
  }
  if ((y >= y_offset) && (y < y_offset + size2)) {
    if ((x == x_offset) || (x == x_offset + size2 - 1)) {
      //    ((y is between y_offset and y_offset + size2) AND
      //     x is equal to either x_offset OR x_offset + size2 -1)
      b = 1;
    }
  }
  /*if ((x < size1 && (y == 0 || y == size1 - 1)) || (y < size1 && (x == 0 || x == size1 - 1))) {
    c = 1;
    }*/
  //if not,
  // check if EITHER
  //    x is less than size1 AND (y is either 0 or size1-1)
  // OR
  //    y is less than size1 AND (x is either 0 or size1-1)
  if ((a || b) == 1) {
    return 1;
  }
  else {
    return 0;
  }
}
int is_less(int size1, int size2, int x, int y) {
  if (((x < size1) && ((y == 0) || (y == size1 - 1))) ||
      ((y < size1) && ((x == 0) || (x == size1 - 1))))
    return 1;
  else
    return 0;
}
void squares(int size1, int x_offset, int y_offset, int size2) {
  int w = max(size1, x_offset + size2);
  //compute the max of size1 and (x_offset + size2).  Call this w

  int h = max(size1, y_offset + size2);
  //compute the max of size1 and (y_offset + size2).  Call this h

  for (int y = 0; y < h; y++) {
    //count from 0 to h. Call the number you count with y

    for (int x = 0; x < w; x++) {
      //count from 0 to w. Call the number you count with x
      if (is_between(x_offset, y_offset, size1, size2, x, y) == 1) {
        printf("*");
      }
      else {
        if (is_less(size1, size2, x, y) == 1) {
          printf("#");
        }
        else
          printf(" ");
      }
      //check if  EITHER

      //    ((x is between x_offset  and x_offset +size2) AND
      //     y is equal to either y_offset OR y_offset + size2 - 1 )
      //  OR
      //    ((y is between y_offset and y_offset + size2) AND
      //     x is equal to either x_offset OR x_offset + size2 -1)
      // if so, print a *

      //if not,
      // check if EITHER
      //    x is less than size1 AND (y is either 0 or size1-1)
      // OR
      //    y is less than size1 AND (x is either 0 or size1-1)
      //if so, print a #

      //else print a space
    }
    printf("\n");
    //when you finish counting x from 0 to w,
    //print a newline
  }
}
