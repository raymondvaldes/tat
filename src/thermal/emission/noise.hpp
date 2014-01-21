/*----------------------------------------------------------------------------*\
  ========                      |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||                         |
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
#include "numSimulations/Numerical_Setup.h"

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
};

void addNoise( const class emissionNoiseParameters myEmissionNoise,
               const std::vector<double> lthermal,
               const std::vector<double> emissionNominal_,
               std::vector<double> emissionExperimental );

  }
}

#endif // NOISE_HPP
