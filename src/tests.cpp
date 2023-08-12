#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(MatrixConstructor, DefaultConstructor) {
  S21Matrix A;
  EXPECT_EQ(A.getRows(), 1);
  EXPECT_EQ(A.getCols(), 1);
}

TEST(MatrixConstructor, ConstructorWithRowsAndCols) {
  int rows = 3;
  int cols = 4;
  S21Matrix A(rows, cols);
  EXPECT_EQ(A.getRows(), rows);
  EXPECT_EQ(A.getCols(), cols);
}

TEST(MatrixConstructor, ConstructorWithInvalidSize) {
  int rows = -1;
  int cols = 2;
  EXPECT_THROW(S21Matrix A(rows, cols), std::invalid_argument);

  rows = 3;
  cols = 0;
  EXPECT_THROW(S21Matrix A(rows, cols), std::invalid_argument);
}

TEST(MatrixConstructor, CopyConstructor) {
  S21Matrix A(2, 3);
  A(0, 0) = 1.25;
  A(0, 1) = 3.0;
  A(0, 2) = 4.25;

  A(1, 0) = -1.25;
  A(1, 1) = 5.25;
  A(1, 2) = -1.25;

  S21Matrix B(A);
  EXPECT_EQ(B.getRows(), A.getRows());
  EXPECT_EQ(B.getCols(), A.getCols());
  EXPECT_TRUE(A == B);
}

TEST(S21MatrixTest, ConstructorMove) {
  S21Matrix A(2, 2);
  A(0, 0) = 15.55;
  A(0, 1) = -15.55;

  A(1, 0) = 3.55;
  A(1, 1) = -3.55;

  S21Matrix B = S21Matrix(std::move(A));

  EXPECT_EQ(A.getRows(), 0);
  EXPECT_EQ(A.getCols(), 0);

  EXPECT_EQ(B.getRows(), 2);
  EXPECT_EQ(B.getCols(), 2);

  EXPECT_NEAR(B(0, 0), 15.55, EPS);
  EXPECT_NEAR(B(0, 1), -15.55, EPS);
  EXPECT_NEAR(B(1, 0), 3.55, EPS);
  EXPECT_NEAR(B(1, 1), -3.55, EPS);
}

TEST(MatrixMethods, SetRows) {
  S21Matrix A(2, 3);
  A(0, 0) = 1.25;
  A(0, 1) = 3.0;
  A(0, 2) = 4.25;

  A(1, 0) = -1.25;
  A(1, 1) = 5.25;
  A(1, 2) = -1.25;
  EXPECT_EQ(A.getRows(), 2);
  EXPECT_EQ(A.getCols(), 3);

  int newRows = 3;
  A.setRows(newRows);
  EXPECT_NEAR(A(0, 0), 1.25, EPS);
  EXPECT_NEAR(A(2, 0), 0.0, EPS);
  EXPECT_NEAR(A(2, 1), 0.0, EPS);
  EXPECT_NEAR(A(2, 2), 0.0, EPS);
  EXPECT_EQ(A.getRows(), newRows);
  EXPECT_EQ(A.getCols(), 3);
}

TEST(MatrixMethods, SetCols) {
  S21Matrix A(2, 3);
  A(0, 0) = 1.25;
  A(0, 1) = 3.0;
  A(0, 2) = 4.25;

  A(1, 0) = -1.25;
  A(1, 1) = 5.25;
  A(1, 2) = -1.25;
  EXPECT_EQ(A.getRows(), 2);
  EXPECT_EQ(A.getCols(), 3);

  int newCols = 4;
  A.setCols(newCols);
  EXPECT_NEAR(A(1, 1), 5.25, EPS);
  EXPECT_NEAR(A(0, 3), 0.0, EPS);
  EXPECT_NEAR(A(1, 3), 0.0, EPS);
  EXPECT_EQ(A.getRows(), 2);
  EXPECT_EQ(A.getCols(), newCols);
}

TEST(MatrixMethods, SetInvalidRows) {
  S21Matrix A(2, 3);
  EXPECT_EQ(A.getRows(), 2);
  EXPECT_EQ(A.getCols(), 3);

  int invalidRows = -1;
  EXPECT_THROW(A.setRows(invalidRows), std::invalid_argument);

  EXPECT_EQ(A.getRows(), 2);
  EXPECT_EQ(A.getCols(), 3);
}

