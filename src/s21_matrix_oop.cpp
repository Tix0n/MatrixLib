#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : rows_(1), cols_(1), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("Invalid size of matrix");
  }
  allocateMatrix();
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  allocateMatrix();
  copyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() { clearMatrix(); }

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  bool result = true;
  if ((*this).getRows() != other.getRows() ||
      (*this).getCols() != other.getCols()) {
    result = false;
  } else {
    for (int i = 0; result != false && i < (*this).getRows(); i++)
      for (int j = 0; result != false && j < (*this).getCols(); j++)
        if (fabs((*this)(i, j) - other(i, j)) > EPS) result = false;
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if ((*this).getRows() != other.getRows() ||
      (*this).getCols() != other.getCols()) {
    throw std::invalid_argument("Different dimension of matrices");
  }

  for (int i = 0; i < (*this).getRows(); i++)
    for (int j = 0; j < (*this).getCols(); j++) (*this)(i, j) += other(i, j);
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if ((*this).getRows() != other.getRows() ||
      (*this).getCols() != other.getCols()) {
    throw std::invalid_argument("Different dimension of matrices");
  }

  for (int i = 0; i < (*this).getRows(); i++)
    for (int j = 0; j < (*this).getCols(); j++) (*this)(i, j) -= other(i, j);
}

