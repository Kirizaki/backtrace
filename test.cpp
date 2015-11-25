#include <iostream>

#include "stacktrace.hpp"
#include "parent.hpp"

std::string fooA(std::string str)
{
  Parent p;
  //Child c;
  
  return str;
}

int fooB(int integer)
{
  fooA("some_str");
  
  return integer;
}

void fooC(int integer)
{
  fooB(integer);
}

int main(int argc, const char** argv)
{
  fooC(5);
  
  return 0;
}
