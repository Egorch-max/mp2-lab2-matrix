// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <cassert>

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

    if (sz >= MAX_VECTOR_SIZE)
        throw out_of_range("max_vector_size");

    pMem = new T[sz]();// {}; // У типа T д.б. конструктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v) //копирующий конструктор
  {
      sz = v.sz;

      pMem = new T[sz];

      if (pMem == nullptr)
      {
          throw("failed_memory");
      }

      for (size_t i = 0; i < sz; i++)
      {
          pMem[i] = v.pMem[i];
      }

  }
  TDynamicVector(TDynamicVector&& v) noexcept //перемещающий конструктор
  {
      sz = 0;

      pMem = nullptr;

      swap(*this, v);
  }
  ~TDynamicVector()
  {
      delete[] pMem;

      pMem = nullptr;
  }
  TDynamicVector& operator=(const TDynamicVector& v) 
  {
      if (this == &v)
      {
          return *this;
      }
      if (sz != v.sz)
      {
          T* p = new T[v.sz];

          if (p == nullptr)
          {
              throw("failed_memory");
          }
          else
          {
              delete[] pMem;

              sz = v.sz;

              pMem = p;
          }
      }
      for (size_t i = 0; i < sz; i++)
      {
          pMem[i] = v.pMem[i];
      }

      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      delete[] pMem;

      pMem = nullptr;

      swap(*this, v);

      return (*this); // заглушка
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
      {
          throw("vector is out");
      }
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind < 0 || ind >= sz)
      {
          throw("vector is out");
      }
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz != v.sz)
      {
          return 0;
      }
      for (size_t i = 0; i < sz; i++)
      {
          if (pMem[i] != v.pMem[i])
          {
              return 0;
          }
      }
      return 1;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector res(sz);

      for (size_t i = 0; i < sz; i++)
      {
          res.pMem[i] = pMem[i] + val;
      }
      return res;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector res(sz);

      for (size_t i = 0; i < sz; i++)
      {
          res.pMem[i] = pMem[i] - val;
      }
      return res;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector res(sz);

      for (size_t i = 0; i < sz; i++)
      {
          res.pMem[i] = pMem[i] * val;
      }
      return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz == v.sz)
      {
          TDynamicVector<T> res(*this);

          for (size_t i = 0; i < sz; i++)
          {
              res.pMem[i] += v.pMem[i];
          }
          return res;

      }
      else
      {
          throw("Error!The lengths of the vectors are not equal");
      }
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz == v.sz)
      {
          TDynamicVector<T> res(*this);

          for (size_t i = 0; i < sz; i++)
          {
              res.pMem[i] -= v.pMem[i];
          }
          return res;

      }
      else
      {
          throw("Error!The lengths of the vectors are not equal");
      }
  }
  T operator*(const TDynamicVector& v) //noexcept(noexcept(T()))
  {
      if (sz == v.sz)
      {
          T res{};

          for (size_t i = 0; i < sz; i++)
          {
              res += (pMem[i] * v.pMem[i]);
          }
          return res;
      }
      else
      {
          throw("Error!The lengths of the vectors are not equal");
      }
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    swap(lhs.sz, rhs.sz);
    swap(lhs.pMem, rhs.pMem);
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
      if (sz >= MAX_MATRIX_SIZE)
      {
          throw out_of_range("max_vector_size");
      }
      for (size_t i = 0; i < sz; i++)
      {
          pMem[i] = TDynamicVector<T>(sz);
      }
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];
  using TDynamicVector<TDynamicVector<T>>::at;
  using TDynamicVector<TDynamicVector<T>>::size;

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz != m.sz)
      {
          return 0;
      }
      for (size_t i = 0; i < sz; i++)
      {
          if (pMem[i] != m.pMem[i])
          {
              return 0;
          }
      }
      return 1;
  }


  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix res(sz);

      for (size_t i = 0; i < sz; i++)
      {
          res.pMem[i] = pMem[i] * val;
      }
      return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (pMem[0].size() != v.size())
      {
          throw("Error");
      }
      else
      {
          TDynamicVector<T> res(sz);

          for (size_t i = 0; i < sz; i++)
          {
              res[i] = pMem[i] * v;
          }
          return res;
      }
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.size())
      {
          throw("Error");
      }
      TDynamicMatrix<T> res(sz);

      for (size_t i = 0; i < sz; i++)
      {
          res[i] = pMem[i] + m.pMem[i];
      }
      return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.size())
      {
          throw("Error");
      }
      else
      {
          TDynamicMatrix<T> res(sz);

          for (size_t i = 0; i < sz; i++)
          {
              res[i] = pMem[i] - m.pMem[i];
          }
          return res;
      }
      
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.size())
      {
          throw("Error");
      }
      
      else
      {
          TDynamicMatrix<T> res(sz);

          TDynamicVector<T> tmp(pMem[0].size());

          for (size_t i = 0; i < sz; i++)
          {
              for (size_t j = 0; j < pMem[0].size(); j++)
              {
                  for (size_t k = 0; k < pMem[0].size(); k++)
                  {
                      tmp[k] = m.pMem[k][j];
                  }
                  res[i][j] = pMem[i] * tmp;
              }
          }
          return res;
      }
      
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
      {
          istr >> v.pMem[i];
      }
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++)
      {
          ostr << v.pMem[i] << endl;
      }
      return ostr;
  }
};

#endif
