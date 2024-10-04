#ifndef CPP1_S21_MATRIXPLUS_1_S21_MATRIX_OOP_H
#define CPP1_S21_MATRIXPLUS_1_S21_MATRIX_OOP_H

#include <cmath>
#include <iostream>

#define SIZE_MSG "Matrix size must be greater or equal to zero"
#define CORRESPOND_MSG "Matrices sizes don't correspond"
#define SQUARE_MSG "Matrix is not square"
#define NULL_DET_MSG "Matrix's determinant is zero"
#define EMPTY_MSG "Matrix is empty"

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_;
  void RemoveMatrix();
  void CopyMatrix(const S21Matrix& other);
  void GetCofact(S21Matrix& other, int p, int q) const;
  double GetDeterminant();
  [[nodiscard]] bool CheckMatrix() const;

 public:
  [[nodiscard]] int rows() const;
  [[nodiscard]] int cols() const;
  [[nodiscard]] double** matrix() const;
  void set_rows(int rows);
  void set_cols(int cols);

  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const double num);
  S21Matrix operator*(const S21Matrix& other);
  bool operator==(const S21Matrix& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix operator+=(const S21Matrix& other);
  S21Matrix operator-=(const S21Matrix& other);
  S21Matrix operator*=(const double num);
  S21Matrix operator*=(const S21Matrix& other);

  double& operator()(int i, int j);
  double& operator()(int i, int j) const;
};

#endif  // CPP1_S21_MATRIXPLUS_1_S21_MATRIX_OOP_H
