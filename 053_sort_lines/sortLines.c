#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  //printf("In Sort Data:\n");
  qsort(data, count, sizeof(char *), stringOrder);
  //printf("Finish Sorting!\n");
}

char ** read_data(size_t * i, FILE * f) {
  char ** lines = NULL;
  char * single_line = NULL;
  size_t len = 5;
  //printf("In reading:\n");
  while (getline(&single_line, &len, f) >= 0) {
    lines = realloc(lines, (*i + 1) * sizeof(*lines));

    lines[*i] = single_line;
    single_line = NULL;
    //printf("%s", lines[*i]);
    (*i)++;
  }
  //printf("Loop stops!\n");
  free(single_line);  //
  return lines;
}

void ptf_result(char ** lines, size_t size) {
  //printf("In Print Func:\n");
  for (size_t i = 0; i < size; i++) {
    printf("%s", lines[i]);
  }
}
int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  char ** lines = NULL;
  size_t lines_len = 0;
  if (argc == 1) {
    lines = read_data(&lines_len, stdin);
    //printf("Back to main:\n");
    sortData(lines, lines_len);
    //printf("Finish Sorting!\n");
    sortData(lines, lines_len);
    ptf_result(lines, lines_len);
    for (size_t j = 0; j < lines_len; j++) {
      free(lines[j]);
    }
    free(lines);
  }
  else if (argc > 1) {
    for (int i = 0; i < argc - 1; i++) {
      FILE * f = fopen(argv[i + 1], "r");
      if (f == NULL) {
        fprintf(stderr, "Can not open the file!\n");
        exit(EXIT_FAILURE);
      }
      else {
        lines = read_data(&lines_len, f);
        sortData(lines, lines_len);
        ptf_result(lines, lines_len);
        for (size_t j = 0; j < lines_len; j++) {
          free(lines[j]);
        }
        free(lines);
        if (fclose(f) != 0) {
          fprintf(stderr, "Can not close file!\n");
          exit(EXIT_FAILURE);
        }
        lines_len = 0;
      }
    }
  }

  return EXIT_SUCCESS;
}
