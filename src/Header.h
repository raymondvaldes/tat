#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

///Standard Template Library
#include <cstdlib>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <iostream>

///External Libraries
  ///GSL Library
  /* sudo apt-get install gsl-bin libgsl0-dev  // to install (ubuntu)
   "-lgsl -lgslcblas -lm" in "Linker Settings in codeblocks (ubuntu)"
   to install in Windows download GNUWin32 library from sourceforge */

  ///Boost Library
  // use linker and install in ubuntu using sudo apt-get install libboost-all-dev
  //     -lboost_system     -lboost_filesystem
#include <boost/filesystem.hpp>

/*When linking libraries you must ensure that the library is built at the same
number of bits as the program.  Also add library under linker settings in \
compiler.*/

///Internal dependencies
#include "tools/timing.h"
#include "numSimulations/Experimental_PhaseOfEmission.h"
#include "algorithms/sensitivity_analysis.hpp"

#endif // HEADER_H_INCLUDED