TEST(MatrixMethods, SetInvalidCols) {
  S21Matrix A(2, 3);
  EXPECT_EQ(A.getRows(), 2);
  EXPECT_EQ(A.getCols(), 3);

  int invalidCols = -1;
  EXPECT_THROW(A.setCols(invalidCols), std::invalid_argument);

  EXPECT_EQ(A.getRows(), 2);
  EXPECT_EQ(A.getCols(), 3);
}

TEST(S21MatrixTest, AssignmentOperator_SameMatrix_Empty_Matrix) {
  S21Matrix A(2, 2);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  S21Matrix B(2, 2);
  B = A;

  EXPECT_TRUE(B.EqMatrix(A));
}

TEST(S21MatrixTest, AssignmentOperator_DifferentMatrix) {
  S21Matrix A(2, 2);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  S21Matrix B(2, 2);
  B(0, 0) = 5.0;
  B(0, 1) = 6.0;
  B(1, 0) = 7.0;
  B(1, 1) = 8.0;

  B = A;

  EXPECT_TRUE(B.EqMatrix(A));
}

TEST(S21MatrixTest, AssignmentOperator_DifferentSizeMatrix) {
  S21Matrix A(2, 2);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  S21Matrix B(3, 2);
  B(0, 0) = 5.0;
  B(0, 1) = 6.0;
  B(1, 0) = 7.0;
  B(1, 1) = 8.0;
  B(2, 0) = 7.0;
  B(2, 1) = 8.0;

  B = A;

  EXPECT_TRUE(B.EqMatrix(A));
}

TEST(S21MatrixTest, AccessOperator_GetValue_ReturnsCorrectValue) {
  S21Matrix A(2, 2);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  double value = A(1, 0);

  EXPECT_NEAR(value, 3.0, EPS);
}

TEST(S21MatrixTest, AccessOperator_SetValue_ChangesMatrix) {
  S21Matrix A(2, 2);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  A(0, 1) = 5.0;

  EXPECT_NEAR(A(0, 1), 5.0, EPS);
}

TEST(S21MatrixTest, AccessOperator_InvalidIndex_ThrowsOutOfRange) {
  S21Matrix A(2, 2);
  EXPECT_THROW(A(2, 0), std::invalid_argument);
}

TEST(S21MatrixTest, AccessOperator_NegativeIndex_ThrowsOutOfRange) {
  S21Matrix A(2, 2);
  EXPECT_THROW(A(0, -1), std::invalid_argument);
}

TEST(S21MatrixTest, AccessOperator_OutOfRange_ThrowsException) {
  S21Matrix A(2, 2);

  EXPECT_THROW(A(3, 0), std::invalid_argument);

  const S21Matrix B(2, 2);
  EXPECT_THROW(B(3, 0), std::invalid_argument);
}

TEST(S21MatrixTest, OperatorPlus) {
  S21Matrix A(2, 2);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  S21Matrix B(2, 2);
  B(0, 0) = 5.0;
  B(0, 1) = 6.0;
  B(1, 0) = 7.0;
  B(1, 1) = 8.0;

  S21Matrix result = A + B;

  EXPECT_NEAR(result(0, 0), 6.0, EPS);
  EXPECT_NEAR(result(0, 1), 8.0, EPS);
  EXPECT_NEAR(result(1, 0), 10.0, EPS);
  EXPECT_NEAR(result(1, 1), 12.0, EPS);
}

TEST(S21MatrixTest, OperatorMinus) {
  S21Matrix A(2, 2);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  S21Matrix B(2, 2);
  B(0, 0) = 5.0;
  B(0, 1) = 6.0;
  B(1, 0) = 7.0;
  B(1, 1) = 8.0;

  S21Matrix result = A - B;

  EXPECT_NEAR(result(0, 0), -4.0, EPS);
  EXPECT_NEAR(result(0, 1), -4.0, EPS);
  EXPECT_NEAR(result(1, 0), -4.0, EPS);
  EXPECT_NEAR(result(1, 1), -4.0, EPS);
}

