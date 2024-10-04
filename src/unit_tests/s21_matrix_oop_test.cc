#include "../s21_matrix_oop.h"

#include <gtest/gtest.h>

TEST(S21MatrixTest, RowsSetter) {
  S21Matrix A(2, 2);
  int rows = 12;
  A.set_rows(rows);
  ASSERT_EQ(A.rows(), rows);
  rows = 5;
  A.set_rows(rows);
  ASSERT_EQ(A.rows(), rows);

  // Incorrect data
  ASSERT_THROW(A.set_rows(-2), std::length_error);
}

TEST(S21MatrixTest, ColsSetter) {
  S21Matrix A(2, 2);
  int cols = 12;
  A.set_cols(cols);
  ASSERT_EQ(A.cols(), cols);
  cols = 5;
  A.set_cols(cols);
  ASSERT_EQ(A.cols(), cols);

  // Incorrect data
  ASSERT_THROW(A.set_cols(-2), std::length_error);
}

TEST(S21MatrixTest, EmptyConstructor) {
  S21Matrix A;
  EXPECT_EQ(A.rows(), 0);
  EXPECT_EQ(A.cols(), 0);
  EXPECT_EQ(A.matrix(), nullptr);
}

TEST(S21MatrixTest, SizedConstructor) {
  srand(time(nullptr));
  int rows = rand() % 100 + 1, cols = rand() % 100 + 1;
  S21Matrix A(rows, cols);
  EXPECT_EQ(A.rows(), rows);
  EXPECT_EQ(A.cols(), cols);
  ASSERT_NE(A.matrix(), nullptr);
  for (int i = 0; i < A.rows(); i++)
    for (int j = 0; j < A.cols(); j++) EXPECT_EQ(A.matrix()[i][j], 0);

  // Incorrect sizes
  EXPECT_THROW(S21Matrix B(-1, 2), std::length_error);
  EXPECT_THROW(S21Matrix C(0, -2), std::length_error);
}

TEST(S21MatrixTest, CopyConstructor) {
  srand(time(nullptr));
  int rows = rand() % 100 + 1, cols = rand() % 100 + 1;
  S21Matrix A(rows, cols), exp(rows, cols);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      double a = (double)rand() / rand();
      A(i, j) = a;
      exp(i, j) = a;
    }
  S21Matrix B(A);
  EXPECT_EQ(B.rows(), exp.rows());
  EXPECT_EQ(B.cols(), exp.cols());
  ASSERT_NE(B.matrix(), nullptr);
  for (int i = 0; i < exp.rows(); i++)
    for (int j = 0; j < exp.cols(); j++)
      EXPECT_EQ(B.matrix()[i][j], exp.matrix()[i][j]);
}

TEST(S21MatrixTest, MoveConstructor) {
  srand(time(nullptr));
  int rows = rand() % 100 + 1, cols = rand() % 100 + 1;
  S21Matrix A(rows, cols), exp(rows, cols);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      double a = (double)rand() / rand();
      A(i, j) = a;
      exp(i, j) = a;
    }
  S21Matrix B(std::move(A));
  EXPECT_EQ(B.rows(), exp.rows());
  EXPECT_EQ(B.cols(), exp.cols());
  ASSERT_NE(B.matrix(), nullptr);
  for (int i = 0; i < exp.rows(); i++)
    for (int j = 0; j < exp.cols(); j++)
      EXPECT_EQ(B.matrix()[i][j], exp.matrix()[i][j]);

  EXPECT_EQ(A.rows(), 0);
  EXPECT_EQ(A.cols(), 0);
  EXPECT_EQ(A.matrix(), nullptr);
}

