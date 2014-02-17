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

#ifndef COSFIT_HPP
#define COSFIT_HPP

#include <vector>

namespace math{
  namespace estimation{


void cosfit(double **dependent, const double *independent, double *x, int j,
            double omega1, int Nend);

void cosfit(double *dependent,const std::vector<double> &independentVec,
            double *x, size_t Nend);

void cosfcn(int P,int /*N*/,double *x,double *fvec,int */*iflag*/,
            double **variables);

void cosfcn1( int P, int /*N*/, double *x, double *fvec, int */*iflag*/,
              double **variables);

  }
}
#endif // COSFIT_HPP
