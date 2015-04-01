/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef __tat__Tss_ana__
#define __tat__Tss_ana__

#include <iostream>

namespace thermal{ namespace model{ namespace one_dim{

double Tss1D_ana( const double z, const double R1, const double lambda,
                  const double Is, const double L, const double d,
                  const double k_ref, const double Iplus0, const double Iplus1,
                  const double q_surface, const double k_c ) noexcept;

}}}

#endif /* defined(__tat__Tss_ana__) */
