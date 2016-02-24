#include <iostream>
#include <bfd.h>
#include "parent.hpp"
#include <mlpack/core.hpp>

using namespace mlpack;

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
  int testInt = 1337;
  
  Log::Fatal << "FATALITY!";
  //Log::Assert(false, "ASSERTITY!");
}

void Parent::ProtectedParentFoo()
{
  PublicStaticFoo();
}