void S21Matrix::MulNumber(const double multiplier) {
  for (int i = 0; i < (*this).getRows(); i++)
    for (int j = 0; j < (*this).getCols(); j++) (*this)(i, j) *= multiplier;
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if ((*this).getCols() != other.getRows()) {
    throw std::invalid_argument(
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix");
  }
  int new_rows = (*this).getRows();
  int new_cols = other.getCols();
  S21Matrix result_matrix = S21Matrix(new_rows, new_cols);
  for (int i = 0; i < new_rows; i++)
    for (int j = 0; j < new_cols; j++)
      for (int k = 0; k < (*this).getCols(); k++)
        result_matrix(i, j) += (*this)(i, k) * other(k, j);
  (*this) = result_matrix;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result_matrix = S21Matrix((*this).getCols(), (*this).getRows());
  for (int i = 0; i < (*this).getRows(); i++)
    for (int j = 0; j < (*this).getCols(); j++)
      result_matrix(j, i) = (*this)(i, j);
  return result_matrix;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (getRows() != getCols())
    throw std::invalid_argument("The matrix is not square");

  if ((*this).getRows() == 1 && (*this).getCols() == 1) {
    if (fabs((*this)(0, 0)) < EPS) {
      throw std::logic_error(
          "A first-order null matrix does not have an algebraic complement "
          "matrix");
    }
  }
  S21Matrix result_matrix = S21Matrix((*this).getRows(), (*this).getCols());
  if ((*this).getRows() == 1 && fabs((*this)(0, 0)) > EPS) {
    result_matrix(0, 0) = 1.;
  } else {
    for (int i = 0; i < (*this).getRows(); i++) {
      for (int j = 0; j < (*this).getCols(); j++) {
        S21Matrix minor_matrix = Minor(*this, i, j);
        result_matrix(i, j) = minor_matrix.Determinant() * pow(-1, i + j);
      }
    }
  }
  return result_matrix;
}

double S21Matrix::Determinant() const {
  if (getRows() != getCols())
    throw std::invalid_argument("The matrix is not square");

  double determinant = 0.0;
  if (getRows() == 1) {
    determinant = (*this)(0, 0);
  } else if (getRows() == 2) {
    determinant = (*this)(0, 0) * (*this)(1, 1) - (*this)(1, 0) * (*this)(0, 1);
  } else {
    for (int i = 0; i < getCols(); i++) {
      S21Matrix temp_matrix = Minor(*this, 0, i);
      determinant += (*this)(0, i) * pow(-1, i) * temp_matrix.Determinant();
    }
  }
  return determinant;
}

S21Matrix S21Matrix::InverseMatrix() const {
  double determinant = Determinant();
  if (fabs(determinant) < EPS)
    throw std::invalid_argument("The determinant of the matrix is 0");

  S21Matrix result_matrix = S21Matrix((*this).getRows(), (*this).getCols());

  S21Matrix complements_matrix = CalcComplements();
  S21Matrix transpose_complements_matrix = complements_matrix.Transpose();
  transpose_complements_matrix.MulNumber(1. / determinant);
  result_matrix = transpose_complements_matrix;

  return result_matrix;
}

S21Matrix S21Matrix::Minor(const S21Matrix& other, int row, int col) const {
  S21Matrix result_matrix(other.getRows() - 1, other.getCols() - 1);
  int minor_row = 0;
  int minor_col = 0;
  for (int i = 0; i < other.getRows(); i++) {
    if (i != row) {
      for (int j = 0; j < other.getCols(); j++) {
        if (j != col) {
          result_matrix(minor_row, minor_col) = other(i, j);
          minor_col++;
        }
      }
      minor_row++;
      minor_col = 0;
    }
  }
  return result_matrix;
}

void S21Matrix::setRows(int rows) {
  if (rows < 1) {
    std::invalid_argument("The number of rows cannot be less than 1");
  }
  S21Matrix result_matrix = S21Matrix(rows, (*this).getCols());
  result_matrix.copyMatrix(*this);
  *this = result_matrix;
}

int S21Matrix::getRows() const { return rows_; }

void S21Matrix::setCols(int cols) {
  if (cols < 1) {
    std::invalid_argument("The number of cols cannot be less than 1");
  }
  S21Matrix result_matrix = S21Matrix((*this).getRows(), cols);
  result_matrix.copyMatrix(*this);
  *this = result_matrix;
}

int S21Matrix::getCols() const { return cols_; }

double& S21Matrix::operator()(int rows, int cols) {
  if (rows >= (*this).getRows() || cols >= (*this).getCols() || rows < 0 ||
      cols < 0) {
    throw std::invalid_argument("Index out of range");
  }
  return matrix_[rows][cols];
}

const double& S21Matrix::operator()(int rows, int cols) const {
  if (rows >= (*this).getRows() || cols >= (*this).getCols() || rows < 0 ||
      cols < 0) {
    throw std::invalid_argument("Index out of range");
  }
  return matrix_[rows][cols];
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (!(this == &other)) {
    clearMatrix();
    rows_ = other.getRows();
    cols_ = other.getCols();
    allocateMatrix();
    copyMatrix(other);
  }
  return *this;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix result_matrix(*this);
  result_matrix.SumMatrix(other);
  return result_matrix;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix result_matrix(*this);
  result_matrix.SubMatrix(other);
  return result_matrix;
}

S21Matrix S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return (*this);
}

S21Matrix S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return (*this);
}

S21Matrix S21Matrix::operator*(const double multiplier) const {
  S21Matrix result_matrix(*this);
  result_matrix.MulNumber(multiplier);
  return result_matrix;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix result_matrix(*this);
  result_matrix.MulMatrix(other);
  return result_matrix;
}

S21Matrix S21Matrix::operator*=(const double multiplier) {
  MulNumber(multiplier);
  return (*this);
}

S21Matrix S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return (*this);
}

void S21Matrix::copyMatrix(const S21Matrix& other) {
  int copy_rows = other.getRows();
  int copy_cols = other.getCols();
  if (copy_rows > (*this).getRows()) copy_rows = (*this).getRows();
  if (copy_cols > (*this).getCols()) copy_cols = (*this).getCols();
  for (int i = 0; i < copy_rows; i++)
    for (int j = 0; j < copy_cols; j++) (*this)(i, j) = other(i, j);
}

void S21Matrix::allocateMatrix() {
  matrix_ = new double*[(*this).getRows()]();
  for (int i = 0; i < (*this).getRows(); i++) {
    matrix_[i] = new double[(*this).getCols()]();
  }
}

void S21Matrix::clearMatrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < (*this).getRows(); i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = 0;
  cols_ = 0;
}
