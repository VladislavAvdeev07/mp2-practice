// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
    this->sz = v.sz;
    pMem = new T[this->sz];
    for (size_t i = 0; i < this->sz; i++) {
      pMem[i] = v.pMem[i];
    }
    //copy(v.pMem, v.pMem + v.sz, this->pMem);
    
      //throw "Method is not implemented";
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
    this->sz = v.sz;
    this->pMem = v.pMem;
    v.pMem = nullptr;
    v.sz = 0;
  }
  ~TDynamicVector() { delete[] this->pMem; }

  TDynamicVector& operator=(const TDynamicVector& v)
  {
    if (this == &v) return *this;
    if (this->sz != v.sz) {
      delete[] this->pMem;
      this->pMem = new T[v.sz];
    }
    this->sz = v.sz;
    for (size_t i = 0; i < this->sz; i++) {
      pMem[i] = v.pMem[i];
    }
    //copy(v.pMem, v.pMem-v.sz,this->pMem);
    return *this;

      //throw "Method is not implemented";
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
    if (this == &v) return *this;
    delete[] this->pMem;
    this->sz = v.sz;
    this->pMem = v.pMem;
    v.pMem = nullptr;
    v.sz = 0;
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
    return pMem[ind];
      //throw "Method is not implemented";
  }
  const T& operator[](size_t ind) const
  {
    return pMem[ind];
      //throw "Method is not implemented";
  }
  // индексация с контролем
  T& at(size_t ind)
  {
    if (ind >= this->sz) throw out_of_range("Invalid vector element index");
    return pMem[ind];
      //throw "Method is not implemented";
  }
  const T& at(size_t ind) const
  {
    if (ind >= this->sz) throw out_of_range("Invalid vector element index");
    return pMem[ind];
      //throw "Method is not implemented";
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
    if (this->sz != v.sz) return false;
    for (size_t i = 0; i < this->sz; i++) {
      if (pMem[i] != v.pMem[i]) return false;
    }
    return true;
    //return equal(pMem, pMem + sz, v.pMem);
    
      //throw "Method is not implemented";
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
    return !(*this == v);

      //throw "Method is not implemented";
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
    TDynamicVector<T> res(*this);
    for (size_t i = 0; i < res.sz; i++) {
      res.pMem[i] += val;
    }
    return res;
      //throw "Method is not implemented";
  }
  TDynamicVector operator-(T val)
  {
    TDynamicVector<T> res(*this);
    for (size_t i = 0; i < res.sz; i++) {
      res.pMem[i] -= val;
    }
    return res;
    //return (*this + ((-1)*val));
    
    //throw "Method is not implemented";
  }
  TDynamicVector operator*(T val)
  {
    TDynamicVector<T> res(*this);
    for (size_t i = 0; i < res.sz; i++) {
      res.pMem[i] *= val;
    }
    return res;
      //throw "Method is not implemented";
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
    if (this->sz != v.sz) throw invalid_argument("Addition of vectors of different lengths");
    TDynamicVector<T> res(*this);
    for (size_t i = 0; i < res.sz; i++) {
      res.pMem[i] += v.pMem[i];
    }
    return res;
      //throw "Method is not implemented";
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
    if (this->sz != v.sz) throw invalid_argument("Subtraction of vectors of different lengths");
    TDynamicVector<T> res(*this);
    for (size_t i = 0; i < res.sz; i++) {
      res.pMem[i] -= v.pMem[i];
    }
    return res;
    //return (*this + ((-1)*v));

    //throw "Method is not implemented";
  }
  T operator*(const TDynamicVector& v) //noexcept(noexcept(T()))
  {
    if (this->sz != v.sz) throw invalid_argument("The dot product for vectors of different lengths");
    T res{};
    for (size_t i = 0; i < this->sz; i++) {
      res += pMem[i] * v.pMem[i];
    }
    return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      throw "Method is not implemented";
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      throw "Method is not implemented";
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      throw "Method is not implemented";
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      throw "Method is not implemented";
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      throw "Method is not implemented";
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      throw "Method is not implemented";
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      throw "Method is not implemented";
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      throw "Method is not implemented";
  }
};

#endif __TDynamicMatrix_H__
