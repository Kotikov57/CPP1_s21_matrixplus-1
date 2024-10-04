#include "s21_matrix_oop.h"

#include <iostream>

int S21Matrix::rows() const { return rows_; }
int S21Matrix::cols() const { return cols_; }
double **S21Matrix::matrix() const { return matrix_; }

void S21Matrix::set_rows(int rows) {
  if (rows < 0) throw std::length_error(SIZE_MSG);
  S21Matrix tmp(rows, cols_);
  for (int i = 0; i < (rows > rows_ ? rows_ : rows); i++)
    for (int j = 0; j < cols_; j++) tmp.matrix_[i][j] = matrix_[i][j];
  *this = tmp;
}

void S21Matrix::set_cols(int cols) {
  if (cols < 0) throw std::length_error(SIZE_MSG);

  S21Matrix tmp(rows_, cols);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < (cols > cols_ ? cols_ : cols); j++)
      tmp.matrix_[i][j] = matrix_[i][j];
  *this = tmp;
}

bool S21Matrix::CheckMatrix() const {
  if (matrix_ == nullptr || rows_ < 1 || cols_ < 1) return false;
  return true;
}

void S21Matrix::RemoveMatrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) delete[] matrix_[i];
    delete[] matrix_;

    matrix_ = nullptr;
    rows_ = 0;
    cols_ = 0;
  }
}

void S21Matrix::CopyMatrix(const S21Matrix &other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; i++) matrix_[i] = new double[cols_]();

  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] = other.matrix_[i][j];
}

S21Matrix::S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows < 0 || cols < 0) throw std::length_error(SIZE_MSG);
  rows_ = rows;
  cols_ = cols;
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; i++) matrix_[i] = new double[cols_]();
}

S21Matrix::S21Matrix(const S21Matrix &other) { CopyMatrix(other); }

S21Matrix::S21Matrix(S21Matrix &&other) noexcept {
  CopyMatrix(other);
  other.RemoveMatrix();
}

S21Matrix::~S21Matrix() { RemoveMatrix(); }

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  if (!CheckMatrix() || !other.CheckMatrix()) throw std::logic_error(EMPTY_MSG);
  if (rows_ != other.rows_ || cols_ != other.cols_) return false;
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++)
      if (round(matrix_[i][j] * pow(10, 6)) !=
          round(other.matrix_[i][j] * pow(10, 6)))
        return false;
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (!CheckMatrix() || !other.CheckMatrix()) throw std::logic_error(EMPTY_MSG);
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::logic_error(CORRESPOND_MSG);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] += other.matrix_[i][j];
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (!CheckMatrix() || !other.CheckMatrix()) throw std::logic_error(EMPTY_MSG);
  if (rows_ != other.rows_ || cols_ != other.cols_)
    throw std::logic_error(CORRESPOND_MSG);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] -= other.matrix_[i][j];
}

void S21Matrix::MulNumber(const double num) {
  if (!CheckMatrix()) throw std::logic_error(EMPTY_MSG);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) matrix_[i][j] *= num;
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (!CheckMatrix() || !other.CheckMatrix()) throw std::logic_error(EMPTY_MSG);
  if (cols_ != other.rows_) throw std::logic_error(CORRESPOND_MSG);
  S21Matrix res(rows_, other.cols_);
  for (int i = 0; i < res.rows_; i++)
    for (int j = 0; j < res.cols_; j++)
      for (int k = 0; k < cols_; k++)
        res(i, j) += matrix_[i][k] * other.matrix_[k][j];
  *this = res;
}

S21Matrix S21Matrix::Transpose() {
  if (!CheckMatrix()) throw std::logic_error(EMPTY_MSG);
  S21Matrix res(cols_, rows_);
  for (int i = 0; i < rows_; i++)
    for (int j = 0; j < cols_; j++) res(j, i) = matrix_[i][j];
  return res;
}

void S21Matrix::GetCofact(S21Matrix &other, int p, int q) const {
  int m = 0, n = 0;
  for (int i = 0; i < rows_; i++) {
    if (i == p) continue;
    m = 0;
    for (int j = 0; j < cols_; j++) {
      if (j == q) continue;
      other(n, m) = matrix_[i][j];
      m++;
    }
    n++;
  }
}

double S21Matrix::GetDeterminant() {
  if (rows_ == 1) return matrix_[0][0];
  S21Matrix tmp(rows_ - 1, cols_ - 1);
  int sign = 1;
  double res = 0;
  for (int i = 0; i < rows_; i++) {
    GetCofact(tmp, 0, i);
    res += sign * matrix_[0][i] * tmp.GetDeterminant();
    sign *= -1;
  }
  return res;
}

S21Matrix S21Matrix::CalcComplements() {
  if (!CheckMatrix()) throw std::logic_error(EMPTY_MSG);
  if (rows_ != cols_) throw std::logic_error(SQUARE_MSG);
  S21Matrix res(rows_, cols_);
  if (rows_ == 1)
    res(0, 0) = matrix_[0][0];
  else {
    for (int i = 0; i < rows_; i++)
      for (int j = 0; j < cols_; j++) {
        S21Matrix minor(rows_ - 1, cols_ - 1);
        GetCofact(minor, i, j);
        res(i, j) = pow(-1., i + j) * minor.GetDeterminant();
      }
  }
  return res;
}

double S21Matrix::Determinant() {
  if (!CheckMatrix()) throw std::logic_error(EMPTY_MSG);
  if (rows_ != cols_) throw std::logic_error(SQUARE_MSG);
  return GetDeterminant();
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();
  if (det == 0) throw std::logic_error(NULL_DET_MSG);
  S21Matrix tmp = CalcComplements();
  if (rows_ == 1)
    tmp(0, 0) = 1 / det;
  else {
    tmp = tmp.Transpose();
    tmp.MulNumber(1 / det);
  }
  return tmp;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix res(*this);
  res.MulNumber(num);
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix res(*this);
  res.MulMatrix(other);
  return res;
}

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  S21Matrix tmp(other);
  RemoveMatrix();
  CopyMatrix(tmp);
  return *this;
}

S21Matrix S21Matrix::operator+=(const S21Matrix &other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix &other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix &other) {
  this->MulMatrix(other);
  return *this;
}

double &S21Matrix::operator()(int i, int j) {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0)
    throw std::length_error("Indices outside the range");
  return matrix_[i][j];
}

double &S21Matrix::operator()(int i, int j) const {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0)
    throw std::length_error("Indices outside the range");
  return matrix_[i][j];
}