TEST(S21MatrixTest, EqMatrix) {
  srand(time(nullptr));
  int rows = rand() % 100 + 1, cols = rand() % 100 + 1;
  S21Matrix A(rows, cols), B(rows, cols);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      double a = (double)rand() / rand();
      A(i, j) = a;
      B(i, j) = a;
    }
  EXPECT_TRUE(A.EqMatrix(B));
  EXPECT_TRUE(B.EqMatrix(A));
  A(0, 0) = A(0, 0) + 1;
  EXPECT_FALSE(A.EqMatrix(B));
  EXPECT_FALSE(B.EqMatrix(A));
}

TEST(S21MatrixTest, SumMatrix) {
  srand(time(nullptr));
  int rows = rand() % 100 + 1, cols = rand() % 100 + 1;
  S21Matrix A(rows, cols), B(rows, cols), C(rows + 1, cols), exp(rows, cols);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      double a = (double)rand() / rand(), b = (double)rand() / rand();
      A(i, j) = a;
      B(i, j) = b;
      exp(i, j) = a + b;
    }
  A.SumMatrix(B);
  EXPECT_TRUE(A.EqMatrix(exp));

  EXPECT_THROW(A.SumMatrix(C), std::logic_error);
}

TEST(S21MatrixTest, SubMatrix) {
  srand(time(nullptr));
  int rows = rand() % 100 + 1, cols = rand() % 100 + 1;
  S21Matrix A(rows, cols), B(rows, cols), C(rows + 1, cols), exp(rows, cols);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      double a = (double)rand() / rand(), b = (double)rand() / rand();
      A(i, j) = a;
      B(i, j) = b;
      exp(i, j) = a - b;
    }
  A.SubMatrix(B);
  EXPECT_TRUE(A.EqMatrix(exp));

  EXPECT_THROW(A.SubMatrix(C), std::logic_error);
}

TEST(S21MatrixTest, MulNumber) {
  srand(time(nullptr));
  int rows = rand() % 100 + 1, cols = rand() % 100 + 1;
  double num = (double)rand() / rand();
  S21Matrix A(rows, cols), exp(rows, cols);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      double a = (double)rand() / rand();
      A(i, j) = a;
      exp(i, j) = a * num;
    }
  A.MulNumber(num);
  EXPECT_TRUE(A.EqMatrix(exp));
}

TEST(S21MatrixTest, MulMatrix) {
  srand(time(nullptr));
  int m = rand() % 100 + 1, k = rand() % 100 + 1, n = rand() % 100 + 1;
  S21Matrix A(m, k), B(k, n), C(m, n), exp(m, n);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < k; j++) A(i, j) = (double)rand() / rand();
  for (int i = 0; i < k; i++)
    for (int j = 0; j < n; j++) B(i, j) = (double)rand() / rand();
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++) {
      for (int r = 0; r < k; r++) exp(i, j) += A(i, r) * B(r, j);
    }

  A.MulMatrix(B);
  EXPECT_TRUE(A.EqMatrix(exp));

  EXPECT_THROW(A.MulMatrix(C), std::logic_error);
}

TEST(S21MatrixTest, Transpose) {
  srand(time(nullptr));
  int rows = rand() % 100 + 1, cols = rand() % 100 + 1;
  S21Matrix A(rows, cols), exp(cols, rows);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      double a = (double)rand() / rand();
      A(i, j) = a;
      exp(j, i) = a;
    }
  S21Matrix B = A.Transpose();
  EXPECT_TRUE(B.EqMatrix(exp));
}

TEST(S21MatrixTest, CalcComplements1x1) {
  int rows = 1, cols = 1;
  S21Matrix A(rows, cols), exp(rows, cols);
  A(0, 0) = 5;
  exp(0, 0) = 5;

  S21Matrix B = A.CalcComplements();
  EXPECT_TRUE(B.EqMatrix(exp));
}

TEST(S21MatrixTest, CalcComplements2x2) {
  int rows = 2, cols = 2;
  S21Matrix A(rows, cols), exp(rows, cols);
  A(0, 0) = 1;
  A(0, 1) = 1;
  A(1, 0) = 1;
  A(1, 1) = 3;
  exp(0, 0) = 3;
  exp(0, 1) = -1;
  exp(1, 0) = -1;
  exp(1, 1) = 1;

  S21Matrix B = A.CalcComplements();
  EXPECT_TRUE(B.EqMatrix(exp));
}

