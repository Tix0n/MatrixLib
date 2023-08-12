#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <iostream>
#include <stdexcept>

#define EPS 1e-6

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  bool operator==(const S21Matrix& other) const;
  S21Matrix& operator=(const S21Matrix& other);

  double& operator()(int i, int j);
  const double& operator()(int rows, int cols) const;

  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator+=(const S21Matrix& other);
  S21Matrix operator-=(const S21Matrix& other);

  S21Matrix operator*(const double multiplier) const;
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*=(const double multiplier);
  S21Matrix operator*=(const S21Matrix& other);

  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double multiplier);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  void setRows(int rows);
  int getRows() const;
  void setCols(int cols);
  int getCols() const;

 private:
  int rows_, cols_;
  double** matrix_;

  void allocateMatrix();
  void clearMatrix();
  void copyMatrix(const S21Matrix& other);
  S21Matrix Minor(const S21Matrix& other, int row, int col) const;
};

#endif  // SRC_S21_MATRIX_OOP_H_
