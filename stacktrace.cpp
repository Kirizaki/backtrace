/**
 * @file Stacktrace.hpp
 * @author Grzegorz Krajewski
 *
 * Stacktrace class for MLPACK.
 *
 * This file is part of mlpack 1.0.12.
 *
 * mlpack is free software; you may redstribute it and/or modify it under the
 * terms of the 3-clause BSD license.  You should have received a copy of the
 * 3-clause BSD license along with mlpack.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
 */ 

#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <execinfo.h>

#include "stacktrace.hpp"

#define TRACE_CONDITION_1 (!dladdr(trace[i], &addressHandler))
#define IS_MAIN (frame.function.compare("main()"))
#define NO_BRACKET (frame.function[(frame.function.length()) - 1] != ')')
#define PUT_BRACKET (frame.function.insert((frame.function.length()), "()"))

// initialize static inctances
Stacktrace::Frames Stacktrace::frame;
std::vector<Stacktrace::Frames> Stacktrace::stack;

Stacktrace::Stacktrace(int maxDepth)
{
  frame.address = NULL;
  frame.function = "0";
  frame.file = "0";
  frame.line = 0;
  
  stack.clear();
  
  GetAddress(maxDepth);
  
  DecodeAddress();
}

void Stacktrace::GetAddress(int maxDepth)
{  
  bool isMain = false;
  
  void * trace[maxDepth];
  int stackDepth = backtrace(trace, maxDepth);

  // retrieve addresses from stack (i = 2 due to skip Stacktrace)
  for (int i = 2; i < stackDepth; i++) 
  {
    Dl_info addressHandler;
    
    if(TRACE_CONDITION_1)
    {
      break;
    }
    
    frame.address = addressHandler.dli_saddr;
    
    if(!isMain)
      DecodeAddress();
  }
}

bool Stacktrace::DecodeAddress()
{
  char buffer[256];
  char *p;
  int tmp = (long)frame.address;
  
  sprintf(buffer, "/usr/bin/addr2line -C -e ./stack -f -i %x", tmp);
  
  FILE *frameHandler = popen(buffer, "r");
  
  // retrieve function name
  //fgets (buffer, 256, frameHandler);
  //frame.function = buffer;
  
  // retrieve file name and line
  //fgets (buffer, 256, frameHandler);
  
  if(buffer[0] != '?')
  {
    char *file = buffer;
    
    // retrieve function name
    fgets(buffer, 256, frameHandler);
    frame.function = buffer;
   
    frame.function.erase((frame.function.length() - 1), 1);
    
    if(NO_BRACKET)
    {
      PUT_BRACKET;
      if(IS_MAIN)
	return true;
    }
   
    // retrieve file name and line
    fgets(buffer, 256, frameHandler);
    
    while(*file != ':')
    {
      file++;
    }
    
    *file++ = 0;

    frame.file = buffer;
    
    std::string tmp = file;
    tmp.erase((tmp.length() - 1), 1);
   
    frame.line = atoi(tmp.c_str());
    
  }
  else
  {
    frame.function = "unknown";
    frame.file = "unknown";
    frame.line = 0;
  }
  
  // save frame
  stack.push_back(frame);
  
  pclose(frameHandler);
  
  return false;
}

std::string Stacktrace::ToString()
{
  std::string stackString;
  
  for(int i = 0; i < stack.size(); i++)
  {
    frame = stack[i];
    
    printf("%s:%s:%d\n", frame.file.c_str(), frame.function.c_str(), 
frame.line);
  }
  
  return stackString;
}
