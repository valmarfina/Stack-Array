#include <iostream>
#include <iomanip>
#include <cctype>
#include "exception"
#include "StackArray.h"

template<class T>
StackArray<T> getStack(StackArray<T> stack)
{
  return stack;
}

bool checkBalanceBrackets(const char *text, int maxDeep = 30);
bool getPostfixFromInfix(const char *infix, std::string &postfix, size_t stackSize = 30);
int evaluatePostfix(const char *infix, size_t stackSize = 30);
bool BalanceBrackets();
bool ToPostfix();
int priority(char operation);
bool testEvaluatePostfix();


int main() {
  try
  {
    StackArray<int> stack1;
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);
    std::cout << stack1.pop() << "\n";
    std::cout << stack1.pop() << "\n";
    std::cout << stack1.pop() << "\n";

    stack1.push(1);
    stack1.push(2);
    stack1.push(3);
    StackArray<int> stack2(stack1);
    std::cout << stack2.pop() << "\n";
    std::cout << stack2.pop() << "\n";
    std::cout << stack2.pop() << "\n";

    StackArray<int> stack3;
    stack3 = stack1;
    std::cout << stack3.pop() << "\n";
    std::cout << stack3.pop() << "\n";
    std::cout << stack3.pop() << "\n";

    StackArray<int> stack4 = getStack(stack1);
    std::cout << stack4.pop() << "\n";
    std::cout << stack4.pop() << "\n";
    std::cout << stack4.pop() << "\n";

    StackArray<int> stack5;
    stack5  = getStack(stack1);
    std::cout << stack5.pop() << "\n";
    std::cout << stack5.pop() << "\n";
    std::cout << stack5.pop() << "\n";
    std::cout << '\n';

    std::cout << "balance of brackets:\n";
    BalanceBrackets();
    std::cout << "Testing translation of an expression from an infix to a postfix form:\n";
    ToPostfix();
    std::cout << "Testing evaluating a postfix expression:\n";
    testEvaluatePostfix();
  }
  catch (const std::exception &error)
  {
    std::cerr << error.what() << '\n';
  }
  return 0;
}

//правильность расстановки скобок
// bracketing is correct
bool checkBalanceBrackets(const char *text, int maxDeep)
{
  char temp;
  StackArray<char> stack(maxDeep);
  int countPairedBrackets = 0;
  while (*text != '\0')
  {
    if (*text == '(' || *text == '[' || *text == '{')
    {
      stack.push(*text);
      text++;
      countPairedBrackets++;
    } else if (*text == ')' || *text == ']' || *text == '}')
    {
      countPairedBrackets--;
      if (countPairedBrackets < 0)
      {
        return false;
      }
      temp = stack.pop();
      if (!(temp == '(' && *text == ')' || temp == '[' && *text == ']' || temp == '{' && *text == '}'))
      {
        return false;
      }
      text++;
    } else
    {
      text++;
    }
  }
  if (countPairedBrackets != 0)
  {
    return false;
  }
  return true;
}

int priority(char operation)
{
  if (operation == '(' || operation == ')')
  {
    return 0;
  } else if (operation == '+' || operation == '-')
  {
    return 1;
  } else if (operation == '*' || operation == '/')
  {
    return 2;
  } else
  {
    throw std::invalid_argument("Invalid character!");
  }
}

//функция перевода арифметического выражения из инфиксной формы в постфиксную
//translate an arithmetic expression from the infix to postfix form
bool getPostfixFromInfix(const char *infix, std::string &postfix, size_t stackSize)
{
  postfix.clear();
  StackArray<char> stack(stackSize);
  while (*infix != '\0')
  {
    if (isdigit(*infix))
    {
      postfix += *infix;
    } else if (*infix == '(')
    {
      stack.push(*infix);
    } else if (*infix == ')')
    {
      while (stack.getTopElement() != '(')
      {
        postfix += stack.pop();
      }
      stack.pop();
    } else if (*infix == '+' || *infix == '-' || *infix == '*' || *infix == '/')
    {
      while (!stack.isEmpty() && priority(stack.getTopElement()) >= priority(*infix))
      {
        postfix += stack.pop();
      }
      stack.push(*infix);
    }
    infix++;
  }
  while (!stack.isEmpty())
  {
    postfix += stack.pop();
  }
  return true;
}
//вычисления значения арифметического выражения в постфиксной форме
//calculate the value of an arithmetic expression in postfix form
int evaluatePostfix(const char *infix, size_t stackSize)
{
  StackArray<int> stack(stackSize);
  while (*infix != '\0')
  {
    if (isdigit(*infix))
    {
      stack.push(static_cast<int>(*infix - '0'));
    } else if (*infix == '+')
    {
      stack.push(stack.pop() + stack.pop());
    } else if (*infix == '-')
    {
      int a = stack.pop();
      int b = stack.pop();
      stack.push(b - a);
    } else if (*infix == '*')
    {
      stack.push(stack.pop() * stack.pop());
    } else if (*infix == '/')
    {
      int div = stack.pop();
      stack.push(stack.pop() / div);
    }
    infix++;
  }
  int result = stack.pop();
  if (stack.isEmpty())
  {
    return result;
  } else
  {
    throw std::invalid_argument("Incorrect expression!");
  }
}

