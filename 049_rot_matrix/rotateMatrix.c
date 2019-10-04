#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int iniArray(FILE * f, char (*array)[10]) {
  char a[11];
  //int i = 0;

  int c;
  int i = 0;
  while (i < 10) {
    for (int j = 0; j < 11; j++) {
      if ((c = fgetc(f)) != EOF) {
        a[j] = c;
      }
      else {
        fprintf(stderr, "EOF included!\n");
        exit(EXIT_FAILURE);
      }
    }
    //printf("Line is %s", a);
    char * pch = strchr(a, '\n');
    if (pch == NULL) {
      fprintf(stderr, "This line is too long!\n");
      exit(EXIT_FAILURE);
    }
    else {
      //printf("\n d = %ld\n", pch - a);
      if ((pch - a) != 10) {
        fprintf(stderr, "This line is shor!\n");
        exit(EXIT_FAILURE);
      }
      else {
        for (int j = 0; j < 10; j++) {
          array[i][j] = a[j];
        }
      }
    }
    i++;
  }
  if (fgetc(f) != EOF) {
    fprintf(stderr, "Matrix has more than 10 lines\n");
    exit(EXIT_FAILURE);
  }

  return 0;
}
void ptfArray(char (*array)[10]) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      fprintf(stdout, "%c", array[i][j]);
    }
    fprintf(stdout, "\n");
  }
  return;
}
void rotateMatrix(char (*array)[10]) {
  char b[10][10];
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      b[i][j] = array[i][j];
    }
  }
  //char * p;
  //ptfArray(p);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      array[i][j] = b[9 - j][i];
    }
  }
  return;
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Wrong number of arguments.\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r+");
  if (f == NULL) {
    fprintf(stderr, "Can not open file!\n");
    return EXIT_FAILURE;
  }
  char array[10][10];
  //char * p = array;

  iniArray(f, array);
  //ptfArray(array);
  rotateMatrix(array);  //rotate here
  ptfArray(array);
  if (fclose(f) != 0) {
    fprintf(stderr, "can not close input file!\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
