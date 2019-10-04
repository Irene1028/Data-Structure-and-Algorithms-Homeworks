#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void iniArray(int * array, int size) {
  for (int i = 0; i < size; i++) {
    array[i] = 0;
  }
}
/*void ptfArray(int * array, int size) {
  for (int i = 0; i < size; i++) {
    printf("array[%d] = %d\n", i, array[i]);
  }
  }*/
void frequency_count(FILE * f, int * array) {
  int c;
  while ((c = fgetc(f)) != EOF) {
    //printf("Get char %d !\n", c);
    if (isalpha(c)) {
      //printf("In fre_cnt: c - 97 = %d\n", c - 97);
      array[c - 97] += 1;
    }
  }
}
int solve_key(int * array, int size) {
  int max = 0;
  int num = 0;
  for (int i = 0; i < size; i++) {
    if (array[i] > max) {
      max = array[i];
      num = i;
    }
  }
  int key = 97 + num - 'e';
  if (key < 0)
    key += 26;
  return key;
}
int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Argc!=2\n");
    return EXIT_FAILURE;
  }

  //int key = 0;  //0<=k<26
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Can not open file!\n");
    return EXIT_FAILURE;
  }
  int array[26];
  iniArray(array, 26);
  //ptfArray(array, 26);
  frequency_count(f, array);
  //ptfArray(array, 26);

  int key = solve_key(array, 26);
  //printf("key is %d\n", key);
  if (key >= 0 && key < 26) {
    fprintf(stdout, "%d\n", key);
  }
  else {
    fprintf(stderr, "This is an invalid key!\n");
  }
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
