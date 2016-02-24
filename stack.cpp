#include <string>
#include <iostream>

#include <mlpack/core.hpp>

#include "parent.hpp"

using namespace mlpack;

char fooC(char * c);

template <typename T>
T nonTypeFoo(T val);

template <typename T>
T tmpFoo (T &t2)
{
  T val = 1337.1337;
  nonTypeFoo(val);
  return t2;
}
inline void inFoo(int &i)
{ 
  float f = 1;
  short sh = 15;
  if(i == 1337)
    tmpFoo(sh);
}

template <typename T>
T nonTypeFoo(T val)
{
  Parent p;
  return val;
}

int fooA(int i)
{
  int j = 1337;
  inFoo(j);
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
  
  Timer::Start("backtrace_timer");
  
  fooC(c);
  
  Timer::Stop("backtrace_timer");
  
  return 0;
}
