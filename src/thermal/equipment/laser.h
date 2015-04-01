/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef __tat__laser__
#define __tat__laser__

#include <iostream>

namespace thermal{

namespace equipment{
    
class Laser
{
private:
  double area(void) const noexcept;
  double IntensityTotal(void) const noexcept;
  double IntensitySteady(void) const noexcept;
  double IntensityTransient(void) const noexcept;
  double offset, amplitude;
  void update(void) noexcept;
  
public:
  double Qlaser;
  double radius;
  double Is;
  double It;
  
  explicit Laser( const double a, const double b, const double c,
                  const double d ) noexcept;
  ~Laser() noexcept;
  
  void updateRadius( const double r ) noexcept;
  void updatePower( const double Qpower ) noexcept;
};
  
  
} // namespace equipment

} // namespace thermal

#endif /* defined(__tat__laser__) */