//анализ правильности расстановки скобок
// analyze the correctness of the brackets
bool BalanceBrackets()
{
  const char *text00 = " ok ";
  std::cout << std::setw(60) << std::left << text00 << (checkBalanceBrackets(text00) ? "right" : "wrong") << "\n";
  const char *text01 = "( ) ok ";
  std::cout << std::setw(60) << std::left << text01 << (checkBalanceBrackets(text01) ? "right" : "wrong") << "\n";
  const char *text02 = "( ( [] ) ) ok ";
  std::cout << std::setw(60) << std::left << text02 << (checkBalanceBrackets(text02) ? "right" : "wrong") << "\n";
  const char *text03 = "( ( [ { } [ ] ( [ ] ) ] ) ) OK";
  std::cout << std::setw(60) << std::left << text03 << (checkBalanceBrackets(text03) ? "right" : "wrong") << "\n";
  const char *text04 = "( ( [ { } [ ] ( [ ] ) ] ) ) ) extra right parenthesis ";
  std::cout << std::setw(60) << std::left << text04 << (checkBalanceBrackets(text04) ? "right" : "wrong") << "\n";
  const char *text05 = "( ( [{ }[ ]([ ])] ) extra left parenthesis ";
  std::cout << std::setw(60) << std::left << text05 << (checkBalanceBrackets(text05) ? "right" : "wrong") << "\n";
  const char *text06 = "( ( [{ ][ ]([ ])])) unpaired bracket ";
  std::cout << std::setw(60) << std::left << text06 << (checkBalanceBrackets(text06) ? "right" : "wrong") << "\n";
  std::cout << '\n';
  return true;
}

bool ToPostfix()
{
  std::string postfix;
  const char *text00 = "5+(3+2)*4";
  getPostfixFromInfix(text00, postfix);
  std::cout << std::setw(34) << std::left << text00 << postfix << "\n";
  const char *text01 = "5-(8+6)/(7-2/(5+8))";
  getPostfixFromInfix(text01, postfix);
  std::cout << std::setw(34) << std::left << text01 << postfix << "\n";
  const char *text02 = "6-5*(5+(5-2))+3";
  getPostfixFromInfix(text02, postfix);
  std::cout << std::setw(34) << std::left << text02 << postfix << "\n";
  const char *text03 = "(6+(8*2-(5+7)/(1-9)))*2";
  getPostfixFromInfix(text03, postfix);
  std::cout << std::setw(34) << std::left << text03 << postfix << "\n";
  const char *text04 = "3-(8+9)/3+5*3";
  getPostfixFromInfix(text04, postfix);
  std::cout << std::setw(34) << std::left << text04 << postfix << "\n";
  const char *text05 = "5/(1+6)*(8-2/(2+8))+6";
  getPostfixFromInfix(text05, postfix);
  std::cout << std::setw(34) << std::left << text05 << postfix << "\n";
  const char *text06 = "(6+(8-5)/(5+4/3)-(6*(2+7)))/7-1";
  getPostfixFromInfix(text06, postfix);
  std::cout << std::setw(34) << std::left << text06 << postfix << "\n";
  std::cout << '\n';
  return true;
}

//вычисления значения арифметического выражения в постфиксной форме
//calculating the value of an arithmetic expression in postfix form
bool testEvaluatePostfix()
{
  const char *text00 = "32+4*5-";
  std::cout << std::setw(34) << std::left << text00 << evaluatePostfix(text00) << "\n";
  const char *text01 = "586+7258+/-/-";
  std::cout << std::setw(34) << std::left << text01 << evaluatePostfix(text01) << "\n";
  const char *text02 = "65552-+*-3+";
  std::cout << std::setw(34) << std::left << text02 << evaluatePostfix(text02) << "\n";
  const char *text03 = "682*57+19-/-+2*";
  std::cout << std::setw(34) << std::left << text03 << evaluatePostfix(text03) << "\n";
  const char *text04 = "389+3/-53*+";
  std::cout << std::setw(34) << std::left << text04 << evaluatePostfix(text04) << "\n";
  const char *text05 = "516+/8228+/-*6+";
  std::cout << std::setw(34) << std::left << text05 << evaluatePostfix(text05) << "\n";
  const char *text06 = "685-543/+/+627+*-7/1-";
  std::cout << std::setw(34) << std::left << text06 << evaluatePostfix(text06) << "\n";
  std::cout << '\n';
  return true;
}