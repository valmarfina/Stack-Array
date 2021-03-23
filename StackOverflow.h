#ifndef INC_3_STACK_STACKOVERFLOW_H
#define INC_3_STACK_STACKOVERFLOW_H

#include <exception>
#include <string>

class StackOverflow : public std::exception
{
public:
  StackOverflow() : reason_("Stack overflow!") {}
  const char* what() const noexcept override{ return reason_; }

private:
  const char* reason_;
};

#endif
