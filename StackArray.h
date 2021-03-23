#ifndef INC_3_STACK_STACKARRAY_H
#define INC_3_STACK_STACKARRAY_H

#include <iostream>
#include "stack.h"
#include "WrongStackSize.h"
#include "StackOverflow.h"
#include "StackUnderflow.h"

template<class T>
class StackArray : public Stack<T>
{
public:
  explicit StackArray(size_t size = 100);

  StackArray(const StackArray<T> &src);
  StackArray(StackArray<T> &&src) noexcept;

  StackArray<T> &operator=(const StackArray<T> &src);
  StackArray<T> &operator=(StackArray<T> &&src) noexcept;

  virtual ~StackArray();
  void push(const T &e);
  const T &pop();
  bool isEmpty();
  T getTopElement() const;

private:
  T *array_; //массив элементов стека
  size_t top_{}; //вершина стека, элемент занесенный в стек последним
  size_t size_{}; //размер стека
  void swap(StackArray<T> &src);
};

template<class T>
StackArray<T>::StackArray(size_t size):
    size_(size),
    top_(0)
{
  try
  {
    array_ = new T[size + 1];
  }
  catch (...)
  {
    throw WrongStackSize();
  }
}

template<class T>
StackArray<T>::StackArray(const StackArray<T> &src):
    size_(src.size_),
    top_(src.top_)
{
  try
  {
    array_ = new T[src.size_ + 1];
  }
  catch (...)
  {
    throw WrongStackSize();
  }
  // копирование массива
  for (size_t i = 1; i <= src.top_; i++)
  {
    array_[i] = src.array_[i];
  }
}

template<class T>
StackArray<T> &StackArray<T>::operator=(const StackArray<T> &src)
{
  if (this == &src)
  {
    return *this;
  }
  StackArray<T> temp(src);
  this->swap(temp);
  return *this;
}

template<class T>
StackArray<T>::StackArray(StackArray<T> &&src) noexcept
{
  this->top_ = src.top_;
  this->size_ = src.size_;
  this->array_ = src.array_;
  src.array_ = nullptr;
  src.top_ = 0;
  src.size_ = 0;
}

template<class T>
StackArray<T> &StackArray<T>::operator=(StackArray<T> &&src) noexcept
{
  delete [] this->array_;
  this->array_ = src.array_;
  this->top_ = src.top_;
  this->size_ = src.size_;
  src.array_ = nullptr;
  return *this;
}

//реализовано в презентации
template<class T>
void StackArray<T>::swap(StackArray<T> &src)
{
  std::swap(array_, src.array_);
  std::swap(top_, src.top_);
  std::swap(size_, src.size_);
}

//реализовано в презентации
template<class T>
void StackArray<T>::push(const T &e)
{
  if (top_ == size_)
  {
    throw StackOverflow(); //нет места для нового элемента
  }
  array_[++top_] = e; //занесение элемента в стек
}


template<class T>
const T &StackArray<T>::pop()
{
  if (top_ == 0)
  {
    throw StackUnderflow();
  }
  return array_[top_--];// Элемент физически остается в стеке, но больше "не доступен"
}

template<class T>
bool StackArray<T>::isEmpty()
{
  return (top_ == 0);
}

template<class T>
StackArray<T>::~StackArray()
{
  delete[] array_;
}

template<class T>
T StackArray<T>::getTopElement() const
{
  return array_[top_];
}

#endif
