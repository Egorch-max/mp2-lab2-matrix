#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
    int* pmem0 = new int[5] {5, 1, 2, 5, 3};

    TDynamicVector<int> vec_0(pmem0, 5);

    TDynamicVector<int> v_copy(vec_0);


    delete[] pmem0;

    EXPECT_EQ(vec_0, v_copy);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	int* pmem0 = new int[5] {5, 1, 2, 5, 3};

	TDynamicVector<int> v(pmem0, 5);
	TDynamicVector<int> v_copy(v);

	TDynamicVector<int>* V = &v;
	TDynamicVector<int>* V_copy = &v_copy;

	delete[] pmem0;

	EXPECT_NE(V, V_copy);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
  TDynamicVector<int> v(4);
  v[0] = 4;

  EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	const int size = 3;

	TDynamicVector<int> v1(size);

	ASSERT_ANY_THROW(v1.at(-1));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	const int size = 3;

	TDynamicVector<int> v1(size);

	ASSERT_ANY_THROW(v1.at(100));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	const int size = 3;

	TDynamicVector<int> v1(size);

	v1[0] = 5; 
	v1[1] = 4; 
	v1[2] = 3;

	TDynamicVector<int> v2(size);

	v2[0] = 5; 
	v2[1] = 4; 
	v2[2] = 3;

	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	const int size = 3;

	TDynamicVector<int> v1(size);

	v1[0] = 5;
	v1[1] = 4; 
	v1[2] = 3;

	TDynamicVector<int> v2(size);

	v2 = v1;

	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	const int size1 = 3;

	const int size2 = 4;

	TDynamicVector<int> v1(size1);

	TDynamicVector<int> v2(size2);

	v2 = v1;

	ASSERT_NE(v2.size(), size2);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	const int size1 = 3;

	const int size2 = 4;

	TDynamicVector<int> v1(size1);

	TDynamicVector<int> v2(size2);

	v2 = v1;

	ASSERT_EQ(v1, v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	const int size = 3;

	TDynamicVector<int> v1(size);

	v1[0] = 5; 
	v1[1] = 4; 
	v1[2] = 3;

	TDynamicVector<int> v2(size);

	v2[0] = 5; 
	v2[1] = 4; 
	v2[2] = 3;

	ASSERT_EQ(v1 == v2, true);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	const int size = 3;

	TDynamicVector<int> v1(size);

	v1[0] = 5; 
	v1[1] = 4; 
	v1[2] = 3;

	ASSERT_EQ(v1 == v1, true);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	const int size = 3;

	TDynamicVector<int> v1(size);

	v1[0] = 5; 
	v1[1] = 4; 
	v1[2] = 3;

	TDynamicVector<int> v2(size + 2);

	v2[0] = 1; 
	v2[1] = 2; 
	v2[2] = 3; 
	v2[3] = 4;
	v2[4] = 5;

	ASSERT_NE(v1, v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	const int size = 3;

	TDynamicVector<int> v1(size);

	v1[0] = 5; 
	v1[1] = 4; 
	v1[2] = 3;

	TDynamicVector<int> res(size);

	const int number = 5;

	res = v1 + number;

	TDynamicVector<int> v2(size);

	v2[0] = 10;
	v2[1] = 9; 
	v2[2] = 8;

	ASSERT_EQ(res, v2);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	const int size = 3;

	TDynamicVector<int> v1(size);

	v1[0] = 5;
	v1[1] = 4; 
	v1[2] = 3;


	TDynamicVector<int> res(size);

	const int number = 2;

	res = v1 - number;

	TDynamicVector<int> v2(size);

	v2[0] = 3; 
	v2[1] = 2; 
	v2[2] = 1;

	ASSERT_EQ(res, v2);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	const int size = 3;

	TDynamicVector<int> v1(size);

	v1[0] = 5;
	v1[1] = 4;
	v1[2] = 3;

	TDynamicVector<int> res(size);

	const int number = 2;

	res = v1 * number;

	TDynamicVector<int> v2(size);

	v2[0] = 10;
	v2[1] = 8; 
	v2[2] = 6;

	ASSERT_EQ(res, v2);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	const int size = 3;

	TDynamicVector<int> v1(size);

	v1[0] = 5;
	v1[1] = 4; 
	v1[2] = 3;

	TDynamicVector<int> v2(size);

	v2[0] = 1;
	v2[1] = 2;
	v2[2] = 3;

	TDynamicVector<int> res(size);

	res[0] = 6; 
	res[1] = 6; 
	res[2] = 6;

	ASSERT_EQ(v1 + v2, res);

}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	const int size = 3;

	TDynamicVector<int> v1(size);

	v1[0] = 5;
	v1[1] = 4; 
	v1[2] = 3;

	TDynamicVector<int> v2(size + 2);

	v2[0] = 1; 
	v2[1] = 2; 
	v2[2] = 3;
	v2[3] = 4;
	v2[4] = 5;

	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	const int size = 3;

	TDynamicVector<int> v1(size);

	v1[0] = 5;
	v1[1] = 4; 
	v1[2] = 3;

	TDynamicVector<int> v2(size);

	v2[0] = 1;
	v2[1] = 2;
	v2[2] = 3;

	TDynamicVector<int> res(size);

	res[0] = 4;
	res[1] = 2;
	res[2] = 0;

	ASSERT_EQ(v1 - v2, res);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	const int size = 3;

	TDynamicVector<int> v1(size);

	v1[0] = 5;
	v1[1] = 4; 
	v1[2] = 3;

	TDynamicVector<int> v2(size + 2);

	v2[0] = 1; 
	v2[1] = 2; 
	v2[2] = 3; 
	v2[3] = 4;
	v2[4] = 5;

	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	const int size = 3;

	TDynamicVector<int> v1(size);

	v1[0] = 5;
	v1[1] = 4;
	v1[2] = 3;

	TDynamicVector<int> v2(size);

	v2[0] = 1; 
	v2[1] = 2; 
	v2[2] = 3;

	int res = 5 + 8 + 9;

	ASSERT_EQ(v1 * v2, res);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	const int size = 3;

	TDynamicVector<int> v1(size);

	v1[0] = 5;
	v1[1] = 4; 
	v1[2] = 3;

	TDynamicVector<int> v2(size + 2);

	v2[0] = 1;
	v2[1] = 2; 
	v2[2] = 3; 
	v2[3] = 4; 
	v2[4] = 5;

	ASSERT_ANY_THROW(v1 * v2);
}

