#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <cstdlib>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <sstream>
#include <fstream>
#include <istream>
#include <vector>

#include <memory>
#include <complex>
#include <iomanip>
#include <map>
#include <utility>
#include <ctime>
#include <random>
#include <omp.h>
#include <cmath>
#include <chrono>

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
///Source headers
#include "models/Thermal_models.h"
#include "models/expEquipment.hpp"
#include "models/physicalmodel.hpp"
#include "models/numericalmodel.hpp"

#include "algorithms/parameterestimation.hpp"
#include "models/poptea.hpp"

#include "algorithms/lmdiff.h"
#include "algorithms/statistical_tools.hpp"
#include "algorithms/ThermalProp_Analysis.h"
#include "algorithms/sensitivity_analysis.hpp"
#include "investigations/sensitivity_paper.h"


#include "numSimulations/Experimental_PhaseOfEmission.h"
#include "numSimulations/Numerical_Temperature.h"
#include "numSimulations/Numerical_PhaseOfEmission_Results.h"
#include "numSimulations/Numerical_PhaseOfEmission.h"
#include "numSimulations/Numerical_Setup.h"

#include "tools/filesystem.hpp"
#include "tools/timing.h"

#endif // HEADER_H_INCLUDED
