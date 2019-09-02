#include "My_matrix.h"
#include <stdexcept>

/*
Implementation of the clas My_matrix
*/


My_matrix::My_matrix()
{
  n = m = 0;
  ptr = 0;
}

void My_matrix::allocate_memory()
{
  ptr = new int*[n];
  for (int i = 0; i < n; i++) {
    ptr[i] = new int[m];
    for (int j = 0; j < m; j++) {
      ptr[i][j] = 0;
    }
  }
}

My_matrix::My_matrix(int n1, int m1)
{
  if (n1 <= 0 || m1 <= 0) throw invalid_input();
  n = n1;
  m = m1;
  allocate_memory();
}

My_matrix::My_matrix(const My_matrix& mat)
{
  ptr = 0;
  *this = mat;
}

// move constructor (optional)
My_matrix::My_matrix(My_matrix&& mat)
{
  ptr = 0;
  *this = mat;
} 

My_matrix::~My_matrix()
{
  if (ptr != 0) {
    for (int i = 0; i < n; i++) {
      delete[] ptr[i];
    }
    delete[] ptr;
  }
}

My_matrix& My_matrix::operator=(const My_matrix& mat)
{
  if (ptr != 0) { // release the current memory
    for (int i = 0; i < n; i++) {
      delete[] ptr[i];
    }
    delete[] ptr;
  }

  // copy from mat
  n = mat.n;
  m = mat.m;
  allocate_memory();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      ptr[i][j] = mat.ptr[i][j];
    }
  }

  return *this;
}

// move assignment operator (optional)
My_matrix& My_matrix::operator=(My_matrix&& mat)
{
  if (ptr != 0) { // release the current memory
    for (int i = 0; i < n; i++) {
      delete[] ptr[i];
    }
    delete[] ptr;
  }

  
  n = mat.n;
  m = mat.m;
  allocate_memory();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      ptr[i][j] = mat.ptr[i][j];
    }
  }
} 

int My_matrix::number_of_rows() const
{
  return n;
}

int My_matrix::number_of_columns() const
{
  return m;
}

int* My_matrix::operator()(int i) const
{
  return ptr[i];
}

int My_matrix::operator()(int i, int j) const
{
  return ptr[i][j];
}

int& My_matrix::operator()(int i, int j)
{
  return ptr[i][j];
}

int My_matrix::elem(int i, int j) const
{
  if (i < 0 || i >= n) throw out_of_range("Out of range");
  if (j < 0 || j >= m) throw out_of_range("Out of range");
  return ptr[i][j];
}

int& My_matrix::elem(int i, int j)
{
  if (i < 0 || i >= n) throw out_of_range("Out of range");
  if (j < 0 || j >= m) throw out_of_range("Out of range");
  return ptr[i][j];
}

ostream& operator<<(ostream& out, const My_matrix& mat)
{
  for (int i = 0; i < mat.number_of_rows(); i++) {
    for (int j = 0; j < mat.number_of_columns(); j++) {
      out << mat.elem(i, j) << "\t";
    }
    out << endl;
  }
  return out;
}

istream& operator>>(istream& in, My_matrix& mat)
{
  int n, m;

  // load the size of the matrix
  if (!(in >> n >> m)) {
    throw invalid_input();
  }

  // read the content of this matrix
  My_matrix rst(n, m);
  for (int i = 0; i < rst.number_of_rows(); i++) {
    for (int j = 0; j < rst.number_of_columns(); j++) {
      if (!(in >> rst(i, j))) {
        throw invalid_input();
      }
    }
  }

  mat = rst;
  return in;
}

My_matrix operator+(const My_matrix& mat1, const My_matrix& mat2)
{
  // make sure the matrices are compatible
  if (mat1.number_of_rows() != mat2.number_of_rows() ||
      mat1.number_of_columns() != mat2.number_of_columns()) {
    throw incompatible_matrices();
  }

  // add each pair of elements in the matrices
  My_matrix rst(mat1.number_of_rows(), mat1.number_of_columns());
  for (int i = 0; i < rst.number_of_rows(); i++) {
    for (int j = 0; j < rst.number_of_columns(); j++) {
      rst(i, j) = mat1(i, j) + mat2(i, j);
    }
  }

  return rst;
}

My_matrix operator*(const My_matrix& mat1, const My_matrix& mat2)
{
  // make sure the matrices are compatible
  if (mat1.number_of_columns() != mat2.number_of_rows()) {
    throw incompatible_matrices();
  }

  My_matrix rst(mat1.number_of_rows(), mat2.number_of_columns());
  for (int i = 0; i < rst.number_of_rows(); i++) {
    for (int j = 0; j < rst.number_of_columns(); j++) {
      // sum of the cross products
      for (int k = 0; k < mat1.number_of_columns(); k++) {
        rst(i, j) += mat1(i, k) * mat2(k, j);
      }
    }
  }

  return rst;
}