TEST(S21MatrixTest, OperatorMinusEqual) {
  S21Matrix A(2, 2);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  S21Matrix B(2, 2);
  B(0, 0) = 5.0;
  B(0, 1) = 6.0;
  B(1, 0) = 7.0;
  B(1, 1) = 8.0;

  A -= B;

  EXPECT_NEAR(A(0, 0), -4.0, EPS);
  EXPECT_NEAR(A(0, 1), -4.0, EPS);
  EXPECT_NEAR(A(1, 0), -4.0, EPS);
  EXPECT_NEAR(A(1, 1), -4.0, EPS);
}

TEST(S21MatrixTest, OperatorMinus_DifferentSizeMatrices_ThrowsInvalidArgument) {
  S21Matrix A(2, 2);
  S21Matrix B(3, 3);
  EXPECT_THROW(A - B, std::invalid_argument);
}

TEST(S21MatrixTest, OperatorMinus_ValidInput_ReturnsCorrectResult) {
  S21Matrix A(2, 2);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  S21Matrix B(2, 2);
  B(0, 0) = 5.0;
  B(0, 1) = 6.0;
  B(1, 0) = 7.0;
  B(1, 1) = 7.0;

  S21Matrix C = A - B;

  EXPECT_NEAR(C(0, 0), -4.0, EPS);
  EXPECT_NEAR(C(0, 1), -4.0, EPS);
  EXPECT_NEAR(C(1, 0), -4.0, EPS);
  EXPECT_NEAR(C(1, 1), -3.0, EPS);
}

TEST(S21MatrixTest,
     OperatorMinusEqual_DifferentSizeMatrices_ThrowsInvalidArgument) {
  S21Matrix A(2, 2);
  S21Matrix B(3, 3);
  EXPECT_THROW(A -= B, std::invalid_argument);
}

TEST(S21MatrixTest, OperatorMinusEqual_ValidInput_ModifiesMatrixInPlace) {
  S21Matrix A(2, 2);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  S21Matrix B(2, 2);
  B(0, 0) = 5.0;
  B(0, 1) = 6.0;
  B(1, 0) = 7.0;
  B(1, 1) = 6.0;

  A -= B;

  EXPECT_NEAR(A(0, 0), -4.0, EPS);
  EXPECT_NEAR(A(0, 1), -4.0, EPS);
  EXPECT_NEAR(A(1, 0), -4.0, EPS);
  EXPECT_NEAR(A(1, 1), -2.0, EPS);
}

TEST(S21MatrixTest, OperatorPlusEqual) {
  S21Matrix A(2, 2);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  S21Matrix B(2, 2);
  B(0, 0) = 5.0;
  B(0, 1) = 6.0;
  B(1, 0) = 7.0;
  B(1, 1) = 8.0;

  A += B;

  EXPECT_NEAR(A(0, 0), 6.0, EPS);
  EXPECT_NEAR(A(0, 1), 8.0, EPS);
  EXPECT_NEAR(A(1, 0), 10.0, EPS);
  EXPECT_NEAR(A(1, 1), 12.0, EPS);
}

TEST(S21MatrixTest, OperatorPlus_DifferentSizeMatrices_ThrowsInvalidArgument) {
  S21Matrix A(2, 2);
  S21Matrix B(3, 3);
  EXPECT_THROW(A + B, std::invalid_argument);
}

TEST(S21MatrixTest, OperatorPlus_ValidInput_ReturnsCorrectResult) {
  S21Matrix A(2, 2);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  S21Matrix B(2, 2);
  B(0, 0) = 5.0;
  B(0, 1) = 6.0;
  B(1, 0) = 7.0;
  B(1, 1) = 8.0;

  S21Matrix C = A + B;

  EXPECT_NEAR(C(0, 0), 6.0, EPS);
  EXPECT_NEAR(C(0, 1), 8.0, EPS);
  EXPECT_NEAR(C(1, 0), 10.0, EPS);
  EXPECT_NEAR(C(1, 1), 12.0, EPS);
}

TEST(S21MatrixTest,
     OperatorPlusEqual_DifferentSizeMatrices_ThrowsInvalidArgument) {
  S21Matrix A(2, 2);
  S21Matrix B(3, 3);
  EXPECT_THROW(A += B, std::invalid_argument);
}

