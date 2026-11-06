#include "postfix_form.h"

bool isoperation(char c) {
  string operation = "+-*/";
  return operation.find(c) != string::npos;
}

bool Mathematically_Correct(const string& s)  {
  if (s.empty()) return false;
  if (s.size() == 1 && !isalpha(s[0])) return false;
  TStack<char> bracket(s.size());
  string br = "()";
  for (int i = 0; i < s.size(); i++) {      //bracketed sequence
    if (!isalpha(s[i])&&(!isoperation(s[i])) && (br.find(s[i]) == string::npos))
      return false;

    if (s[i] == '(') bracket.push(s[i]);
    if (s[i] == ')') {
      if (bracket.is_empty()) return false;
      bracket.pop();
    }
  }
  if (!bracket.is_empty()) return false;
  //------------------------------------
  for (int i = 0; i < s.size()-1; i++) {    // AA | ++ | -- | ** | // | () | +) | -) | *) | /) | (+ | (* | (/
    if (isoperation(s[i]) && isoperation(s[i+1])) return false;
    if (isalpha(s[i])&& isalpha(s[i+1])) return false;
    if (s[i] == '(' && s[i + 1] == ')') return false;
    if (isoperation(s[i]) && s[i + 1] == ')') return false;
    if (s[i] == '(' && isoperation(s[i + 1]) && s[i+1]!='-') return false;
    if (isalpha(s[i]) && s[i+1] == '(') return false;
    if (s[i] == ')' && isalpha(s[i + 1])) return false;
   }
  //------------------------------------
  if (isoperation(s[0]) && s[0] != '-') return false; //front and back of s
  if (isoperation(s[s.size()-1])) return false;
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
  string umexpr = expr;
  if (umexpr[0] == '-') umexpr = '0' + umexpr; //unary minus
  for (int i = 0; i < umexpr.size() - 1; i++) {
    if (umexpr[i] == '(' && umexpr[i + 1] == '-') umexpr.insert(i + 1, "0");
  }

  string pf;
  pf.reserve(umexpr.size());
  TStack<char> oper(umexpr.size());
  for (int i = 0; i < umexpr.size(); i++) {
    if (isalpha(umexpr[i]) || isdigit(umexpr[i])) pf += umexpr[i];
    if (umexpr[i] == '(') oper.push(umexpr[i]);
    if (umexpr[i] == '+' || umexpr[i] == '-') {
      while (!oper.is_empty() && (oper.top() == '*' || oper.top() == '/'||
        oper.top() == '+' || oper.top() == '-')) {
        pf += oper.top();
        oper.pop();
      }
      oper.push(umexpr[i]);
    }
    if (umexpr[i] == ')') {
      while (!oper.is_empty() && oper.top() != '(') {
        pf += oper.top();
        oper.pop();
      }
      if (!oper.is_empty() && oper.top() == '(') oper.pop();
    }
    if (umexpr[i] == '*' || umexpr[i] == '/') {
      while (!oper.is_empty() && (oper.top() == '*' || oper.top() == '/')) {
        pf += oper.top();
        oper.pop();
      }
      oper.push(umexpr[i]);
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
    if (isdigit(pfex[i])) {
      st.push(pfex[i] - '0');
    }
    else if (isalpha(pfex[i])) {
      bool found = false;
      for (int j = 0; j < v.size(); j++) {
        if (v[j].first == pfex[i]) {
          st.push(v[j].second);
          found = true;
          break;
        }
      }
      if (!found) throw invalid_argument("There is no required value");
    }
    else {
      double arg1, arg2; 
      if (!st.is_empty()) {
        arg2 = st.top();
        st.pop();
      }
      if (!st.is_empty()) {
        arg1 = st.top();
        st.pop();
      }
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