TEST(S21MatrixTest, CalcComplements3x3) {
  int rows = 3, cols = 3;
  S21Matrix A(rows, cols), exp(rows, cols);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 0;
  A(1, 1) = 4;
  A(1, 2) = 2;
  A(2, 0) = 5;
  A(2, 1) = 2;
  A(2, 2) = 1;
  exp(0, 0) = 0;
  exp(0, 1) = 10;
  exp(0, 2) = -20;
  exp(1, 0) = 4;
  exp(1, 1) = -14;
  exp(1, 2) = 8;
  exp(2, 0) = -8;
  exp(2, 1) = -2;
  exp(2, 2) = 4;

  S21Matrix B = A.CalcComplements();
  EXPECT_TRUE(B.EqMatrix(exp));
}

TEST(S21MatrixTest, CalcComplementsNotSquare) {
  int rows = 2, cols = 3;
  S21Matrix A(rows, cols);
  EXPECT_THROW(A.CalcComplements(), std::logic_error);
}

TEST(S21MatrixTest, Determinant1x1) {
  int rows = 1, cols = 1;
  S21Matrix A(rows, cols);
  A(0, 0) = 5;
  double exp = 5;

  double res = A.Determinant();
  EXPECT_FLOAT_EQ(res, exp);
}

TEST(S21MatrixTest, Determinant2x2) {
  int rows = 2, cols = 2;
  S21Matrix A(rows, cols);
  A(0, 0) = 0;
  A(0, 1) = 1;
  A(1, 0) = 1;
  A(1, 1) = 0;
  double exp = -1;
  double res = A.Determinant();
  EXPECT_FLOAT_EQ(res, exp);

  A(0, 0) = 0.25;
  A(0, 1) = 1.3333;
  A(1, 0) = -9.36;
  A(1, 1) = 0.001;
  exp = 12.479938;
  res = A.Determinant();
  EXPECT_FLOAT_EQ(res, exp);

  A(0, 0) = 1;
  A(0, 1) = 1;
  A(1, 0) = 1;
  A(1, 1) = 3;
  exp = 2;
  res = A.Determinant();
  EXPECT_FLOAT_EQ(res, exp);

  A(0, 0) = 1;
  A(0, 1) = 1;
  A(1, 0) = 3;
  A(1, 1) = 3;
  exp = 0;
  res = A.Determinant();
  EXPECT_FLOAT_EQ(res, exp);
}

TEST(S21MatrixTest, Determinant3x3) {
  int rows = 3, cols = 3;
  S21Matrix A(rows, cols);
  A(0, 0) = 5;
  A(0, 1) = 4.245;
  A(0, 2) = 39.423;
  A(1, 0) = 8.5;
  A(1, 1) = 54.3;
  A(1, 2) = 5.7;
  A(2, 0) = 78.78;
  A(2, 1) = 78.755;
  A(2, 2) = 0;
  double exp = -142589.767069;
  double res = A.Determinant();
  EXPECT_FLOAT_EQ(res, exp);

  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 4;
  A(1, 1) = 5;
  A(1, 2) = 6;
  A(2, 0) = 7;
  A(2, 1) = 8;
  A(2, 2) = 9;
  exp = 0;
  res = A.Determinant();
  EXPECT_FLOAT_EQ(res, exp);
}

