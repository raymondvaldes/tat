/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef __tat__interval__
#define __tat__interval__

#include <utility>
#include <vector>
#include <cstddef>


namespace math {
//namespace geometry {


struct Interval
{
private:
  double left_end;
  double right_end;

public:
  Interval( const std::pair<double, double> endpoints_input ) noexcept;
  
  double get_left_end() const noexcept;
  
  double get_right_end() const noexcept;
  
  bool is_valid() const noexcept;
  
  bool is_invalid() const noexcept;
  
  void set_ends( const std::pair<double, double> endpoints_input) noexcept;
  
  Interval get_log10_random_subInterval() const noexcept;
  
  std::pair<double, double> get_pair() const noexcept;
  
  std::vector<std::vector<double>> random_group_xCR( const size_t val ) const noexcept;
  
  std::vector<std::vector<double>> ordered_group_xCR( const size_t iter ) const noexcept;
  
  std::vector<double> myX_CR( const double lmin, const double lmax ) const noexcept;
  
  std::vector< std::pair<double, double > > gridInterval( const size_t iter ) const noexcept;
  
  size_t numberofOddIntervals( const size_t iter ) const noexcept;
};


//}
}

#endif /* defined(__tat__interval__) */
