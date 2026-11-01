#include "postfix_form.h"

bool Mathematically_Correct(const string& s)  {
  if (s.empty()) return false;
  if (s.size() == 1 && !isalpha(s[0])) return false;
  TStack<char> bracket(s.size());
  string operation = "+-*/";
  string br = "()";
  for (int i = 0; i < s.size(); i++) {      //bracketed sequence
    if (!isalpha(s[i])&&(operation.find(s[i]) == string::npos)&& (br.find(s[i]) == string::npos))
      return false;
    if (s[i] == '(') bracket.push(s[i]);
    if (s[i] == ')') {
      if (bracket.is_empty()) return false;
      bracket.pop();
    }
  }
  if (!bracket.is_empty()) return false;
  //------------------------------------
  for (int i = 0; i < s.size()-1; i++) {    //two operations or operands in a row, () and +),-),*),/),(+,(*,(/
    if ((operation.find(s[i]) != string::npos) && (operation.find(s[i + 1]) != string::npos))
       return false;
    if(isalpha(s[i])&& isalpha(s[i+1])) return false;
    if (s[i] == '(' && s[i + 1] == ')') return false;
    if ((operation.find(s[i]) != string::npos) && s[i + 1] == ')') return false;
    if (s[i] == '(' && (operation.find(s[i+1]) != string::npos) && s[i+1]!='-') return false;
    if (isalpha(s[i]) && s[i+1] == '(') return false;
    if (s[i] == ')' && isalpha(s[i + 1])) return false;
   }
  if (s.size()>2)
  for (int i = 0; i < s.size() - 2; i++) {  
    if (s[i] == '(' && s[i + 1] == '-' && s[i + 2] == ')') return false;
  }
  //------------------------------------
  if ((operation.find(s[0]) != string::npos) && s[0] != '-') return false; //front and back of s
  if (operation.find(s[s.size()-1]) != string::npos) return false;
  return true;
}

ArExpression::ArExpression(const string& s) {
  string s_clean;
  s_clean.reserve(s.size());
  for (int i = 0; i < s.size(); i++) {
    if (s[i] != ' ') s_clean += s[i];
  }
  for (int i = 0; i < s_clean.size(); i++) {
    s_clean[i] = toupper(s_clean[i]);
  }
  if (!Mathematically_Correct(s_clean)) throw invalid_argument("The expression is mathematically incorrect");
  this->expr = s_clean;
}

string ArExpression::GetPostfix() const {
  string pf;
  pf.reserve(expr.size());
  TStack<char> oper(expr.size());
  for (int i = 0; i < expr.size(); i++) {
    if (isalpha(expr[i])) pf += expr[i];
    if (expr[i] == '(') oper.push(expr[i]);
    if (expr[i] == '+' || expr[i] == '-') {
      while (!oper.is_empty() && (oper.top() == '*' || oper.top() == '/'||
        oper.top() == '+' || oper.top() == '-')) {
        pf += oper.top();
        oper.pop();
      }
      oper.push(expr[i]);
    }
    if (expr[i] == ')') {
      while (!oper.is_empty() && oper.top() != '(') {
        pf += oper.top();
        oper.pop();
      }
      if (!oper.is_empty() && oper.top() == '(') oper.pop();
    }
    if (expr[i] == '*' || expr[i] == '/') {
      while (!oper.is_empty() && (oper.top() == '*' || oper.top() == '/')) {
        pf += oper.top();
        oper.pop();
      }
      oper.push(expr[i]);
    }
  }
  while (!oper.is_empty()) {
    pf += oper.top();
    oper.pop();
   }
  return pf;
}

void Vector_Filling(vector<pair<char, double>>& vp) {
  char c;
  double d;
  pair<char, double> p;
  while (cin >> c >> d) {
    p = { toupper(c), d };
    vp.push_back(p);
  }
}

double ArExpression::Compute(const vector<pair<char, double>>& v) const {
  if (v.size() == 0) throw invalid_argument("Vector of meanings is empty");
  for (int i = 0; i < v.size(); i++) {
    for (int j = 0; j < v.size(); j++) {
      if (v[i].first == v[j].first && i != j) throw invalid_argument("Ambiguous meanings for expression");
    }
  }
  TStack<double> st(expr.size());
  string pfex = GetPostfix();
  for (int i = 0; i < pfex.size(); i++) {
    if (isalpha(pfex[i]))
      for (int j = 0; j < v.size(); j++) {
        if (v[j].first == pfex[i]) {
          st.push(v[j].second);
          break;
        }
        if(j==v.size()-1) throw invalid_argument("There is no required value");
      }
    else {
      double arg1, arg2; 
      arg2 = st.top();
      if (!st.is_empty()) st.pop();
      arg1 = st.top();
      if (!st.is_empty()) st.pop();
      switch (pfex[i]) {
        case '+':
          st.push(arg1 + arg2);
        break;
        case '-':
         st.push(arg1 - arg2);
          break;
        case '*':
          st.push(arg1 * arg2);
          break;
        case '/':
          if(arg2 == 0.0) throw domain_error("Division by zero");
          st.push(arg1 / arg2);
         break;
        default:
          throw invalid_argument("Unknown operation");
         break;
        }
    }
  }
  return st.top();
}