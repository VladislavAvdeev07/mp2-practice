#include "tmatrix.h"

#include <gtest\gtest.h>

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
  TDynamicVector<int> v(3);
  v[0] = 0; v[1] = 1; v[2] = 2;
  TDynamicVector<int> p(v);
  EXPECT_TRUE(p==v);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
  TDynamicVector<int> v(3);
  v[0] = 0; v[1] = 1; v[2] = 2;
  TDynamicVector<int> p(v);
  p[0] = 1;
  EXPECT_FALSE(p[0] == v[0]);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

//TEST(TDynamicVector, can_set_and_get_element)
//{
//  TDynamicVector<int> v(4);
//  v[0] = 4;
//
//  EXPECT_EQ(4, v[0]);
//}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
  TDynamicVector<int> v(10);
  EXPECT_ANY_THROW(v.at(-1));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
  TDynamicVector<int> v(10);
  ASSERT_ANY_THROW(v.at(11));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
  TDynamicVector<int> v(3);
  v[0] = 1; v[1] = 2; v[2] = 3;
  ASSERT_NO_THROW(v = v);
  EXPECT_EQ(1, v[0]);
  EXPECT_EQ(2, v[1]);
  EXPECT_EQ(3, v[2]);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
  TDynamicVector<int> v(3), p(3);
  v[0] = 1; v[1] = 2; v[2] = 3;
  p[0] = 4; p[1] = 5; p[2] = 6;
  v = p;
  EXPECT_EQ(4, v[0]);
  EXPECT_EQ(5, v[1]);
  EXPECT_EQ(6, v[2]);
  EXPECT_EQ(3, v.size());
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
  TDynamicVector<int> v(3),p(5);
  v = p;
  EXPECT_EQ(5, v);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
  TDynamicVector<int> v(4), p(3);
  v[0] = 1; v[1] = 2; v[2] = 3; v[3] = 0;
  p[0] = 4; p[1] = 5; p[2] = 6;
  v = p;
  EXPECT_EQ(4, v[0]);
  EXPECT_EQ(5, v[1]);
  EXPECT_EQ(6, v[2]);
  EXPECT_EQ(3, v.size());
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
  TDynamicVector<int> v(3), p(3);
  v[0] = 1; v[1] = 2; v[2] = 3;
  p[0] = 1; p[1] = 2; p[2] = 3;
  EXPECT_TRUE(p == v);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
  TDynamicVector<int> v(3);
  v[0] = 1; v[1] = 2; v[2] = 3;
  EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
  TDynamicVector<int> v(3), p(4);;
  EXPECT_TRUE(p != v);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
  TDynamicVector<int> v(3);
  TDynamicVector<int> p(3);
  v[0] = 1; v[1] = 1; v[2] = 1;
  int a = 7;
  p = v + a;
  EXPECT_TRUE(p[0] == 8);
  EXPECT_TRUE(p[1] == 8);
  EXPECT_TRUE(p[2] == 8);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
  TDynamicVector<int> v(3);
  TDynamicVector<int> p(3);
  v[0] = 2; v[1] = 3; v[2] = 4;
  int a = 1;
  p = v - a;
  EXPECT_TRUE(p[0] == 1);
  EXPECT_TRUE(p[1] == 2);
  EXPECT_TRUE(p[2] == 3);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
  TDynamicVector<int> v(3);
  TDynamicVector<int> p(3);
  v[0] = 1; v[1] = 2; v[2] = 3;
  int a = 2;
  p = v * a;
  EXPECT_TRUE(p[0] == 2);
  EXPECT_TRUE(p[1] == 4);
  EXPECT_TRUE(p[2] == 6);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
  TDynamicVector<int> v(3);
  TDynamicVector<int> p(3);
  TDynamicVector<int> res(3);
  v[0] = 1; v[1] = 2; v[2] = 3;
  p[0] = 1; p[1] = 2; p[2] = 3;
  res = v + p;
  EXPECT_TRUE(res[0] == 2);
  EXPECT_TRUE(res[1] == 4);
  EXPECT_TRUE(res[2] == 6);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
  TDynamicVector<int> v(3);
  TDynamicVector<int> p(4);
  ASSERT_ANY_THROW(p+v);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
  TDynamicVector<int> v(3);
  TDynamicVector<int> p(3);
  TDynamicVector<int> res(3);
  v[0] = 1; v[1] = 2; v[2] = 3;
  p[0] = 2; p[1] = 3; p[2] = 4;
  res = v - p;
  EXPECT_TRUE(res[0] == -1);
  EXPECT_TRUE(res[1] == -1);
  EXPECT_TRUE(res[2] == -1);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
  TDynamicVector<int> v(3);
  TDynamicVector<int> p(4);
  ASSERT_ANY_THROW(p - v);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
  TDynamicVector<int> v(3);
  TDynamicVector<int> p(3);
  int res = 0;
  v[0] = 1; v[1] = 2; v[2] = 3;
  p[0] = 2; p[1] = 3; p[2] = 4;
  res = p * v;
  EXPECT_EQ(res,20);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
  TDynamicVector<int> v(3);
  TDynamicVector<int> p(4);
  ASSERT_ANY_THROW(p * v);
}

