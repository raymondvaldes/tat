/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef COSFIT_HPP
#define COSFIT_HPP

#include <vector>
#include <cstddef>

namespace math{
  namespace estimation{

void cosfit( const double *dependent,const std::vector<double> &independentVec,
             double *x, const size_t Nend) noexcept;

void cosfcn1( int P, int /*N*/, double *x, double *fvec, int */*iflag*/,
              double **variables) noexcept;

  }
}
#endif // COSFIT_HPP
