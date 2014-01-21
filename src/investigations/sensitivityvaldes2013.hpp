/*----------------------------------------------------------------------------*\
  ========                      |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||   	  		|
-------------------------------------------------------------------------------
License
    This file is part of Thermal Analysis Toolbox.

    Thermal Analysis Toolbox is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    Thermal Analysis Toolbox is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with
    Thermal Analysis Toolbox.  If not, see <http://www.gnu.org/licenses/>.

\*----------------------------------------------------------------------------*/
#ifndef SENSITIVITYVALDES2013_HPP
#define SENSITIVITYVALDES2013_HPP
#include "algorithms/sensitivity_analysis.hpp"
#include "models/poptea.hpp"
#include "tools/filesystem.hpp"
#include "math/bisection.hpp"
#include "math/sensitivityAnalysis/parameterEstimationInterval.hpp"

namespace investigations
{
namespace sensitivityvaldes2013{

class thermalAnalysisMethod::PopTea
    loadWorkingDirectory(const class filesystem::directory dir);
void run(const class filesystem::directory dir);

}
}
#endif // SENSITIVITYVALDES2013_HPP









//#include "math/bisection.hpp"
//double Funct2( double x)
//{
//  return x*x ;
//}
//  math::solve funcSoln( &Funct2, 4 , -5 , 0);
//  std::cout << "this is my result\t" << funcSoln.returnSoln() << "\n"
//            << "number of iterations\t" << funcSoln.returnIterations() << "\n"
//            << "tolerance\t" << funcSoln.returnSolnTolerance() << "\n";
