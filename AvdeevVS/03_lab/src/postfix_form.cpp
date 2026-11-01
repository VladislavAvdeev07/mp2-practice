#include "postfix_form.h"

bool ArExpression::Mathematically_Correct(const string& s) {
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
