#ifndef INC_3_STACK_STACKUNDERFLOW_H
#define INC_3_STACK_STACKUNDERFLOW_H

#include <exception>
#include <string>

class StackUnderflow : public std::exception
{
public:
  StackUnderflow() : reason_("Stack underflow!") {}
  const char* what() const noexcept override{ return reason_; }

private:
  const char* reason_;
};

#endif
