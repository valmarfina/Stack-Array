#ifndef INC_3_STACK_STACK_H
#define INC_3_STACK_STACK_H

template<class T>
class Stack
{
public:
  virtual ~Stack() {}
  virtual void push(const T &e) = 0;// Добавление элемента в стек | Adding an element to the stack
  virtual const T &pop() = 0;// Удаление и возвращение верхнего элемента | Removing and returning the top item
  virtual bool isEmpty() = 0;// Проверка стека на пустоту | Checking the stack for emptiness
};

#endif
