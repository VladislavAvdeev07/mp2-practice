//===================================================
#ifndef __TSTACK_H__
#define __TSTACK_H__

#include <iostream>

using namespace std;

const int MAX_STACK_SIZE = 1000000;
const int ORIGIN_FIRST_INDEX = -1;

template<typename T>
class TStack {

  int size;
  int top_ind;
  T* pMem;

public:
  TStack(int s) {
    if (s > MAX_STACK_SIZE) throw length_error("The stack size is too large");
    if(s <= 0 ) throw length_error("The stack size is less than zero or zero");
    this->size = s;
    this->top_ind = ORIGIN_FIRST_INDEX;
    this->pMem = new T[size]{};
  }
  TStack(const TStack<T>& st) {
    this->size = st.size;
    this->top_ind = st.top_ind;
    this->pMem = new T[size];
    if (top_ind != -1)
    for (int i = 0; i <= top_ind; i++) 
      pMem[i] = st.pMem[i];
  }
  TStack(TStack<T>&& st) noexcept {
    this->size = st.size;
    this->top_ind = st.top_ind;
    pMem = st.pMem;
    st.pMem = nullptr;
    st.size = 0;
    st.top_ind = ORIGIN_FIRST_INDEX;
  }
  ~TStack() { delete[] this->pMem; }
  void push(const T& x) {
    if (is_full()) throw out_of_range("push::The stack is full");
    pMem[++top_ind] = x;
  }
  void pop() {
    if (is_empty()) throw out_of_range("pop::The stack is empty");
    this->top_ind--;
  }
  T top() {
    if (is_empty()) throw out_of_range("top::The stack is empty");
    return pMem[top_ind];
  }
  bool is_full() const noexcept {
    return top_ind == size - 1;
  }
  bool is_empty() const noexcept {
    return top_ind == ORIGIN_FIRST_INDEX;
  }
  bool operator==(const TStack& st) const noexcept {
    if (size != st.size || top_ind != st.top_ind) return false;
    for (int i = 0; i <= top_ind; i++) {
      if (pMem[i] != st.pMem[i])  return false;
    }
    return true;
  }
  TStack<T>& operator= (const TStack<T>& st) {
    if (this == &st) return *this;
    if (this->size != st.size) {
      delete[] this->pMem;
      this->pMem = new T[st.size];
    }
    this->size = st.size;
    this->top_ind = st.top_ind;
    for (int i = 0; i <= top_ind; i++) {
      pMem[i] = st.pMem[i];
    }
    return *this;
  }
  TStack<T>& operator= (TStack<T>&& st) noexcept {
    if (this == &st) return *this;
    this->size = st.size;
    this->top_ind = st.top_ind;
    delete[] this->pMem;
    this->pMem = st.pMem;
    st.pMem = nullptr;
    st.size = 0;
    st.top_ind = ORIGIN_FIRST_INDEX;
    return *this;
  }
  friend ostream& operator<<(ostream& out, const TStack& st) {
    if (st.is_empty()) {
      out << "[ ]";
      return out;
    }
    out << "[ ";
    for (int i = 0; i <= st.top_ind; i++) {
      if (i != st.top_ind) out << st.pMem[i] << ", ";
      else out << st.pMem[i] << " ";
    }
    out << "]";
    return out;
  }
};



#endif __TSTACK_H__