﻿// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
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

#pragma region Dynamic Vector
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
      if (sz == 0) throw out_of_range("Error");
      if (size > MAX_VECTOR_SIZE) throw out_of_range("Error");
      pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }

  TDynamicVector(T* arr, size_t s) : sz(s)
  {
      assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
      pMem = new T[sz]();
      copy(arr, arr + sz, pMem);
  }

  TDynamicVector(const TDynamicVector& v)
  {
      sz = v.sz;
      pMem = new T[sz]();
      for (int i = 0; i < sz; i++) pMem[i] = v.pMem[i];
  }

  TDynamicVector(TDynamicVector&& v) noexcept
  {
      pMem = nullptr;
      swap(*this, v);
  }

  ~TDynamicVector()
  {
      delete[] pMem;
  }

  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this != &v) {
          if (sz != v.sz) {
              delete[] pMem;
              pMem = new T[v.sz];
          }
          sz = v.sz;
          for (int i = 0; i < sz; i++) pMem[i] = v.pMem[i];
      }

      return *this;
  }

  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      swap(*this, v);

      return *this;
  }

  size_t size() const noexcept { return sz; }

#pragma region  Indexing
  T& operator[](size_t ind)
  {
      if (ind < 0 || ind >= sz) throw "Error";

      return pMem[ind];
  }

  const T& operator[](size_t ind) const
  {
      if (ind < 0 || ind >= sz) throw "Error";

      return pMem[ind];
  }
#pragma endregion

#pragma region Control Indexing
  T& at(size_t ind)
  {
      if (ind < 0 || ind >= sz) throw "Error";

      return pMem[ind];
  }

  const T& at(size_t ind) const
  {
      if (ind < 0 || ind >= sz) throw "Error";

      return pMem[ind];
  }
#pragma endregion

#pragma region Comparison
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (this == &v) return true;
      if (sz != v.sz) return false;
      for (int i = 0; i < sz; i++) if (pMem[i] != v.pMem[i]) return false;

      return true;
  }

  bool operator!=(const TDynamicVector& v) const noexcept
  {
      if (this == &v) return false;
      if (sz != v.sz) return true;
      for (int i = 0; i < sz; i++) if (pMem[i] != v.pMem[i]) return true;

      return false;
  }
#pragma endregion

#pragma region Scalar Operations
  TDynamicVector operator+(T val)
  {
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++) tmp.pMem[i] = pMem[i] + val;

      return tmp;
  }

  TDynamicVector operator-(double val)
  {
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++) tmp.pMem[i] = pMem[i] - val;

      return tmp;
  }

  TDynamicVector operator*(double val)
  {
      TDynamicVector tmp(sz);
      for (size_t i = 0; i < sz; i++) tmp.pMem[i] = pMem[i] * val;

      return tmp;
  }
#pragma endregion

#pragma region Operations
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz) throw out_of_range("Error");
      TDynamicVector tmp(v.sz);

      for (int i = 0; i < sz && i < v.sz; i++) tmp.pMem[i] = pMem[i] + v.pMem[i];

      return tmp;
  }

  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz) throw out_of_range("Error");
      TDynamicVector tmp(v.sz);

      for (int i = 0; i < sz && i < v.sz; i++) tmp.pMem[i] = pMem[i] - v.pMem[i];

      return tmp;
  }

  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (sz != v.sz) throw out_of_range("Error");
      int result = 0;

      for (size_t i = 0; i < sz; i++) result += pMem[i] * v.pMem[i];

      return result;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }
#pragma endregion

#pragma region IO
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++) istr >> v.pMem[i]; // требуется оператор>> для типа T

    return istr;
  }

  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++) ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T

    return ostr;
  }
};
#pragma endregion
#pragma endregion

#pragma region Dynamic Matrix
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
      if (s > MAX_MATRIX_SIZE) throw out_of_range("Error");
      for (size_t i = 0; i < sz; i++) pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

#pragma region Comparison
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      return TDynamicVector<TDynamicVector<T>>::operator==(m);
//      if (sz != m.sz) return false;
//      for (int i = 0; i < sz; i++) if (pMem[i] != m.pMem[i]) return false;
//
//      return true;
  }
#pragma endregion

#pragma region Operation Matrix-Scalar
  TDynamicVector<T> operator*(const T& val)
  {
      return TDynamicVector<TDynamicVector<T>>::operator*(val);
      //TDynamicMatrix tmp(sz);
      //for (int i = 0; i < sz; i++) tmp.pMem[i] = pMem[i] * val;
      //
      //return tmp;
  }
#pragma endregion

#pragma region Operation Matrix-Vector
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      return TDynamicVector<TDynamicVector<T>>::operator*(v);
      //TDynamicVector<T> tmp(sz);
      //for (int i = 0; i < sz; i++) tmp[i] = pMem[i] * v;
      //
      //return tmp;
  }
#pragma endregion

#pragma region Operations Matrix-Matrix
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw out_of_range("Error");
      TDynamicMatrix tmp(sz);

      for (int i = 0; i < sz; i++) tmp.pMem[i] = pMem[i] + m.pMem[i];

      return tmp;
  }

  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw out_of_range("Error");
      TDynamicMatrix tmp(sz);

      for (int i = 0; i < sz; i++) tmp.pMem[i] = pMem[i] - m.pMem[i];

      return tmp;
  }

  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz) throw out_of_range("Error");
      TDynamicMatrix res(sz);
      TDynamicMatrix tmp = transpose(m);

      for (int i = 0; i < sz; i++) for (int j = 0; j < sz; j++) res[i][j] = pMem[i] * tmp[j];

      return res;
  }
#pragma endregion

#pragma region IO
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++) istr >> v.pMem[i];

      return istr;
  }

  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++) ostr << v.pMem[i] << endl;

      return ostr;
  }
};
#pragma endregion
#pragma endregion
#endif