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
#include <cmath>

namespace thermal{

double effusivity( const double k, const double rhoCp )
{
  return sqrt(k * rhoCp);
}

double diffusivity( const double k, const double rhoCp )
{
  return k / rhoCp;
}

double omega( const double L_coat, const double l_thermal, const double k_c,
              const double psi_c)
{
  return ( k_c / psi_c ) / ( pow( L_coat * l_thermal , 2 ) );
}

double lthermal( const double L_coat, const double k_c, const double psi_c,
                 const double omega )
{
  double lthermal = k_c;
  lthermal /= psi_c*omega;
  lthermal = sqrt(lthermal);
  lthermal /= L_coat;

  return lthermal;
}


}