TEST(S21MatrixTest, Determinant4x4) {
  int rows = 4, cols = 4;
  S21Matrix A(rows, cols);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(0, 3) = 4;
  A(1, 0) = 5;
  A(1, 1) = 6;
  A(1, 2) = 7;
  A(1, 3) = 8;
  A(2, 0) = 9;
  A(2, 1) = 10.1;
  A(2, 2) = 11;
  A(2, 3) = 12;
  A(3, 0) = 13;
  A(3, 1) = 14;
  A(3, 2) = -15;
  A(3, 3) = 16;
  double exp = 36;
  double res = A.Determinant();
  EXPECT_FLOAT_EQ(res, exp);

  A(0, 0) = 1.2;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(0, 3) = 4;
  A(1, 0) = 5;
  A(1, 1) = 6;
  A(1, 2) = 7.56;
  A(1, 3) = 8;
  A(2, 0) = 9;
  A(2, 1) = 10.1;
  A(2, 2) = 11;
  A(2, 3) = 12;
  A(3, 0) = 13;
  A(3, 1) = 14;
  A(3, 2) = -15;
  A(3, 3) = 16;
  exp = -13.9072;
  res = A.Determinant();
  EXPECT_FLOAT_EQ(res, exp);
}

TEST(S21MatrixTest, DeterminantExcept) {
  int rows = 3, cols = 2;
  S21Matrix A;
  EXPECT_THROW(A.Determinant(), std::logic_error);
  A.set_rows(rows);
  A.set_cols(cols);
  EXPECT_THROW(A.Determinant(), std::logic_error);
}

TEST(S21MatrixTest, InverseMatrix1x1) {
  int rows = 1, cols = 1;
  S21Matrix A(rows, cols), exp(rows, cols);
  A(0, 0) = 5;
  exp(0, 0) = 0.2;

  S21Matrix B = A.InverseMatrix();
  EXPECT_TRUE(B.EqMatrix(exp));
}

TEST(S21MatrixTest, InverseMatrix2x2) {
  int rows = 2, cols = 2;
  S21Matrix A(rows, cols), exp(rows, cols);
  A(0, 0) = 1;
  A(0, 1) = 1;
  A(1, 0) = 1;
  A(1, 1) = 3;
  exp(0, 0) = 1.5;
  exp(0, 1) = -0.5;
  exp(1, 0) = -0.5;
  exp(1, 1) = 0.5;
  S21Matrix B = A.InverseMatrix();
  EXPECT_TRUE(B.EqMatrix(exp));

  A(0, 0) = 1;
  A(0, 1) = 1;
  A(1, 0) = 1;
  A(1, 1) = 1;
  EXPECT_THROW(A.InverseMatrix(), std::logic_error);
}

TEST(S21MatrixTest, InverseMatrix3x3) {
  int rows = 3, cols = 3;
  S21Matrix A(rows, cols), exp(rows, cols);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 0;
  A(1, 1) = 4;
  A(1, 2) = 2;
  A(2, 0) = 5;
  A(2, 1) = 2;
  A(2, 2) = 1;
  exp(0, 0) = 0;
  exp(0, 1) = -0.1;
  exp(0, 2) = 0.2;
  exp(1, 0) = -0.25;
  exp(1, 1) = 0.35;
  exp(1, 2) = 0.05;
  exp(2, 0) = 0.5;
  exp(2, 1) = -0.2;
  exp(2, 2) = -0.1;
  S21Matrix B = A.InverseMatrix();
  EXPECT_TRUE(B.EqMatrix(exp));

  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 4;
  A(1, 1) = 5;
  A(1, 2) = 6;
  A(2, 0) = 7;
  A(2, 1) = 8;
  A(2, 2) = 9;
  EXPECT_THROW(A.InverseMatrix(), std::logic_error);

  A(0, 0) = 2.5;
  A(0, 1) = 2.5;
  A(0, 2) = -1.36;
  A(1, 0) = 0;
  A(1, 1) = 2;
  A(1, 2) = -3.2;
  A(2, 0) = 0;
  A(2, 1) = 0;
  A(2, 2) = 2;
  exp(0, 0) = 0.4;
  exp(0, 1) = -0.5;
  exp(0, 2) = -0.528;
  exp(1, 0) = 0;
  exp(1, 1) = 0.5;
  exp(1, 2) = 0.8;
  exp(2, 0) = 0;
  exp(2, 1) = 0;
  exp(2, 2) = 0.5;
  B = A.InverseMatrix();
  EXPECT_TRUE(B.EqMatrix(exp));
}

