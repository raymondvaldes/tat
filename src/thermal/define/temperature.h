/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef __tat__temperature__thermal_define__
#define __tat__temperature__thermal_define__

#include <iostream>
#include <vector>

namespace thermal{
  namespace define{
  using std::vector;

class Temperature
{
public:
  explicit Temperature( const size_t Nend_, const size_t M2_ ) noexcept;
  double eval( const size_t Nvalue, const size_t M2Value ) const noexcept;
  void assgn( const size_t i, const size_t j, const double value ) noexcept;
  void cleanup( void ) noexcept;
  
  vector<double> eval_at_z( const size_t val ) const noexcept;
  vector<double> eval_at_t( const size_t val ) const noexcept;
  
private:
  const size_t Nend;
  const size_t M2;
  double *temperature = nullptr;
};


}}


#endif /* defined(__tat__temperature__thermal_define__) */
