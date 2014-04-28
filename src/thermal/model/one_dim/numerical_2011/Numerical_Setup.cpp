/*----------------------------------------------------------------------------*\
  ========                |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||   	  		        |
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
#include "thermal/model/one_dim/numerical_2011/Numerical_Setup.h"


double gspatial( double z, double opt, double lambda, double R1, double Iplus0,
                 double Iplus1)
{
// z must be normalized by the coating thickness
  double gs ;
  gs =  Iplus0 * exp( -z / lambda );
  gs += R1 * Iplus1 * exp( ( z - 1 ) / lambda );
  gs *= (1. / opt) ;

  if( z<=1)
    return gs;
  else if (z>1)
    return 0;

  return 0;
}


double gs_int(const double eta, const double opt, const double lambda,
              const double R1, const double Iplus0,
              const double Iplus1)
{
    // z must be normalized by the coating thickness
    if ( eta > 1 )
    {
        return 0;
    }
    else if( eta <= 1 )
    {
        double gs = eta;
        gs -= 1;
        gs /= lambda;
        gs = exp(gs);
        gs *= Iplus1;
        gs *= R1 ;
        gs -= Iplus0 *  exp( -eta / lambda );
        gs *= lambda;
        gs /= opt;
        return gs;
    }

    return -1;
}