TEST(S21MatrixTest, OperatorPlusEqual_ValidInput_ModifiesMatrixInPlace) {
  S21Matrix A(2, 2);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  S21Matrix B(2, 2);
  B(0, 0) = 5.0;
  B(0, 1) = 6.0;
  B(1, 0) = 7.0;
  B(1, 1) = 8.0;

  A += B;

  EXPECT_NEAR(A(0, 0), 6.0, EPS);
  EXPECT_NEAR(A(0, 1), 8.0, EPS);
  EXPECT_NEAR(A(1, 0), 10.0, EPS);
  EXPECT_NEAR(A(1, 1), 12.0, EPS);
}

TEST(S21MatrixTest, EqMatrix_DifferentMatrices) {
  S21Matrix A(2, 2);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  S21Matrix B(3, 2);
  B(0, 0) = 1.0;
  B(0, 1) = 2.0;
  B(1, 0) = 3.0;
  B(1, 1) = 4.0;

  EXPECT_FALSE(A.EqMatrix(B));
}

TEST(S21MatrixTest, MultiplicationOperator_EmptyMatrices) {
  S21Matrix A(1, 1);
  S21Matrix B(1, 1);
  S21Matrix C = A * B;
  EXPECT_EQ(C.getRows(), 1);
  EXPECT_EQ(C.getCols(), 1);
  EXPECT_NEAR(C(0, 0), 0.0, EPS);
}

TEST(S21MatrixTest,
     MultiplicationOperator_DifferentSizeMatrices_ThrowsInvalidArgument) {
  S21Matrix A(2, 2);
  S21Matrix B(3, 3);
  EXPECT_THROW(A * B, std::invalid_argument);
}

TEST(S21MatrixTest, MultiplicationOperator_ValidInput_ReturnsCorrectResult) {
  S21Matrix A(2, 3);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(0, 2) = 3.0;
  A(1, 0) = 4.0;
  A(1, 1) = 5.0;
  A(1, 2) = 6.0;

  S21Matrix B(3, 2);
  B(0, 0) = 7.0;
  B(0, 1) = 8.0;
  B(1, 0) = 9.0;
  B(1, 1) = 10.0;
  B(2, 0) = 11.0;
  B(2, 1) = 12.0;

  S21Matrix C = A * B;

  EXPECT_EQ(C.getRows(), 2);
  EXPECT_EQ(C.getCols(), 2);
  EXPECT_NEAR(C(0, 0), 58.0, EPS);
  EXPECT_NEAR(C(0, 1), 64.0, EPS);
  EXPECT_NEAR(C(1, 0), 139.0, EPS);
  EXPECT_NEAR(C(1, 1), 154.0, EPS);
}

TEST(S21MatrixTest,
     MultiplicationOperator_MultiplyByScalar_ReturnsCorrectResult) {
  S21Matrix A(2, 2);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  S21Matrix B = A * 2.0;

  EXPECT_EQ(B.getRows(), 2);
  EXPECT_EQ(B.getCols(), 2);
  EXPECT_NEAR(B(0, 0), 2.0, EPS);
  EXPECT_NEAR(B(0, 1), 4.0, EPS);
  EXPECT_NEAR(B(1, 0), 6.0, EPS);
  EXPECT_NEAR(B(1, 1), 8.0, EPS);
}
TEST(S21MatrixTest, MultiplicationAssignmentOperator_EmptyMatrix_NoChange) {
  S21Matrix A(1, 1);
  A *= 2.0;
  EXPECT_EQ(A.getRows(), 1);
  EXPECT_EQ(A.getCols(), 1);
  EXPECT_NEAR(A(0, 0), 0.0, EPS);
}

TEST(
    S21MatrixTest,
    MultiplicationAssignmentOperator_MultiplyByScalar_ValidInput_ModifiesMatrixInPlace) {
  S21Matrix A(2, 2);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  A *= 2.0;

  EXPECT_EQ(A.getRows(), 2);
  EXPECT_EQ(A.getCols(), 2);
  EXPECT_NEAR(A(0, 0), 2.0, EPS);
  EXPECT_NEAR(A(0, 1), 4.0, EPS);
  EXPECT_NEAR(A(1, 0), 6.0, EPS);
  EXPECT_NEAR(A(1, 1), 8.0, EPS);
}

