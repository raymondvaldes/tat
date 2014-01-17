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
#include <boost/math/tools/roots.hpp>

#ifndef BISECTION_HPP_INCLUDED
#define BISECTION_HPP_INCLUDED
/*This class solves the function:                        f(x) = phi
  by using the bisection method to solve :  abs( f(x) - phi ) =  0
*/

namespace math{

size_t PrecisionToBits(const size_t precision);

class solve
{
private:
//  const callback_function myF;
  double (*myF)(double) ;
  const double phi;
  const double min;
  const double max;
  double bestGuess;
  double solnTolerance;
  boost::uintmax_t maxInt = 100;

public:
  solve(double(*myF_)(double) , const double phi_, const double min_,
         const double max_);
  ~solve(void);

  double returnSoln(void);
  size_t returnIterations(void);
  double returnSolnTolerance(void);
};

}


#endif // BISECTION_HPP_INCLUDED
