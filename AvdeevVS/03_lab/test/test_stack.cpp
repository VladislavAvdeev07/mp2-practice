#include "stack.h"

#include <gtest\gtest.h>

TEST(TStack, can_create_stack_with_positive_length)
{
  ASSERT_NO_THROW(TStack<int> st(5));
}

TEST(TStackr, cant_create_too_large_stack)
{
  ASSERT_ANY_THROW(TStack<int> st(MAX_STACK_SIZE + 1));
}

TEST(TStack, throws_when_create_stack_with_negative_length)
{
  ASSERT_ANY_THROW(TStack<int> st(-5));
}

TEST(TStack, can_create_copied_stack)
{
  TStack<int> st(10);

  ASSERT_NO_THROW(TStack<int> st1(st));
}

TEST(TStack, copied_vector_is_equal_to_source_one)
{
  TStack<int> st1(3);
  st1.push(0), st1.push(1), st1.push(3);
  TStack<int> st2(st1);
  EXPECT_EQ(st1,st2);
}

TEST(TStack, copied_vector_has_its_own_memory)
{
  TStack<int> st1(3);
  st1.push(0), st1.push(1), st1.push(3);
  TStack<int> st2(st1);
  st2.pop();
  EXPECT_FALSE(st1 == st2);
}

TEST(TStack, can_get_top_element)
{
  TStack<int> st1(3);
  st1.push(0), st1.push(1), st1.push(3);
  EXPECT_EQ(3, st1.top());
}

TEST(TStack, can_assign_stack_to_itself)
{
  TStack<int> st1(3);
  st1.push(0), st1.push(1), st1.push(3);
  ASSERT_NO_THROW(st1 = st1);
}

TEST(TStack, can_assign_stacks_of_equal_size)
{
  TStack<int> st1(3),st2(3);
  st1.push(0), st1.push(1), st1.push(3);
  st2.push(1), st2.push(2), st2.push(4);
  ASSERT_NO_THROW(st1 = st2);
}

TEST(TStack, compare_equal_stacks_return_true)
{
  TStack<int> st1(3), st2(3);
  st1.push(0), st1.push(1), st1.push(3);
  st2.push(1), st2.push(2), st2.push(4);
  EXPECT_TRUE(st1 == st2);
}

TEST(TStack, compare_stack_with_itself_return_true)
{
  TStack<int> st1(3);
  st1.push(0), st1.push(1), st1.push(3);
  EXPECT_TRUE(st1 == st1);
}

TEST(TStack, vectors_with_different_size_are_not_equal)
{
  TStack<int> st1(3), st2(4);
  EXPECT_FALSE(st1 == st2);
}

TEST(TStack, checking_stack_for_emptiness_return_true)
{
  TStack<int> st1(3);
  EXPECT_TRUE(st1.is_empty());
}

TEST(TStack, checking_stack_for_fullness_return_true)
{
  TStack<int> st1(3);
  st1.push(0), st1.push(1), st1.push(3);
  EXPECT_TRUE(st1.is_full());
}