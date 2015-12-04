#include <iostream>

#include "parent.hpp"
#include "backtrace.hpp"

Parent::Parent()
{
  PublicParentFoo();
}

void Parent::PublicParentFoo()
{
  ProtectedParentFoo();
}

void Parent::PublicStaticFoo()
{
  Backtrace bt;
  std::cout << bt.ToString() << std::endl;
}

void Parent::ProtectedParentFoo()
{
  PublicStaticFoo();
}
