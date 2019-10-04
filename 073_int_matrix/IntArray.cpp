#include "IntArray.h"

#include <assert.h>

#include <iostream>
#include <ostream>
IntArray::IntArray() : data(NULL), numElements(0) {}
IntArray::IntArray(int n) : data(new int[n]), numElements(n) {}

IntArray::IntArray(const IntArray & rhs) {
  data = new int[rhs.numElements];
  numElements = rhs.numElements;
  for (int i = 0; i < numElements; i++) {
    data[i] = rhs.data[i];
  }
}
IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this == &rhs) {
    return *this;
  }
  else {
    delete[] data;
    data = new int[rhs.numElements];
    numElements = rhs.numElements;
    for (int i = 0; i < numElements; i++) {
      data[i] = rhs.data[i];
    }
    return *this;
  }
}
const int & IntArray::operator[](int index) const {
  // std::cout << "now index const=" << index;
  assert(index >= 0 && index < numElements);
  return data[index];
}
int & IntArray::operator[](int index) {
  //std::cout << "now index =" << index << "\n";
  //std::cout << "now numElements=" << numElements << "\n";
  assert((index >= 0) && (index < numElements));
  return data[index];
}

int IntArray::size() const {
  return numElements;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if (numElements != rhs.numElements) {
    return 0;
  }
  for (int i = 0; i < numElements; i++) {
    if (data[i] != rhs.data[i]) {
      return 0;
    }
  }
  return 1;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  if (numElements != rhs.numElements) {
    return 1;
  }
  for (int i = 0; i < numElements; i++) {
    if (data[i] != rhs.data[i]) {
      return 1;
    }
  }
  return 0;
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  s << "{";
  for (int i = 0; i < rhs.size(); i++) {
    if (i == rhs.size() - 1) {
      s << rhs[i];
    }
    else {
      s << rhs[i] << ", ";
    }
  }
  s << "}";
  return s;
}
