#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <queue>

#include "node.h"
#include "readFreq.h"

void writeHeader(BitFileWriter * bfw, const std::map<unsigned, BitString> & theMap) {
  for (int i = 0; i < 257; i++) {
    std::map<unsigned, BitString>::const_iterator it = theMap.find(i);
    if (it != theMap.end()) {
      bfw->writeByte(it->second.size());
      bfw->writeBitString(it->second);
    }
    else {
      bfw->writeByte(0);
    }
  }
}

void writeCompressedOutput(const char * inFile,
                           const char * outFile,
                           const std::map<unsigned, BitString> & theMap) {
  BitFileWriter bfw(outFile);
  writeHeader(&bfw, theMap);

  //WRITE YOUR CODE HERE!
  //open the input file for reading
  std::ifstream input(inFile);
  if (!input.good()) {
    std::cerr << "Can not open the file!\n";
    exit(EXIT_FAILURE);
  }
  char c;
  std::map<unsigned, BitString>::const_iterator it;
  //You need to read the input file, lookup the characters in the map,
  while ((c = input.get()) != EOF) {
    //    std::cout << "In write output's while, c=" << c << std::endl;
    it = theMap.find((unsigned char)c);
    assert(it != theMap.end());
    bfw.writeBitString(it->second);
    //and write the proper bit string with the BitFileWriter
  }
  //dont forget to lookup 256 for the EOF marker, and write it out.
  it = theMap.find(256);
  bfw.writeBitString(it->second);
  //BitFileWriter will close the output file in its destructor
  //but you probably need to close your input file.
  input.close();
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr, "Usage: compress input output\n");
    return EXIT_FAILURE;
  }
  //WRITE YOUR CODE HERE
  //Implement main
  //hint 1: most of the work is already done.
  //hint 2: you can look at the main from the previous tester for 90% of this
  std::cout << "NOw we read freq\n";
  uint64_t * freq_array(readFrequencies(argv[1]));
  assert(freq_array != NULL);
  std::cout << "Now begin build tree\n";
  Node * myTree(buildTree(freq_array));
  std::map<unsigned, BitString> theMap;
  BitString b;
  //
  std::cout << "Now begin build Map\n";
  myTree->buildMap(b, theMap);
  std::cout << "Now begin write output\n";
  writeCompressedOutput(argv[1], argv[2], theMap);
  delete[] freq_array;
  delete myTree;
  return EXIT_SUCCESS;
}
