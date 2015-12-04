#include <string>
#include <iostream>

#include <mlpack/core.hpp>

#include "backtrace.hpp"
#include "parent.hpp"

using namespace mlpack;

int fooA(int i)
{
  Parent p;
  
  return 0;
}

std::string fooB(void * v)
{
  fooA(5);
  
  return "exit";
}

char fooC(char * c)
{
  void * v = 0;
  fooB(v);
  
  return 'q';
}


int main(int argc, char* argv[])
{
  CLI::ParseCommandLine(argc, argv);
  
  char * c = (char*)'c';
  
  Timer::Start("call_stack_timer");
  
  fooC(c);
  
  Timer::Stop("call_stack_timer");
  
  return 0;
}