TEST(
    S21MatrixTest,
    MultiplicationAssignmentOperator_DifferentSizeMatrices_ThrowsInvalidArgument) {
  S21Matrix A(2, 2);
  S21Matrix B(3, 3);
  EXPECT_THROW(A *= B, std::invalid_argument);
}

TEST(S21MatrixTest,
     MultiplicationAssignmentOperator_ValidInput_ModifiesMatrixInPlace) {
  S21Matrix A(2, 3);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(0, 2) = 3.0;
  A(1, 0) = 4.0;
  A(1, 1) = 5.0;
  A(1, 2) = 6.0;

  S21Matrix B(3, 2);
  B(0, 0) = 7.0;
  B(0, 1) = 8.0;
  B(1, 0) = 9.0;
  B(1, 1) = 10.0;
  B(2, 0) = 11.0;
  B(2, 1) = 12.0;

  A *= B;

  EXPECT_EQ(A.getRows(), 2);
  EXPECT_EQ(A.getCols(), 2);
  EXPECT_NEAR(A(0, 0), 58.0, EPS);
  EXPECT_NEAR(A(0, 1), 64.0, EPS);
  EXPECT_NEAR(A(1, 0), 139.0, EPS);
  EXPECT_NEAR(A(1, 1), 154.0, EPS);
}

TEST(S21MatrixTest, Transpose_UnitMatrix) {
  S21Matrix A(1, 1);
  A(0, 0) = 2.25;
  S21Matrix B = A.Transpose();
  EXPECT_EQ(B.getRows(), 1);
  EXPECT_EQ(B.getCols(), 1);
  EXPECT_NEAR(A(0, 0), B(0, 0), EPS);
}

TEST(S21MatrixTest, Transpose_SquareMatrix_ValidInput_ReturnsCorrectResult) {
  S21Matrix A(3, 3);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(0, 2) = 3.0;
  A(1, 0) = 4.0;
  A(1, 1) = 5.0;
  A(1, 2) = 6.0;
  A(2, 0) = 7.0;
  A(2, 1) = 8.0;
  A(2, 2) = 9.0;

  S21Matrix B = A.Transpose();

  EXPECT_EQ(B.getRows(), 3);
  EXPECT_EQ(B.getCols(), 3);
  EXPECT_NEAR(B(0, 0), 1.0, EPS);
  EXPECT_NEAR(B(0, 1), 4.0, EPS);
  EXPECT_NEAR(B(0, 2), 7.0, EPS);
  EXPECT_NEAR(B(1, 0), 2.0, EPS);
  EXPECT_NEAR(B(1, 1), 5.0, EPS);
  EXPECT_NEAR(B(1, 2), 8.0, EPS);
  EXPECT_NEAR(B(2, 0), 3.0, EPS);
  EXPECT_NEAR(B(2, 1), 6.0, EPS);
  EXPECT_NEAR(B(2, 2), 9.0, EPS);
}

TEST(S21MatrixTest,
     Transpose_RectangularMatrix_ValidInput_ReturnsCorrectResult) {
  S21Matrix A(2, 3);
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(0, 2) = 3.0;
  A(1, 0) = 4.0;
  A(1, 1) = 5.0;
  A(1, 2) = 6.0;

  S21Matrix B = A.Transpose();

  EXPECT_EQ(B.getRows(), 3);
  EXPECT_EQ(B.getCols(), 2);
  EXPECT_NEAR(B(0, 0), 1.0, EPS);
  EXPECT_NEAR(B(0, 1), 4.0, EPS);
  EXPECT_NEAR(B(1, 0), 2.0, EPS);
  EXPECT_NEAR(B(1, 1), 5.0, EPS);
  EXPECT_NEAR(B(2, 0), 3.0, EPS);
  EXPECT_NEAR(B(2, 1), 6.0, EPS);
}

TEST(S21MatrixTest, CalcComplements_1x1_NonZero) {
  S21Matrix A(1, 1);
  A(0, 0) = 5.0;

  S21Matrix B = A.CalcComplements();

  EXPECT_NEAR(B(0, 0), 1., EPS);
}

