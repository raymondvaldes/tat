/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
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
#include "thermal/model/one_dim/Tss_ana.h"

namespace thermal{ namespace model{ namespace one_dim{

double Tss1D_ana( const double z, const double R1, const double lambda,
                  const double Is, const double L, const double d,
                  const double k_ref, const double Iplus0, const double Iplus1,
                  const double q_surface, const double k_c ) noexcept
{
    /* This is the steady state 1d analytical solution to volumetric heat
    absorption in a two-layer system.  The front surface is maintained with
    an adiabatic boundary and the rear surface is held at a constant reference
    temperature of zero. */
    double Tss = 0;
    using std::exp;

    const double
    C0 = Is * L  / ( lambda * k_c ) ;

    const double
    Clam = exp( -1 / lambda );

    double
    C1  = C0 ;
    C1 *= -Iplus0 * lambda + R1 * Iplus1 * lambda * Clam;
    C1 -= q_surface / (k_c / k_ref);

    double
    C3  = k_c / k_ref;
    C3 *= -C0 * ( - Iplus0 * lambda * Clam + R1 * Iplus1 * lambda ) + C1 ;
    C3 += ( ( -1 + R1 ) * Is * Iplus1 * L ) /   k_ref  ;

    double
    C4 = - C3 * d;

    double
    C2 =  C0 ;
    C2 *= lambda * lambda * Iplus0 * Clam + R1 * Iplus1 * lambda * lambda ;
    C2 += C4 + C3 - C1;

    if ( z<=1 )
    {
        Tss = -C0;
        Tss *= Iplus0 * lambda * lambda * exp( -z / lambda ) + R1 * Iplus1 *
               lambda * lambda * exp( ( z - 1 ) / lambda ) ;
        Tss += C1 * z;
        Tss += C2;
    }
    else if (z > 1)
    {
        Tss = C3 * z + C4 ;
    }
    return Tss;
}

}}}
