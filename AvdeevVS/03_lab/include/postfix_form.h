#ifndef __POSTFIX_FORM_H__
#define __POSTFIX_FORM_H__

#include "stack.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class ArExpression {

  string expr;

  bool Mathematically_Correct(const string&);

public:
  explicit ArExpression(const string&);
  //bool operator==(const ArExpression& ae) const noexcept;
  const string& GetPostfix() const;
  double Compute(const vector<pair<char, double>>&) const;
  friend std::istream& operator>>(std::istream& in, ArExpression& ae);
  friend std::ostream& operator<<(std::ostream& out, const ArExpression& ae);
};

#endif __POSTFIX_FORM_H__