TEST(S21MatrixTest, CalcComplements_1x1_Zero) {
  S21Matrix A(1, 1);
  A(0, 0) = 0.0;

  EXPECT_THROW(S21Matrix B = A.CalcComplements(), std::logic_error);
}

TEST(S21MatrixTest, CalcComplements_InvalidSize) {
  S21Matrix A(1, 2);
  A(0, 0) = 2.0;
  A(0, 1) = 1.0;

  EXPECT_THROW(S21Matrix B = A.CalcComplements(), std::invalid_argument);
}

TEST(S21MatrixTest, CalcComplements_2x2) {
  S21Matrix A(2, 2);

  S21Matrix B = A.CalcComplements();

  EXPECT_NEAR(B(0, 0), 0.0, EPS);
  EXPECT_NEAR(B(0, 1), 0.0, EPS);
  EXPECT_NEAR(B(1, 0), 0.0, EPS);
  EXPECT_NEAR(B(1, 1), 0.0, EPS);
  EXPECT_EQ(B.getRows(), 2);
  EXPECT_EQ(B.getCols(), 2);
}

TEST(S21MatrixTest, CalcComplements_3x3) {
  S21Matrix A(3, 3);
  A(0, 0) = 3.0;
  A(0, 1) = 2.0;
  A(0, 2) = -6.0;

  A(1, 0) = -4.0;
  A(1, 1) = 17.0;
  A(1, 2) = 7.0;

  A(2, 0) = 1.0;
  A(2, 1) = 2.0;
  A(2, 2) = 9.0;

  S21Matrix B = A.CalcComplements();

  EXPECT_NEAR(B(0, 0), 139.0, EPS);
  EXPECT_NEAR(B(0, 1), 43.0, EPS);
  EXPECT_NEAR(B(0, 2), -25.0, EPS);

  EXPECT_NEAR(B(1, 0), -30.0, EPS);
  EXPECT_NEAR(B(1, 1), 33.0, EPS);
  EXPECT_NEAR(B(1, 2), -4.0, EPS);

  EXPECT_NEAR(B(2, 0), 116.0, EPS);
  EXPECT_NEAR(B(2, 1), 3.0, EPS);
  EXPECT_NEAR(B(2, 2), 59.0, EPS);

  EXPECT_EQ(B.getRows(), 3);
  EXPECT_EQ(B.getCols(), 3);
}

TEST(S21MatrixTest, Determinant_2x2_Zero) {
  S21Matrix A(2, 2);

  double det = A.Determinant();

  EXPECT_NEAR(det, 0.0, EPS);
}

TEST(S21MatrixTest, Determinant_1x1_Zero) {
  S21Matrix A(1, 1);
  A(0, 0) = 0.0;

  double det = A.Determinant();

  EXPECT_NEAR(det, 0.0, EPS);
}

TEST(S21MatrixTest, Determinant_InvalidSize) {
  S21Matrix A(3, 2);
  A(0, 0) = 0.0;

  double det = 0.0;

  EXPECT_THROW(det = A.Determinant(), std::invalid_argument);
  EXPECT_NEAR(det, 0.0, EPS);
}

TEST(S21MatrixTest, Determinant_1x1_NonZero) {
  S21Matrix A(1, 1);
  A(0, 0) = -7.77;

  double det = A.Determinant();

  EXPECT_NEAR(det, -7.77, EPS);
}

TEST(S21MatrixTest, Determinant_5x5) {
  S21Matrix A(5, 5);
  A(0, 0) = 3.0;
  A(0, 1) = 2.0;
  A(0, 2) = -6.0;
  A(0, 3) = 2.0;
  A(0, 4) = -6.0;

  A(1, 0) = -4.0;
  A(1, 1) = 17.0;
  A(1, 2) = 7.0;
  A(1, 3) = 17.0;
  A(1, 4) = 7.0;

  A(2, 0) = 1.0;
  A(2, 1) = 2.0;
  A(2, 2) = 9.0;
  A(2, 3) = -3.0;
  A(2, 4) = 4.0;

  A(3, 0) = 12.0;
  A(3, 1) = 3.0;
  A(3, 2) = 3.0;
  A(3, 3) = 2.0;
  A(3, 4) = 9.0;

  A(4, 0) = -1.0;
  A(4, 1) = -2.0;
  A(4, 2) = 4.0;
  A(4, 3) = 8.0;
  A(4, 4) = -1.0;

  double det = A.Determinant();

  EXPECT_NEAR(det, -158255, EPS);
}

