/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#include "thermal/define/temperature.h"

namespace thermal{
  namespace define{
  

Temperature::Temperature( const size_t Nend_, const size_t M2_ ) noexcept
: Nend(Nend_), M2(M2_)
{
  temperature = new double[Nend_ * M2_];
}

vector<double> Temperature::eval_at_z( const size_t val ) const noexcept
{
  vector<double> output( Nend ) ;

  for ( size_t i = 0 ; i < Nend ; ++i)
    output[i] = eval( i, val );
  
  return output;
}


vector<double> Temperature::eval_at_t( const size_t val ) const noexcept
{
  vector<double> output( M2 ) ;
  
  for ( size_t i = 0 ; i < M2 ; ++i)
    output[i] = eval( val, i );
  
  return output;
}

double Temperature::eval( const size_t i, const size_t j ) const noexcept
{
  return temperature[j + M2 * i];
}

void Temperature::assgn( const size_t i, const size_t j, const double value ) noexcept
{
  temperature[j + M2 * i] = value;
}

void Temperature::cleanup( void ) noexcept
{
  delete[]temperature;
}


  }
}
