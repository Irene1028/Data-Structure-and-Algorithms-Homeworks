#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

template<typename T>
class Matrix
{
 private:
  int Rows;
  int Cols;
  std::vector<std::vector<T> > rows;

 public:
  Matrix() : Rows(0), Cols(0), rows(0) {}
  Matrix(int r, int c);  // : Rows(r), Cols(c) {}
  Matrix(const Matrix<T> & m) : Rows(m.Rows), Cols(m.Cols), rows(m.rows) {}
  //~Matrix() {} //no malloc, no destructor?
  Matrix<T> operator=(const Matrix<T> & m);
  int getRows() const { return Rows; }
  int getColumns() const { return Cols; }
  std::vector<T> & operator[](int index);
  const std::vector<T> & operator[](int index) const;
  bool operator==(const Matrix<T> & m);
  Matrix<T> operator+(const Matrix<T> & m);  //why &?
  template<typename U>
  friend std::ostream & operator<<(std::ostream & s, const Matrix<U> & m);
};

template<typename T>
Matrix<T>::Matrix(int r, int c) : Rows(r), Cols(c), rows(r) {
  for (typename std::vector<std::vector<T> >::iterator it = rows.begin(); it != rows.end(); ++it) {
    it->resize(c, T());
  }
}
template<typename T>
Matrix<T> Matrix<T>::operator=(const Matrix<T> & m) {
  rows = m.rows;
  Rows = m.Rows;
  Cols = m.Cols;
  return *this;
}

template<typename T>
std::vector<T> & Matrix<T>::operator[](int index) {
  assert(index >= 0 && (size_t)index < rows.size());
  return rows[index];
}

template<typename T>
const std::vector<T> & Matrix<T>::operator[](int index) const {
  assert(index >= 0 && (size_t)index < rows.size());
  return rows[index];
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T> & m) {
  return m.Rows == Rows && m.Cols == Cols && m.rows == rows;
}

template<typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> & m) {
  assert(Rows == m.Rows && Cols == m.Cols);
  Matrix<T> result(Rows, Cols);

  typename std::vector<std::vector<T> >::iterator it;  //why typename here?
  typename std::vector<std::vector<T> >::const_iterator x = rows.begin();
  typename std::vector<std::vector<T> >::const_iterator y = m.rows.begin();
  for (it = result.rows.begin(); it != result.rows.end(); ++it, ++x, ++y) {
    typename std::vector<T>::iterator itt;
    typename std::vector<T>::const_iterator ix = x->begin();
    typename std::vector<T>::const_iterator iy = y->begin();
    for (itt = it->begin(); itt != it->end(); ++itt, ++ix, ++iy) {
      *itt = *ix + *iy;
    }
  }
  return result;
}

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & m) {
  s << "[ ";
  for (typename std::vector<std::vector<T> >::const_iterator it = m.rows.begin();
       it != m.rows.end();
       ++it) {  //rows call begin or end()
    if (it != m.rows.begin()) {
      s << ",\n{";
    }
    else {
      s << "{";
    }
    for (typename std::vector<T>::const_iterator itt = it->begin(); itt != it->end(); ++itt) {
      if (itt != it->begin()) {
        s << ",";
      }
      s << *itt;
    }
    s << "}";
  }
  s << " ]";
  return s;
}
//YOUR CODE GOES HERE!

#endif
