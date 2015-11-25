/**
 * @file stacktrace.hpp
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

#include <string>
#include <vector>

class Stacktrace
{
 public:
  /**
   * Constructor call methods for stacktrace.
   * 
   * @param maxDepth Maximum depth of tracing the stack. Default 32 frames.
   */
  Stacktrace(int maxDepth = 32);
  
  //! Returns string of traced stack.
  static std::string ToString();
  
 private:
  /**
   * Gets frames from stack.
   * 
   * @param maxDepth Maximum depth of tracing the stack. Default 32 frames.
   */
  static void GetAddress(int maxDepth);
   
  //! Setter for layer datastructure.
  static bool DecodeAddress();
   
  //! Stacktrace layer datastructure.
  struct Frames
  {
    void *address;
    std::string function;
    std::string file;
    int line;
  } static frame;
  
  //! A vector for all the layers of traced stack.
  static std::vector<Frames> stack;
};
