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
    sz = v.sz;
    pMem = new T[sz];
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
    std::swap(sz, v.sz);
    std::swap(pMem, v.pMem);
  }
  ~TDynamicVector()
  {
    delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
    if (this == &v)
      return *this;
    sz = v.sz;
    delete[] pMem;
    pMem = new T[sz];
    std::memcpy(pMem, v.pMem, sizeof(T) * sz);
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
    delete[] pMem;
    std::swap(sz, v.sz);
    std::swap(pMem, v.pMem);
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
    return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
    return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
    if (ind < 0 || ind >= sz)
      throw 1;
    return pMem[ind];
  }
  const T& at(size_t ind) const
  {
    if (ind < 0 || ind >= sz)
      throw 1;
    return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
    if (sz != v.sz)
      return false;
    return std::memcmp(pMem, v.pMem, sizeof(T) * sz) == 0;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
    return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
    TDynamicVector<T> tmp = *this;
    for (int i = 0; i < sz; ++i)
      tmp.pMem[i] += val;
    return tmp;
  }
  TDynamicVector operator-(T val)
  {
    TDynamicVector<T> tmp(sz) = *this;
    return tmp + (-val);
  }
  TDynamicVector operator*(T val)
  {
    TDynamicVector<T> tmp = *this;
    for (int i = 0; i < sz; ++i)
      tmp.pMem[i] *= val;
    return tmp;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
    if (sz != v.sz)
      throw 2;
    
    TDynamicVector<T> tmp = *this;
    for (int i = 0; i < sz; ++i)
      tmp.pMem[i] += v.pMem[i];
    
    return tmp;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
    if (sz != v.sz)
      throw 2;
    
    TDynamicVector<T> tmp = *this;
    for (int i = 0; i < sz; ++i)
      tmp.pMem[i] -= v.pMem[i];
    
    return tmp;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
    if (sz != v.sz)
      throw 2;
    
    TDynamicVector<T> tmp = *this;
    for (int i = 0; i < sz; ++i)
      tmp.pMem[i] *= v.pMem[i];
    
    return tmp;
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
      if (sz != m.sz)
          return false;
      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz; ++j)
              if (pMem[i][j] != m.pMem[i][j])
                  return false;
      }
      return true;
 }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix<T> tmp = *this;
      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz; ++j)
              tmp[i][j] = pMem[i][j] * val;
      }
      return tmp;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (v.size() != sz)
          throw 3;
      TDynamicVector<T> res(sz);
      for (int i = 0; i < sz; ++i) {
          T sum = 0;
          for (int j = 0; j < sz; ++j) {
              sum += pMem[i][j] * v[j];
          }
          res[i] = sum;
      }
      return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      TDynamicMatrix<T> tmp = *this;
      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz; ++j)
              tmp[i][j] = pMem[i][j] + m.pMem[i][j];
      }
      return tmp;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      TDynamicMatrix<T> tmp = *this;
      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz; ++j)
              tmp[i][j] = pMem[i][j] - m.pMem[i][j];
      }
      return tmp;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
  }
};

#endif
