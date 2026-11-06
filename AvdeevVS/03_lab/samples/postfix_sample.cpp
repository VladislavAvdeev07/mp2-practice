#include <iostream>
#include <limits>
#include "stack.h"
#include "postfix_form.h"

using namespace std;

int main()
{
  try {
    system("color F0"); //5-violet 0-black
    setlocale(LC_ALL, "Russian");

    cout << endl << " Тестирование работы с классом TStack:" << endl << endl;

    TStack<int> st1(5), st2(5);
    for (int i = 0; i < 4; i++) {
      st1.push(i);
      st2.push(i + 1);
    }
    cout << "  Stack st1 = " << st1 << endl;
    cout << "  Stack st2 = " << st2 << endl;
    bool flag = (st1 == st2);
    cout << "  st1==st2? --> " << boolalpha << flag << endl;
    st1 = st2;
    flag = (st1 == st2);
    cout << "  after st1=st2 --> st1==st2? --> " << boolalpha << flag << endl;

    cout << endl << "================================================================" << endl;
    cout << endl << " Тестирование работы с классом ArExpression:" << endl << endl;
    bool flag1 = true;
    while (flag1) {
      string ex;
      cout << endl << " Введи математическое выражение (только латиница):  ";
      getline(cin, ex);
      if (ex.empty()) continue;
      ArExpression ae(ex);
      cout << endl << " Постфиксная форма --> " << ae.GetPostfix()<< endl;
      bool flag2 = true;
      cout << endl << " Будем вычислять значение? (1 - да, 0 - нет) --> " ;
      cin >> flag2;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      while (flag2) {
        cout << endl << " Введи значения для вычисления: (закончил вводить --> ctrl+z) " << endl;
        vector <pair<char, double>> fill;
        Vector_Filling(fill);
        if (cin.fail()) {
          cin.clear();
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl << " Значение функции в данной точке --> " << fixed << setprecision(2) <<
          ae.Compute(fill)<<endl<<endl;
        cout << " Продолжаем с этой функцией для других значений? (1 - да, 0 - нет) --> ";
        cin >> flag2;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
      }
      cout << endl << " Придумаем новую функцию? (1 - да, 0 - нет) --> ";
      cin >> flag1;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << endl << "============================The End!!!===============================";

  }
  catch (const exception& e) {
    cerr << "Fatal --> " << e.what() << endl;
  }
  return 0; 
}
