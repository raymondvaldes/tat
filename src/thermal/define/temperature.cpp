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

#include "thermal/define/temperature.h"

namespace thermal{
  namespace define{
  

Temperature::Temperature( const size_t Nend_, const size_t M2_ )
: Nend(Nend_), M2(M2_)
{
  temperature = new double[Nend_ * M2_];
}

vector<double> Temperature::eval_at_z( const size_t val ) const
{
  vector<double> output( Nend ) ;

  for ( size_t i = 0 ; i < Nend ; ++i)
    output[i] = eval( i, val );
  
  return output;
}


vector<double> Temperature::eval_at_t( const size_t val ) const
{
  vector<double> output( M2 ) ;
  
  for ( size_t i = 0 ; i < M2 ; ++i)
    output[i] = eval( val, i );
  
  return output;
}

double Temperature::eval( const size_t i, const size_t j ) const
{
  return temperature[j + M2 * i];
}

void Temperature::assgn( const size_t i, const size_t j, const double value )
{
  temperature[j + M2 * i] = value;
}

void Temperature::cleanup( void )
{
  delete[]temperature;
}


  }
}