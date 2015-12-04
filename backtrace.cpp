/**
 * @file backtrace.cpp
 * @author Grzegorz Krajewski
 *
 * Implementation of the Backtrace class.
 *
 * This file is part of mlpack 1.0.12.
 *
 * mlpack is free software; you may redstribute it and/or modify it under the
 * terms of the 3-clause BSD license.  You should have received a copy of the
 * 3-clause BSD license along with mlpack.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
 */

#include <sstream>

#ifndef _WIN32
  #include <execinfo.h>
  #include <cxxabi.h>
  #include <dlfcn.h>
#endif

#include "backtrace.hpp"

// Easier to read Backtrace::DecodeAddress().
#ifndef _WIN32
  #define TRACE_CONDITION_1 (!dladdr(trace[i], &addressHandler))
  #define FIND_LINE (bfd_find_nearest_line(abfd, text, syms, offset, &frame.file, &frame.function, &frame.line) && frame.file)
#endif

// Initialize Backtrace static inctances.
Backtrace::Frames Backtrace::frame;
std::vector<Backtrace::Frames> Backtrace::stack;
bfd* Backtrace::abfd;
asymbol **Backtrace::syms;
asection *Backtrace::text;

Backtrace::Backtrace(int maxDepth)
{
  frame.address = NULL;
  frame.function = "0";
  frame.file = "0";
  frame.line = 0;
  
  abfd = 0;
  syms = 0;
  text = 0;
  
  stack.clear();
  
  GetAddress(maxDepth);
}

#ifndef _WIN32
void Backtrace::GetAddress(int maxDepth)
{
  void* trace[maxDepth];
  int stackDepth = backtrace(trace, maxDepth);

  // Skip first stack frame (points to Backtrace::Backtrace).
  for (int i = 1; i < stackDepth; i++) 
  {
    Dl_info addressHandler;
    
    if(TRACE_CONDITION_1)
    {
      return;
    }
    
    frame.address = addressHandler.dli_saddr;
    
    DecodeAddress((long)frame.address);
  }
}

void Backtrace::DecodeAddress(long addr)
{
  // Check to see if there is anything to descript. If it doesn't, we'll
  // dump running program.
  if (!abfd)
  {
    char ename[1024];
    int l = readlink("/proc/self/exe",ename,sizeof(ename));
    if (l == -1)
    {
      perror("Failed to open executable!\n");
      return;
    }
    ename[l] = 0;
    
    bfd_init();
    
    abfd = bfd_openr(ename, 0);
    if (!abfd)
    {
      perror("bfd_openr failed: ");
      return;
    }
 
    bfd_check_format(abfd,bfd_object);
 
    unsigned storage_needed = bfd_get_symtab_upper_bound(abfd);
    syms = (asymbol **) malloc(storage_needed);
    unsigned cSymbols = bfd_canonicalize_symtab(abfd, syms);
  
    text = bfd_get_section_by_name(abfd, ".text");
   }
   
  long offset = addr - text->vma;
  
  if (offset > 0)
  {	
    if(FIND_LINE)
    {
      DemangleFunction();
      // Save retrieved informations.
      stack.push_back(frame);
    }
  }
}

void Backtrace::DemangleFunction()
{
  int status;
  char* tmp = abi::__cxa_demangle(frame.function, 0, 0, &status);
  
  // If demangling is successful, reallocate 'frame.function' pointer to
  // demangled name. Else if 'status != 0', leave 'frame.function as it is.
  if (status == 0)
  {
    frame.function = tmp;
  }
}
#else
void Backtrace::GetAddress(int /* maxDepth */) { }
void Backtrace::DecodeAddress(long /*address */) { }
#endif

std::string Backtrace::ToString()
{
  std::string stackStr;
  
  std::ostringstream lineOss;
  std::ostringstream it;
  
  for(unsigned int i = 0; i < stack.size(); i++)
  {
    frame = stack[i];
    
    lineOss << frame.line;
    it << i + 1;
    
    stackStr += "[bt]: (" + it.str() + ") "
	     + frame.file + ":"
	     + frame.function + ":"
	     + lineOss.str() + "\n";
    
    lineOss.str("");
    it.str("");
  }
  
  return stackStr;
}
