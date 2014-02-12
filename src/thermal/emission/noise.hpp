/*----------------------------------------------------------------------------*\
  ========                |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||                   |
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
#ifndef NOISE_HPP
#define NOISE_HPP
#include <vector>
#include "thermal/simulations/Numerical_Setup.h"

namespace thermal{
  namespace emission{


class ExpNoiseSetting
{
public:
  double a, b, noiseRandom;
  bool d1, d2;
  int s1;
  explicit ExpNoiseSetting( const double a1_, const double b1_,
                            const bool d1_, const bool d2_,
                            const int s1_, const double noiseRandom_);

  static ExpNoiseSetting initializeObj( const boost::property_tree::ptree pt ) ;
  static ExpNoiseSetting loadExpNoiseFile( const filesystem::directory dir ) ;
};





std::vector<double>
addNoise( const std::vector<double> &emissionNominal_,
          const std::vector<double> &lthermal,
          const thermal::emission::ExpNoiseSetting &para );
/*
a is the magnitude of the error at the edges of the range
b is the stretching parameter that ranges from 1 < b < pi (use around 3)
c is the location of the center and set it to 0.5.
d is the orientation options
d1 true (positive)
d2 true (monotonically)
s1 is //-1(left bias) 0(symmetric) +1(right bias)

This function needs an emissionProfile already established. This is the
nominal emission profile used for the simulation. The EXPERIMENTAL EMISSION
is in the object (this) scope.

This function needs l_thermal to be populated with the thermal
penetration range.

lmin and lmax are used to determine the nominal limits of the lthermal
range.

*/
// a = 0.025;
// b = 3.05;
// c = 0.5
// d1 = 1 or 0;
// d2 = 1 or 0

  }
}

#endif // NOISE_HPP
