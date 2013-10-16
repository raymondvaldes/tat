#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>
#include <vector>

//sudo apt-get install gsl-bin libgsl0-dev  // to install (ubuntu)
// "-lgsl-lgslcblas -lm" in "Linker Settings in codeblocks (ubuntu)"
// to install in Windows download GNUWin32 library from sourceforge
#include <gsl/gsl_math.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_statistics.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_spline.h>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_sf.h>
#include <gsl/gsl_dht.h>
#include <gsl/gsl_linalg.h>

///Boost Library
// use linker and install in ubuntu using sudo apt-get install libboost-all-dev
//-lboost_system in linker
//-lboost_filesystem in linker
#include <boost/filesystem.hpp>

/*
When linking libraries you must ensure that the library is built at the same
number of bits as the program.  Also add library under linker settings in \
compiler.
*/
#include <memory>
#include <complex>
#include <iomanip>
#include <map>
#include <utility>
#include <ctime>
#include <random>
#include <omp.h>
#include <cmath>

///Source headers
#include "algorithms/parameterEstimationAlgorithms.hpp"
#include "algorithms/statistical_tools.hpp"
#include "algorithms/ThermalProp_Analysis.h"

#include "investigations/sensitivity_paper.h"

#include "numSimulations/Experimental_PhaseOfEmission.h"
#include "numSimulations/models.h"
#include "numSimulations/Numerical_Temperature.h"
#include "numSimulations/Numerical_PhaseOfEmission_Results.h"
#include "numSimulations/Numerical_PhaseOfEmission.h"
#include "numSimulations/Numerical_Setup.h"
#endif // HEADER_H_INCLUDED
