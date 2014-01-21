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
#include "thermal/emission/noise.hpp"

namespace thermal{
  namespace emission{


ExpNoiseSetting::ExpNoiseSetting( const double a1_, const double b1_,
                                  const bool d1_, const bool d2_,
                                  const int s1_, const double noiseRandom_):
    a(a1_), b(b1_), noiseRandom(noiseRandom_), d1(d1_), d2(d2_), s1(s1_)
{}


// EmissionNoise
void addNoise( const class ExpNoiseSetting myEmissionNoise,
               const std::vector<double> lthermal,
               const std::vector<double> emissionNominal_,
               std::vector<double> emissionExperimental )

{
  const double lmin = lthermal.front();
  const double lmax = lthermal.back();
  const size_t L_end = lthermal.size(); //TODO BUG REMOVE
  /*
  a is the magnitude of the error at the edges of the range
  b is the stretching parameter that ranges from 1 < b < pi (use around 3)
  c is the location of the center and set it to 0.5.
  d is the orientation options
  d1 true (positive)
  d2 true (monotonically)

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

  const double a = myEmissionNoise.a;
  const double b = myEmissionNoise.b;
  const bool d1 = myEmissionNoise.d1;
  const bool d2 = myEmissionNoise.d2;
  const int s1 = myEmissionNoise.s1;
  const double noiseRandom = myEmissionNoise.noiseRandom;

// std::cout << "these are my noise parameters\n";
// std::cout << "a = " << a << "\n" << "b = " << b << "\n" << "d1 = " << d1;
// std::cout << "\n" << "d2 = " << d2 << "\n" << "s1 = "<< s1;
// std::cout << "\nnoiseRandom = " << noiseRandom << "\nend\n\n";

  if( (a < 0) || (b < 1) || (b > M_PI) )
  {
      std::cout << "parameters (a,b) out of range"; exit(-99);
  }


  for( size_t i=0 ; i < L_end; ++i)
  {
    constexpr double c = 0.5;

    const double
    lthermalPercentile = percentilelog10(lmin, lmax, lthermal[i] );

    ///Determine biased noise
    const double cotbc = tan(M_PI_2 - ( b * c ) );
    double noiseBias = -a * cotbc * tan( b * ( c - lthermalPercentile ) );

    if(!d2)
    {
        noiseBias = fabs(noiseBias);
    }

    if(!d1)
    {
        noiseBias *= -1;
    }

    switch(s1)
    {
      case -1:
          if( lthermalPercentile > 0.5 ) { noiseBias = 0; }
          break;
      case 0:
          break;
      case 1:
          if( lthermalPercentile < 0.5 ) { noiseBias = 0; }
          break;
      default:
          std::cout << "\n\nerror in symmetry options\n\n"; exit(-1);
    }

    ///Determine random noise
    const double noiseRandomGen = x_normal(0, noiseRandom);

    emissionExperimental[i] = emissionNominal_[i];
    emissionExperimental[i] += M_PI_2 * noiseBias;
    emissionExperimental[i] += M_PI_2 * noiseRandomGen;
  }

//
// std::ofstream myfile;
// std::stringstream filename;
// filename << "data/emissionSimulated.dat";
// myfile.open(filename.str().c_str());
// myfile << std::setprecision(8);
//
// for(size_t i = 0; i < laser->L_end; ++i)
// {
// myfile << laser->l_thermal[i] << "\t"
// << emissionNominal_[i] << "\t"
// << emissionExperimental[i] << "\n";
// }
// myfile.close();
}

  }
}