TEST(S21MatrixTest, InverseMatrixExcept) {
  int rows = 3, cols = 2;
  S21Matrix A;
  EXPECT_THROW(A.InverseMatrix(), std::logic_error);
  A.set_rows(rows);
  A.set_cols(cols);
  EXPECT_THROW(A.InverseMatrix(), std::logic_error);
}

TEST(S21MatrixTest, OperatorPlus) {
  srand(time(nullptr));
  int rows = rand() % 100 + 1, cols = rand() % 100 + 1;
  S21Matrix A(rows, cols), B(rows, cols), C(rows + 1, cols), exp(rows, cols);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      double a = (double)rand() / rand(), b = (double)rand() / rand();
      A(i, j) = a;
      B(i, j) = b;
      exp(i, j) = a + b;
    }
  S21Matrix res = A + B;
  EXPECT_TRUE(res.EqMatrix(exp));

  EXPECT_THROW(A + C, std::logic_error);
}

TEST(S21MatrixTest, OperatorMinus) {
  srand(time(nullptr));
  int rows = rand() % 100 + 1, cols = rand() % 100 + 1;
  S21Matrix A(rows, cols), B(rows, cols), C(rows + 1, cols), exp(rows, cols);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      double a = (double)rand() / rand(), b = (double)rand() / rand();
      A(i, j) = a;
      B(i, j) = b;
      exp(i, j) = a - b;
    }
  S21Matrix res = A - B;
  EXPECT_TRUE(res.EqMatrix(exp));

  EXPECT_THROW(A - C, std::logic_error);
}

TEST(S21MatrixTest, OperatorAstNum) {
  srand(time(nullptr));
  int rows = rand() % 100 + 1, cols = rand() % 100 + 1;
  S21Matrix A(rows, cols), exp(rows, cols);
  double num = (double)rand() / rand();
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      double a = (double)rand() / rand();
      A(i, j) = a;
      exp(i, j) = a * num;
    }
  S21Matrix res = A * num;
  EXPECT_TRUE(res.EqMatrix(exp));
}

TEST(S21MatrixTest, OperatorAstMatrix) {
  srand(time(nullptr));
  int m = rand() % 100 + 1, k = rand() % 100 + 1, n = rand() % 100 + 1;
  S21Matrix A(m, k), B(k, n), C(m, n), exp(m, n);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < k; j++) A(i, j) = (double)rand() / rand();
  for (int i = 0; i < k; i++)
    for (int j = 0; j < n; j++) B(i, j) = (double)rand() / rand();
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++) {
      for (int r = 0; r < k; r++) exp(i, j) += A(i, r) * B(r, j);
    }
  S21Matrix res = A * B;
  EXPECT_TRUE(res.EqMatrix(exp));

  EXPECT_THROW(A * C, std::logic_error);
}

TEST(S21MatrixTest, OperatorEq) {
  srand(time(nullptr));
  int rows = rand() % 100 + 1, cols = rand() % 100 + 1;
  S21Matrix A(rows, cols), B(rows, cols);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      double a = (double)rand() / rand();
      A(i, j) = a;
      B(i, j) = a;
    }
  EXPECT_TRUE(A == B);
  EXPECT_TRUE(B == A);
  A(0, 0) = A(0, 0) + 1;
  EXPECT_FALSE(A == B);
  EXPECT_FALSE(B == A);
}

TEST(S21MatrixTest, OperatorCopy) {
  srand(time(nullptr));
  int rows = rand() % 100 + 1, cols = rand() % 100 + 1;
  S21Matrix A(rows, cols);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) A(i, j) = (double)rand() / rand();
  S21Matrix res = A;
  EXPECT_TRUE(A == res);
}