TEST(S21MatrixTest, InverseMatrix_SingleElement_NonZero) {
  S21Matrix A(1, 1);
  A(0, 0) = 10.0;

  S21Matrix B = A.InverseMatrix();

  EXPECT_NEAR(B(0, 0), 0.1, EPS);
}

TEST(S21MatrixTest, InverseMatrix_SingleElement_Negative) {
  S21Matrix A(1, 1);
  A(0, 0) = -50.0;

  S21Matrix B = A.InverseMatrix();

  EXPECT_NEAR(B(0, 0), -0.02, EPS);
}

TEST(S21MatrixTest, InverseMatrix_SingleElement_Zero) {
  S21Matrix A(1, 1);
  A(0, 0) = 0.0;

  EXPECT_THROW(S21Matrix B = A.InverseMatrix(), std::invalid_argument);
}

TEST(S21MatrixTest, InverseMatrix_InvalidSize) {
  S21Matrix A(2, 2);

  EXPECT_THROW(S21Matrix B = A.InverseMatrix(), std::invalid_argument);
}

TEST(S21MatrixTest, InverseMatrix_2x2) {
  S21Matrix A(2, 2);
  A(0, 0) = 14.0;
  A(0, 1) = 64.0;

  A(1, 0) = -27.0;
  A(1, 1) = 58.0;

  S21Matrix B = A.InverseMatrix();

  EXPECT_NEAR(B(0, 0), 29. / 1270., EPS);
  EXPECT_NEAR(B(0, 1), -(16. / 635.), EPS);
  EXPECT_NEAR(B(1, 0), 27. / 2540., EPS);
  EXPECT_NEAR(B(1, 1), 7. / 1270., EPS);

  EXPECT_EQ(B.getRows(), 2);
  EXPECT_EQ(B.getCols(), 2);
}

TEST(S21MatrixTest, InverseMatrix_4x4) {
  S21Matrix A(4, 4);
  A(0, 0) = 3.0;
  A(0, 1) = 2.0;
  A(0, 2) = -6.2;
  A(0, 3) = 5.5;

  A(1, 0) = -2.0;
  A(1, 1) = 14.0;
  A(1, 2) = 7.0;
  A(1, 3) = 1.7;

  A(2, 0) = 1.12;
  A(2, 1) = 3.0;
  A(2, 2) = 9.0;
  A(2, 3) = -3.0;

  A(3, 0) = 1.0;
  A(3, 1) = 3.0;
  A(3, 2) = 3.0;
  A(3, 3) = 2.0;

  S21Matrix B = A.InverseMatrix();

  EXPECT_NEAR(B(0, 0), 25250. / 95691., EPS);
  EXPECT_NEAR(B(0, 1), -(5000. / 95691.), EPS);
  EXPECT_NEAR(B(0, 2), 28675 / 95691., EPS);
  EXPECT_NEAR(B(0, 3), -(22175 / 95691.), EPS);

  EXPECT_NEAR(B(1, 0), 125335. / 1148292., EPS);
  EXPECT_NEAR(B(1, 1), 103085. / 1148292., EPS);
  EXPECT_NEAR(B(1, 2), 100175. / 1148292., EPS);
  EXPECT_NEAR(B(1, 3), -(282031. / 1148292.), EPS);

  EXPECT_NEAR(B(2, 0), -(128435. / 1148292.), EPS);
  EXPECT_NEAR(B(2, 1), -(45625. / 1148292.), EPS);
  EXPECT_NEAR(B(2, 2), -(37375. / 1148292.), EPS);
  EXPECT_NEAR(B(2, 3), 335915. / 1148292., EPS);

  EXPECT_NEAR(B(3, 0), -(24475. / 191382.), EPS);
  EXPECT_NEAR(B(3, 1), -(9365. / 191382.), EPS);
  EXPECT_NEAR(B(3, 2), -(44375. / 191382.), EPS);
  EXPECT_NEAR(B(3, 3), 104395. / 191382., EPS);

  EXPECT_EQ(B.getRows(), 4);
  EXPECT_EQ(B.getCols(), 4);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}