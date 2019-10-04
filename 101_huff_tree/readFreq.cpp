#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  uint64_t * freq_ary = new uint64_t[257]();
  for (int i = 0; i < 257; i++) {
    freq_ary[i] = 0;
  }
  std::ifstream fs(fname);
  if (!fs.good()) {
    std::cerr << "Can not open file.\n";
    exit(EXIT_FAILURE);
  }
  char c;
  while ((c = fs.get()) != EOF) {
    freq_ary[(unsigned char)c]++;
  }
  freq_ary[256] = 1;
  fs.close();
  return freq_ary;
}
