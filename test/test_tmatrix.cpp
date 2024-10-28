#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
    int* pmem0 = new int[4] {5, 1, 2, 5};
    int* pmem1 = new int[4] {1, 4, 2, 3};
    int* pmem2 = new int[4] {1, 12, 13,15};
    int* pmem3 = new int[4] {16, 21, 19, 45};

    TDynamicVector<int> vec_0(pmem0, 4);
    TDynamicVector<int> vec_1(pmem1, 4);
    TDynamicVector<int> vec_2(pmem2, 4);
    TDynamicVector<int> vec_3(pmem3, 4);


    delete[] pmem0; 
    delete[] pmem1; 
    delete[] pmem2; 
    delete[] pmem3; 

    TDynamicMatrix<int> m(4);

    m[0] = vec_0; 
    m[1] = vec_1; 
    m[2] = vec_2; 
    m[3] = vec_3;

    TDynamicMatrix<int> m1(m);

	EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int> m1(2);

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            m1[i][j] = 1;
        }
    }
    TDynamicMatrix<int> m2(m1);

    EXPECT_NE(&m1, &m2);
}

TEST(TDynamicMatrix, can_get_size)
{
    const int size = 5;
    TDynamicMatrix<int> m(size);

    EXPECT_EQ(size, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    const int size = 2;

    TDynamicMatrix<int> m(size);

    m[0][0] = 1;
    m[0][1] = 2;
    m[1][0] = 3;
    m[1][1] = 4;

    EXPECT_EQ(size, m[0][1]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    const int size = 3;

    TDynamicMatrix<int> m(size);

    ASSERT_ANY_THROW(m.at(-5));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    const int size = 3;

    TDynamicMatrix<int> m(size);

    ASSERT_ANY_THROW(m.at(10));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    const int size = 3;

    TDynamicMatrix<int> m1(size);
    TDynamicMatrix<int> m2(size);

    m1[2][2] = m2[2][2] = 1;

    m1 = m1;

    ASSERT_EQ(m1, m2);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    const int size = 2;

    TDynamicMatrix<int> m1(size);

    TDynamicMatrix<int> m2(size);

    ASSERT_EQ(m2 = m1, m1);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    const int size = 2;

    TDynamicMatrix<int> m1(size);

    TDynamicMatrix<int> m2(size + 1);

    m2 = m1;

    ASSERT_EQ(m2.size(), size);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    const int size = 2;

    TDynamicMatrix<int> m1(size);

    TDynamicMatrix<int> m2(size + 1);

    m2 = m1;

    ASSERT_EQ(m2, m1);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    const int size = 2;

    TDynamicMatrix<int> m1(size);

    TDynamicMatrix<int> m2(size);

    ASSERT_EQ(m1 == m2, true);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    const int size = 2;
    TDynamicMatrix<int> m(size);

    ASSERT_EQ(m == m, true);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    const int size = 2;

    TDynamicMatrix<int> m1(size);

    TDynamicMatrix<int> m2(size + 1);

    ASSERT_EQ(m1 == m2, false);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    const int size = 2;

    TDynamicMatrix<int> m1(size);

    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[1][0] = 3;
    m1[1][1] = 4;

    TDynamicMatrix<int> m2(size);

    m2[0][0] = 5;
    m2[0][1] = 6;
    m2[1][0] = 7;
    m2[1][1] = 8;

    TDynamicMatrix<int> res = m1 + m2;

    ASSERT_EQ(res[0][0], 6);
    ASSERT_EQ(res[0][1], 8);
    ASSERT_EQ(res[1][0], 10);
    ASSERT_EQ(res[1][1], 12);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    const int size = 3;

    TDynamicMatrix<int> m1(size);

    TDynamicMatrix<int> m2(size + 1);

    ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    const int size = 2;

    TDynamicMatrix<int> m1(size);

    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[1][0] = 3;
    m1[1][1] = 4;

    TDynamicMatrix<int> m2(size);

    m2[0][0] = 5;
    m2[0][1] = 6;
    m2[1][0] = 7;
    m2[1][1] = 8;

    TDynamicMatrix<int> res = m1 - m2;

    ASSERT_EQ(res[0][0], -4);
    ASSERT_EQ(res[0][1], -4);
    ASSERT_EQ(res[1][0], -4);
    ASSERT_EQ(res[1][1], -4);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    const int size = 3;

    TDynamicMatrix<int> m1(size);

    TDynamicMatrix<int> m2(size + 2);

    ASSERT_ANY_THROW(m1 - m2);
}
//Свои тесты

TEST(TDynamicMatrix, can_multiply_matrix_by_scalar) {

    TDynamicMatrix<int> original_matrix(4);
    TDynamicMatrix<int> result_matrix(4);
    int scalar = 3;

    int* row1 = new int [4] { 2, 4, 6, 8};
    int* row2 = new int [4] { 10, 12, 14, 16};
    int* row3 = new int [4] { 18, 20, 22, 24};
    int* row4 = new int [4] { 26, 28, 30, 32};

    int* expected_row1 = new int [4] { 6, 12, 18, 24};
    int* expected_row2 = new int [4] { 30, 36, 42, 48};
    int* expected_row3 = new int [4] { 54, 60, 66, 72};
    int* expected_row4 = new int [4] { 78, 84, 90, 96};

    TDynamicVector<int> vector_row1(row1, 4);
    TDynamicVector<int> vector_row2(row2, 4);
    TDynamicVector<int> vector_row3(row3, 4);
    TDynamicVector<int> vector_row4(row4, 4);

    TDynamicVector<int> expected_vector_row1(expected_row1, 4);
    TDynamicVector<int> expected_vector_row2(expected_row2, 4);
    TDynamicVector<int> expected_vector_row3(expected_row3, 4);
    TDynamicVector<int> expected_vector_row4(expected_row4, 4);

    delete[] row1;
    delete[] row2;
    delete[] row3;
    delete[] row4;

    delete[] expected_row1;
    delete[] expected_row2;
    delete[] expected_row3;
    delete[] expected_row4;

    original_matrix[0] = vector_row1;
    original_matrix[1] = vector_row2;
    original_matrix[2] = vector_row3;
    original_matrix[3] = vector_row4;

    result_matrix[0] = expected_vector_row1;
    result_matrix[1] = expected_vector_row2;
    result_matrix[2] = expected_vector_row3;
    result_matrix[3] = expected_vector_row4;

    EXPECT_EQ(original_matrix * scalar, result_matrix);

}
TEST(TDynamicMatrix, can_multiply_matrix_by_vector_with_correct_size) {

    TDynamicMatrix<int> original_matrix(4);
    TDynamicMatrix<int> result_matrix(4);

    int* row1 = new int [4] { 1, 2, 3, 1};
    int* row2 = new int [4] { 1, 1, 1, 1};
    int* row3 = new int [4] { 1, 2, 2, 2};
    int* row4 = new int [4] { 2, 2, 3, 3};

    int* vector_elements = new int [4] { 1, 2, 1, 1};

    int* expected_vector_elements = new int [4] { 9, 5, 9, 12};

    TDynamicVector<int> vector_row1(row1, 4);
    TDynamicVector<int> vector_row2(row2, 4);
    TDynamicVector<int> vector_row3(row3, 4);
    TDynamicVector<int> vector_row4(row4, 4);

    TDynamicVector<int> input_vector(vector_elements, 4);
    TDynamicVector<int> expected_result_vector(expected_vector_elements, 4);

    delete[] row1;
    delete[] row2;
    delete[] row3;
    delete[] row4;

    delete[] vector_elements;
    delete[] expected_vector_elements;

    original_matrix[0] = vector_row1;
    original_matrix[1] = vector_row2;
    original_matrix[2] = vector_row3;
    original_matrix[3] = vector_row4;

    EXPECT_EQ(original_matrix * input_vector, expected_result_vector);
}
TEST(TDynamicMatrix, cant_multiply_matrix_by_vector_with_incorrect_size) {

    TDynamicMatrix<int> original_matrix(4);
    TDynamicMatrix<int> result_matrix(4);

    int* row1 = new int [4] { 2, 4, 6, 8};
    int* row2 = new int [4] { 10, 12, 14, 16};
    int* row3 = new int [4] { 18, 20, 22, 24};
    int* row4 = new int [4] { 26, 28, 30, 32};

    int* vector_elements = new int [5] { 3, 5, 7, 9, 11};

    TDynamicVector<int> vector_row1(row1, 4);
    TDynamicVector<int> vector_row2(row2, 4);
    TDynamicVector<int> vector_row3(row3, 4);
    TDynamicVector<int> vector_row4(row4, 4);

    TDynamicVector<int> input_vector(vector_elements, 5);

    delete[] row1;
    delete[] row2;
    delete[] row3;
    delete[] row4;

    delete[] vector_elements;

    original_matrix[0] = vector_row1;
    original_matrix[1] = vector_row2;
    original_matrix[2] = vector_row3;
    original_matrix[3] = vector_row4;

    ASSERT_ANY_THROW(original_matrix * input_vector);
}
TEST(TDynamicMatrix, can_multiply_matrix_by_matrix_with_correct_size) {

    TDynamicMatrix<int> original_matrix(4);
    TDynamicMatrix<int> multiplier_matrix(4);
    TDynamicMatrix<int> result_matrix(4);

    int* row1 = new int [4] { 1, 1, 2, 1};
    int* row2 = new int [4] { 1, 2, 1, 1};
    int* row3 = new int [4] { 1, 2, 2, 4};
    int* row4 = new int [4] { 2, 2, 3, 3};

    int* multiplier_row1 = new int [4] { 3, 5, 7, 1};
    int* multiplier_row2 = new int [4] { 9, 1, 3, 1};
    int* multiplier_row3 = new int [4] { 5, 1, 1, 1};
    int* multiplier_row4 = new int [4] { 5, 1, 9, 1};

    int* expected_row1 = new int [4] { 27, 9, 21, 5};
    int* expected_row2 = new int [4] { 31, 9, 23, 5};
    int* expected_row3 = new int [4] { 51, 13, 51, 9};
    int* expected_row4 = new int [4] { 54, 18, 50, 10};

    TDynamicVector<int> vector_row1(row1, 4);
    TDynamicVector<int> vector_row2(row2, 4);
    TDynamicVector<int> vector_row3(row3, 4);
    TDynamicVector<int> vector_row4(row4, 4);

    TDynamicVector<int> multiplier_vector_row1(multiplier_row1, 4);
    TDynamicVector<int> multiplier_vector_row2(multiplier_row2, 4);
    TDynamicVector<int> multiplier_vector_row3(multiplier_row3, 4);
    TDynamicVector<int> multiplier_vector_row4(multiplier_row4, 4);

    TDynamicVector<int> expected_vector_row1(expected_row1, 4);
    TDynamicVector<int> expected_vector_row2(expected_row2, 4);
    TDynamicVector<int> expected_vector_row3(expected_row3, 4);
    TDynamicVector<int> expected_vector_row4(expected_row4, 4);

    delete[] row1;
    delete[] row2;
    delete[] row3;
    delete[] row4;

    delete[] multiplier_row1;
    delete[] multiplier_row2;
    delete[] multiplier_row3;
    delete[] multiplier_row4;

    delete[] expected_row1;
    delete[] expected_row2;
    delete[] expected_row3;
    delete[] expected_row4;

    original_matrix[0] = vector_row1;
    original_matrix[1] = vector_row2;
    original_matrix[2] = vector_row3;
    original_matrix[3] = vector_row4;

    multiplier_matrix[0] = multiplier_vector_row1;
    multiplier_matrix[1] = multiplier_vector_row2;
    multiplier_matrix[2] = multiplier_vector_row3;
    multiplier_matrix[3] = multiplier_vector_row4;

    result_matrix[0] = expected_vector_row1;
    result_matrix[1] = expected_vector_row2;
    result_matrix[2] = expected_vector_row3;
    result_matrix[3] = expected_vector_row4;

    EXPECT_EQ(original_matrix * multiplier_matrix, result_matrix);
}
TEST(TDynamicMatrix, cant_multiply_matrix_by_matrix_with_incorrect_size) {

    TDynamicMatrix<int> original_matrix(4);
    TDynamicMatrix<int> multiplier_matrix(5);

    int* row1 = new int [4] { 2, 4, 6, 8};
    int* row2 = new int [4] { 10, 12, 14, 16};
    int* row3 = new int [4] { 18, 20, 22, 24};
    int* row4 = new int [4] { 26, 28, 30, 32};

    int* multiplier_row1 = new int [5] { 3, 5, 7, 9, 11};
    int* multiplier_row2 = new int [5] { 13, 15, 17, 19, 21};
    int* multiplier_row3 = new int [5] { 23, 25, 27, 29, 31};
    int* multiplier_row4 = new int [5] { 33, 35, 37, 39, 41};
    int* multiplier_row5 = new int [5] { 43, 45, 47, 49, 51};

    TDynamicVector<int> vector_row1(row1, 4);
    TDynamicVector<int> vector_row2(row2, 4);
    TDynamicVector<int> vector_row3(row3, 4);
    TDynamicVector<int> vector_row4(row4, 4);

    TDynamicVector<int> multiplier_vector_row1(multiplier_row1, 5);
    TDynamicVector<int> multiplier_vector_row2(multiplier_row2, 5);
    TDynamicVector<int> multiplier_vector_row3(multiplier_row3, 5);
    TDynamicVector<int> multiplier_vector_row4(multiplier_row4, 5);
    TDynamicVector<int> multiplier_vector_row5(multiplier_row5, 5);

    delete[] row1;
    delete[] row2;
    delete[] row3;
    delete[] row4;

    delete[] multiplier_row1;
    delete[] multiplier_row2;
    delete[] multiplier_row3;
    delete[] multiplier_row4;
    delete[] multiplier_row5;

    original_matrix[0] = vector_row1;
    original_matrix[1] = vector_row2;
    original_matrix[2] = vector_row3;
    original_matrix[3] = vector_row4;

    multiplier_matrix[0] = multiplier_vector_row1;
    multiplier_matrix[1] = multiplier_vector_row2;
    multiplier_matrix[2] = multiplier_vector_row3;
    multiplier_matrix[3] = multiplier_vector_row4;
    multiplier_matrix[4] = multiplier_vector_row5;

    ASSERT_ANY_THROW(original_matrix * multiplier_matrix);
}
