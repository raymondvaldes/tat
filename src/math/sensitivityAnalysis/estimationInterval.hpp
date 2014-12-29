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
#ifndef estimationINTERVAL_HPP_INCLUDED
#define estimationINTERVAL_HPP_INCLUDED

#include <functional>
#include "math/bisection.hpp"

namespace math
{
namespace sensitivityAnalysis
{


class step4
{
public:
  double solve() noexcept
  {
    using std::placeholders::_1;
    const std::function<double(double)>
        myFuncReduced = std::bind( &step4::gfunc, this , _1 );

    math::solve ojb( myFuncReduced, 0, 0, 1 );

    return ojb.returnSoln();
  }

  double gfunc(double x) noexcept
  {
    return x*x - 3*x + 1;  // Replace with your function
  }
};


/// let's say I make a function that outputs the parameter estimates intervals
/// this function inputs will include -> popteaCore (fixed)
///                                   -> experimental data (fixed)
///                                   -> best guess AND goodness-of-fit
///                                   -> upper and lowerbounds PI




}
}

#endif // estimationINTERVAL_HPP_INCLUDED
