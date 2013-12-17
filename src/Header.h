#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <cstdlib>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <iostream>

#include <sstream>
#include <fstream>
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

///Source headers
#include "tools/configuration.hpp"
#include "tools/filesystem.hpp"
#include "tools/timing.h"

#include "models/numericalmodel.hpp"
#include "models/Thermal_models.h"
#include "models/expEquipment.hpp"
#include "models/physicalmodel.hpp"

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

#endif // HEADER_H_INCLUDED
