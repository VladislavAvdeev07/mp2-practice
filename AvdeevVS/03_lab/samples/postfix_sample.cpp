#include <iostream>
#include "stack.h"
#include "postfix_form.h"

using namespace std;

int main()
{
  system("color F0"); //5-violet 0-black
  setlocale(LC_ALL, "Russian");

  cout <<endl<< " Тестирование работы с классом TStack:" << endl << endl;

  TStack<int> st1(5), st2(5);
  for (int i = 0; i < 4; i++) {
    st1.push(i);
    st2.push(i+1);
  }
  cout << "  Stack st1 = " << st1 << endl;
  cout << "  Stack st2 = " << st2 << endl;
  bool flag = (st1 == st2);
  cout << "  st1==st2? --> " << boolalpha << flag << endl;
  st1 = st2;
  flag = (st1 == st2);
  cout << "  after st1=st2 --> st1==st2? --> " << boolalpha << flag << endl;

  cout <<endl<< "================================================================" << endl;
  cout << endl << " Тестирование работы с классом Postfix_form:" << endl << endl;

  return 0;
}
