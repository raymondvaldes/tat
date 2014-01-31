/*----------------------------------------------------------------------------*\
  ========                      |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox     	| Copyright (C) 2013 Raymond Valdes
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
#ifndef LMDIFF_POPTEA_HELP_HPP
#define LMDIFF_POPTEA_HELP_HPP

#include "thermal/analysis/kernal.hpp"
#include "math/statistical_tools.hpp"


namespace thermal {
namespace analysis{

void scaleDiag( double *diag, math::estimation::unknownList List,
                const physicalModel::TBCsystem TBCsystem, const int mode );

class LMA_workingArrays
{
public:
  std::vector<double> fjac;
  std::vector<double> fvec;

  double MSEinitial;

  LMA_workingArrays(const size_t Lend_, const size_t N_);
  ~LMA_workingArrays(void);
  void updateArraySize(const size_t Lend_, const size_t N);
};


}
}

#endif // LMDIFF_POPTEA_HELP_HPP
