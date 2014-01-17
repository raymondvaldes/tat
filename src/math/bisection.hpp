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

template<class callback_function>
class solve
{
private:
  boost::uintmax_t maxInt = 100;
  const size_t digitsPrecision = 32;
  const callback_function myF;
  const double phi;
  const double min;
  const double max;
  size_t digitsBitsofPrecision;
  boost::math::tools::eps_tolerance<double> tol = PrecisionToBits(digitsPrecision);
  double bestGuess;
  void soln(void);
  double solnTolerance;

public:
  solve( callback_function myF_, const double phi_, const double min_,
          const double max_);
  ~solve(void);

  double returnSoln(void);
  size_t returnIterations(void);
  double returnSolnTolerance(void);

};

template<class callback_function>
solve<callback_function>::solve( callback_function myF_, const double phi_,
                                 const double min_, const double max_)
  :myF(myF_), phi(phi_), min(min_), max(max_)
{
  namespace BMT =  boost::math::tools;

  try
  {
    std::pair<double, double> result = BMT::bisect( myF, min, max, tol, maxInt);
    solnTolerance = abs( result.first - result.second );
    bestGuess = (result.first + result.second) / 2;
  }
  catch (std::exception const&  ex)
  {
    std::cout << "\noutside range or no roots \n\n" << "\n";
    bestGuess = max;
  }

}

template<class callback_function>
double solve<callback_function>::returnSoln(void)
{
  return bestGuess;
}

template<class callback_function>
size_t solve<callback_function>::returnIterations(void)
{
  return maxInt;
}

template<class callback_function>
double solve<callback_function>::returnSolnTolerance(void)
{
  return solnTolerance;
}

template<class callback_function>
solve<callback_function>::~solve(void){}

}


#endif // BISECTION_HPP_INCLUDED
