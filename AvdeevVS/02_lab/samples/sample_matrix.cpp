// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
// Тестирование матриц

#include <iostream>
#include "tmatrix.h"
//---------------------------------------------------------------------------

void main()
{
  try {
    system("color F0"); //5-violet 0-black
    setlocale(LC_ALL, "Russian");

    TDynamicMatrix<int> a(5), b(5), c(5);
    int i, j;

    cout << "Тестирование класса работы с матрицами" << endl;
    for (i = 0; i < 5; i++)
      for (j = i; j < 5; j++)
      {
        a[i][j] = i * 10 + j;
        b[i][j] = (i * 10 + j) * 100;
      }
    c = a + b;
    cout << "Matrix a = " << endl << a << endl;
    cout << "Matrix b = " << endl << b << endl;
    cout << "Matrix c = a + b" << endl << c << endl;
  }
  catch (const char* msg)
  {
    std::cerr << "Строковое исключение: " << msg << '\n';
  }
}
//---------------------------------------------------------------------------
