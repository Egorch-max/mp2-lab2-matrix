#include "tmatrix.h"
#include <gtest.h>

template <typename T>

class TestTDynamicVector : public ::testing::Test
{
public:
	TDynamicVector<T>* v;
	TDynamicVector<T>* v0;
	TDynamicVector<T>* v1;
	TDynamicVector<T>* v2;
	T* tmp1;
	T* tmp2;

	void SetUp()
	{
		tmp1 = new T[10]{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

		v1 = new TDynamicVector<T>(tmp1, 10);

	
		tmp2= new T[10]{ 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

		v2 = new TDynamicVector<T>(tmp2, 10);

		v = new TDynamicVector<T>(*v1);

		v0 = nullptr;
	}
	void TearDown()
	{
		delete v;
		delete v0;
		delete v1;
		delete v2;
		delete[] tmp1;
		tmp1 = nullptr;
		delete[] tmp2;
		tmp2 = nullptr;

	}

	void BuildDynamicVector(size_t s = 5)
	{
		v = new TDynamicVector<T>(s);
		v0 = new TDynamicVector<T>(*v);

	}
};

TYPED_TEST_CASE_P(TestTDynamicVector);

TYPED_TEST_P(TestTDynamicVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(this->BuildDynamicVector(1));
}

TYPED_TEST_P(TestTDynamicVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(this->BuildDynamicVector(MAX_VECTOR_SIZE + 1));
}

TYPED_TEST_P(TestTDynamicVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(this->BuildDynamicVector(-5));
}

TYPED_TEST_P(TestTDynamicVector, can_create_copied_vector)
{
	ASSERT_NO_THROW(this->BuildDynamicVector());
}

TYPED_TEST_P(TestTDynamicVector, copied_vector_is_equal_to_source_one)
{
	EXPECT_EQ((*(this->v)), (*(this->v1)));
}

TYPED_TEST_P(TestTDynamicVector, copied_vector_has_its_own_memory)
{
	EXPECT_NE((this->v), (this->v1));
}

TYPED_TEST_P(TestTDynamicVector, can_get_size)
{
	EXPECT_EQ(10, (this->v->size()));
}

TYPED_TEST_P(TestTDynamicVector, can_set_and_get_element)
{
	this->v[0][0] = 4;

	EXPECT_EQ((this->v[0][0]), 4);
}

TYPED_TEST_P(TestTDynamicVector, throws_when_set_element_with_negative_index)
{
	ASSERT_ANY_THROW(this->v->at(-1) = 4);
}

TYPED_TEST_P(TestTDynamicVector, throws_when_set_element_with_too_large_index)
{
	ASSERT_ANY_THROW(this->v->at(50));
}

TYPED_TEST_P(TestTDynamicVector, can_assign_vector_to_itself)
{
	*(this->v) = *(this->v);

	EXPECT_EQ(*(this->v), *(this->v));
}

TYPED_TEST_P(TestTDynamicVector, can_assign_vectors_of_equal_size)
{
	*(this->v) = *(this->v2);

	EXPECT_EQ(*(this->v), *(this->v2));
}


REGISTER_TYPED_TEST_CASE_P(TestTDynamicVector, can_create_vector_with_positive_length, cant_create_too_large_vector, throws_when_create_vector_with_negative_length,
	can_create_copied_vector, copied_vector_is_equal_to_source_one, copied_vector_has_its_own_memory, can_get_size, can_set_and_get_element, throws_when_set_element_with_negative_index,
	throws_when_set_element_with_too_large_index, can_assign_vector_to_itself, can_assign_vectors_of_equal_size);

typedef::testing::Types<int, double> VectorTypes;

INSTANTIATE_TYPED_TEST_CASE_P(VectorTypesInstantiation, TestTDynamicVector, VectorTypes);


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