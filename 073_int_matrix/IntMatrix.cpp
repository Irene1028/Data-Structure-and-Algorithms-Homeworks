#include "IntMatrix.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {}
IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c) {
  // std::cout << "IntMatrix(r,c) begins\n";
  rows = new IntArray *[r];
  for (int i = 0; i < r; i++) {
    rows[i] = new IntArray(c);
  }
  //std::cout << "IntMatrix(r,c) ends\n";
}
IntMatrix::IntMatrix(const IntMatrix & rhs) {
  //std::cout << "IntMatrix(rhs) begin\n";
  numRows = rhs.numRows;
  numColumns = rhs.numColumns;
  rows = new IntArray *[rhs.numRows];
  for (int i = 0; i < rhs.numRows; i++) {
    rows[i] = new IntArray(rhs.numColumns);
    *rows[i] = *rhs.rows[i];
  }
  //std::cout << "IntMatrix(rhs) end\n";
}
IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  //std::cout << "operator=(rhs) begin\n";
  if (this == &rhs) {
    return *this;
  }
  else {
    for (int i = 0; i < numRows; i++) {
      delete[] rows[i];
    }
    delete[] rows;
    numColumns = rhs.numColumns;
    numRows = rhs.numRows;
    rows = new IntArray *[numRows];
    for (int i = 0; i < numRows; i++) {
      rows[i] = new IntArray(numColumns);
      *rows[i] = *rhs.rows[i];
    }
    //std::cout << "operator=(rhs) ends\n";
    return *this;
  }
}
int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  //std::cout << "operator[](index)const begins\n";
  assert(index >= 0 && index < numRows);
  //std::cout << "index=" << index << "\n";
  return *rows[index];
}
IntArray & IntMatrix::operator[](int index) {
  //std::cout << "operator[](index) begins\n";
  assert(index >= 0 && index < numRows);
  //std::cout << "index=" << index << "\n";
  return *rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  //std::cout << "operator==(rhs) begins\n";
  if (numColumns != rhs.numColumns) {
    return 0;
  }
  if (numRows != rhs.numRows) {
    return 0;
  }
  for (int i = 0; i < numRows; i++) {
    if (*rows[i] != *rhs.rows[i]) {
      return 0;
    }
  }
  //std::cout << "operator==(rhs) ends\n";
  return 1;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  //std::cout << "operator+(rhs) begins\n";
  assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
  IntMatrix result(numRows, numColumns);

  for (int i = 0; i < numRows; i++) {
    IntArray & a = *result.rows[i];
    IntArray & b = *rows[i];
    IntArray & c = *rhs.rows[i];
    //    std::cout << "R succeed\n";
    for (int j = 0; j < numColumns; j++) {
      a[j] = b[j] + c[j];
      //std::cout << "For column=" << j << " succeed\n";
    }
  }
  // std::cout << "operator+(rhs) ends\n";
  return result;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  s << "[ ";
  for (int i = 0; i < rhs.getRows(); i++) {
    if (i != rhs.getRows() - 1) {
      s << rhs[i] << ",\n";
    }
    else {
      s << rhs[i];
    }
  }
  s << " ]";
  return s;
}
