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
#ifndef NUMERICAL_PHASEOFEMISSION_H_INCLUDED
#define NUMERICAL_PHASEOFEMISSION_H_INCLUDED

#include "models/poptea.hpp"

class Temperature
{
public:
  explicit Temperature( const size_t Nend_, const size_t M2_ );
  double eval( const size_t Nvalue, const size_t M2Value ) const;
  void assgn( const size_t i, const size_t j, const double value );
  void cleanup( void );

private:
  const size_t Nend;
  const size_t M2;
  double *temperature = nullptr;
};

class emissionNoiseParameters
{
public:
  double a, b, noiseRandom;
  bool d1, d2;
  int s1;
  explicit emissionNoiseParameters( const double a1_, const double b1_,
                                    const bool d1_, const bool d2_,
                                    const int s1_, const double noiseRandom_);
};

double PhaseOfEmission2DAna( const int flag,
                             const thermalAnalysisMethod::PopTea &poptea);
double PhaseOfEmission1DNum( const int flag,
                             const thermalAnalysisMethod::PopTea &poptea);
double PhaseOfEmission1DAna( const int flag,
                             const thermalAnalysisMethod::PopTea &poptea);


#endif // NUMERICAL_PHASEOFEMISSION_H_INCLUDED
