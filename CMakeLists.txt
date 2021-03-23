cmake_minimum_required(VERSION 3.17)
project(3_stack)

set(CMAKE_CXX_STANDARD 14)

add_executable(3_stack main.cpp stack.h StackArray.h WrongStackSize.h StackOverflow.h StackUnderflow.h)