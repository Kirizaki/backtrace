#include <iostream>

#include "parent.hpp"
#include "stacktrace.hpp"

Parent::Parent()
{
  PublicParentFoo();
}

void Parent::PublicParentFoo()
{
  ProtectedParentFoo();
}

void Parent::ProtectedParentFoo()
{
  Stacktrace st;
  std::cout << st.ToString() << std::endl;
}
