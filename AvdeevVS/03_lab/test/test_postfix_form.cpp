#include "postfix_form.h"

#include <gtest/gtest.h>

TEST(ArExpression, can_create_expression_with_positive_string)
{
  string s = "A+B-C";
  ASSERT_NO_THROW(ArExpression ae(s));
}

TEST(ArExpression, throws_when_create_expression_with_negative_string)
{
  string s = "+A+";
  ASSERT_ANY_THROW(ArExpression ae(s));
}

TEST(ArExpression, can_get_postfix_form)
{
  string s = "A+B-C";
  ArExpression ae(s);
  ASSERT_NO_THROW(ae.GetPostfix());
}

TEST(ArExpression, postfix_form_is_correct)
{
  string s = "A+B-C";
  ArExpression ae(s);
  ASSERT_EQ(ae.GetPostfix(),"AB+C-" );
}

TEST(ArExpression, can_get_the_value_of_expression)
{
  string s = "A+B-C";
  ArExpression ae(s);
  vector<pair<char, double>> fill = { {'A', 10.0}, {'B', 5.0}, {'C', 2.0} };
  ASSERT_NO_THROW(ae.Compute(fill));
}

TEST(ArExpression, the_value_of_expression_is_correct)
{
  string s = "A+B-C";
  ArExpression ae(s);
  vector<pair<char, double>> fill = { {'A', 10.0}, {'B', 5.0}, {'C', 2.0} };
  ASSERT_EQ(ae.Compute(fill),13.0);
}
//тесты на внешние функции 
TEST(ArExpression, correct_expression_return_true)
{
  string s = "A+B-C";
  ASSERT_TRUE(Mathematically_Correct(s));
}

TEST(ArExpression, uncorrect_expression_return_false)
{
  string s = "(A+B-C))";
  ASSERT_FALSE(Mathematically_Correct(s));
}

