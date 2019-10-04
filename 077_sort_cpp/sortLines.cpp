#include <algorithm>
#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <vector>
void sortFuc(std::istream & s) {
  std::string line;
  std::vector<std::string> lines;

  while (getline(s, line)) {
    lines.push_back(line);
  }
  /*if (!s.eof() && !s) {
    std::cerr << "Wrong input!" << std::endl;
    exit(EXIT_FAILURE);
    }*/
  std::sort(lines.begin(), lines.end());

  for (typename std::vector<std::string>::const_iterator it = lines.begin(); it != lines.end();
       ++it) {
    std::cout << *it << std::endl;
  }
}
int main(int argc, char ** argv) {
  if (argc < 2) {
    sortFuc(std::cin);
  }
  else {
    for (int i = 1; i < argc; i++) {
      std::ifstream flines(argv[i]);
      if (!flines) {
        std::cerr << "cannot open " << argv[i] << std::endl;
        exit(EXIT_FAILURE);
      }
      sortFuc(flines);
    }
  }

  return 0;
}
