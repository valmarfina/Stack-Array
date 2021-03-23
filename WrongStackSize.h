#ifndef INC_3_STACK_WRONGSTACKSIZE_H
#define INC_3_STACK_WRONGSTACKSIZE_H

#include <exception>
#include <string>

class WrongStackSize : public std::exception
{
public:
  WrongStackSize() : reason_("Wrong stack size!") {}
  const char* what() const noexcept override{ return reason_; }

private:
  const char* reason_;
};

#endif
