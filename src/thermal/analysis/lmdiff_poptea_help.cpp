/*----------------------------------------------------------------------------*\
  ========                |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||                   |
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

#include "thermal/analysis/lmdiff_poptea_help.hpp"


namespace thermal {
namespace analysis{

void scaleDiag( double *diag, math::estimation::unknownList List,
                const sensible::TBCsystem TBCsystem, const int mode ) noexcept
{
  BOOST_ASSERT( diag != nullptr ) ;

  if( mode == 2 )
  {
    int i = 0;

    for( const class math::estimation::unknown &unknown : List() )
      { diag[i++] = TBCsystem.returnVal( unknown.label() ); }
  }
}

LMA_workingArrays::LMA_workingArrays(const size_t Lend_, const size_t N_) noexcept
{
  updateArraySize( Lend_, N_ ) ;
}

void LMA_workingArrays::updateArraySize( const size_t Lend_, const size_t N ) noexcept
{
  /*Lend_ is the total number of unique measurements in a dataset,
  this value is based on the range and the set minimum*/

  fjac.resize( Lend_* N ) ;
  fvec.resize( Lend_ ) ;
}

LMA_workingArrays::~LMA_workingArrays(void) noexcept
{}


}
}