TEST(S21MatrixTest, OperatorPlusEq) {
  srand(time(nullptr));
  int rows = rand() % 100 + 1, cols = rand() % 100 + 1;
  S21Matrix A(rows, cols), B(rows, cols), C(rows + 1, cols), exp(rows, cols);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      double a = (double)rand() / rand(), b = (double)rand() / rand();
      A(i, j) = a;
      B(i, j) = b;
      exp(i, j) = a + b;
    }
  A += B;
  EXPECT_TRUE(A == exp);

  EXPECT_THROW(A += C, std::logic_error);
}

TEST(S21MatrixTest, OperatorMinusEq) {
  srand(time(nullptr));
  int rows = rand() % 100 + 1, cols = rand() % 100 + 1;
  S21Matrix A(rows, cols), B(rows, cols), C(rows + 1, cols), exp(rows, cols);
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      double a = (double)rand() / rand(), b = (double)rand() / rand();
      A(i, j) = a;
      B(i, j) = b;
      exp(i, j) = a - b;
    }
  A -= B;
  EXPECT_TRUE(A == exp);

  EXPECT_THROW(A -= C, std::logic_error);
}

TEST(S21MatrixTest, OperatorAstNumEq) {
  srand(time(nullptr));
  int rows = rand() % 100 + 1, cols = rand() % 100 + 1;
  S21Matrix A(rows, cols), exp(rows, cols);
  double num = (double)rand() / rand();
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      double a = (double)rand() / rand();
      A(i, j) = a;
      exp(i, j) = a * num;
    }
  A *= num;
  EXPECT_TRUE(A == exp);
}

TEST(S21MatrixTest, OperatorAstMatrixEq) {
  srand(time(nullptr));
  int m = rand() % 100 + 1, k = rand() % 100 + 1, n = rand() % 100 + 1;
  S21Matrix A(m, k), B(k, n), C(m, n), exp(m, n);
  for (int i = 0; i < m; i++)
    for (int j = 0; j < k; j++) A(i, j) = (double)rand() / rand();
  for (int i = 0; i < k; i++)
    for (int j = 0; j < n; j++) B(i, j) = (double)rand() / rand();
  for (int i = 0; i < m; i++)
    for (int j = 0; j < n; j++) {
      for (int r = 0; r < k; r++) exp(i, j) += A(i, r) * B(r, j);
    }
  A *= B;
  EXPECT_TRUE(A == exp);

  EXPECT_THROW(A *= C, std::logic_error);
}

TEST(S21MatrixTest, OperatorParenthesis) {
  srand(time(nullptr));
  int rows = 7, cols = 9;
  S21Matrix A(rows, cols);
  double exp[rows][cols];
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      double a = (double)rand() / rand();
      A(i, j) = a;
      exp[i][j] = a;
    }

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) EXPECT_EQ(A(i, j), exp[i][j]);

  EXPECT_THROW(A(rows + 1, cols), std::length_error);
  EXPECT_THROW(A(rows, cols + 1), std::length_error);
  EXPECT_THROW(A(-1, cols), std::length_error);
  EXPECT_THROW(A(rows, -1), std::length_error);
}

TEST(S21MatrixTest, OperatorParenthesisConst) {
  srand(time(nullptr));
  int rows = 7, cols = 9;
  const S21Matrix A(rows, cols);
  double exp[rows][cols];
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      double a = (double)rand() / rand();
      A(i, j) = a;
      exp[i][j] = a;
    }

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) EXPECT_EQ(A(i, j), exp[i][j]);

  EXPECT_THROW(A(rows + 1, cols), std::length_error);
  EXPECT_THROW(A(rows, cols + 1), std::length_error);
  EXPECT_THROW(A(-1, cols), std::length_error);
  EXPECT_THROW(A(rows, -1), std::length_error);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}