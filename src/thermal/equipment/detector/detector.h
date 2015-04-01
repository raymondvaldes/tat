/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef __tat__detector__
#define __tat__detector__

#include <iostream>

namespace thermal{

namespace equipment{

namespace detector{

class Detector
{
private:
  double wavelength;
  double radius;

public:

  double getPeakWavelength(void)  const noexcept ;
  double getSpotSizeRadius(void)  const noexcept;
  
  explicit Detector( const double wavelength_, const double radius_ ) noexcept;
  ~Detector(void) noexcept;
};

} // namespace detector
  
} // namespace equipment

} // namespace thermal

#endif /* defined(__tat__detector__) */
