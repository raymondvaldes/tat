//
//  cmath.h
//  tat
//
//  Created by Raymond Valdes on 1/27/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_cmath_h
#define tat_cmath_h

#include <complex>

#include <boost/units/cmath.hpp>
#include <boost/units/dimensionless_quantity.hpp>
#include "units/physical_dimensions.h"

namespace units {

  using boost::units::isfinite;
  using boost::units::isinf;
  using boost::units::isnan;
  using boost::units::isnormal;
  using boost::units::isgreater;
  using boost::units::isgreaterequal;
  
  using boost::units::isless;
  using boost::units::islessequal;
  using boost::units::islessgreater;
  using boost::units::isunordered;
  using boost::units::abs;
  using boost::units::ceil;

  using boost::units::copysign;
  using boost::units::fabs;
  using boost::units::fdim;
  using boost::units::fmax;
  using boost::units::fmin;

  using boost::units::hypot;
  using boost::units::nextafter;
  using boost::units::nexttoward;
  using boost::units::round;
  using boost::units::signbit;
  using boost::units::trunc;
  using boost::units::fmod;
  using boost::units::modf;
  using boost::units::frexp;
  using boost::units::pow;
  using boost::units::exp;
  using boost::units::ldexp;

  using boost::units::log;
  using boost::units::log10;
  using boost::units::sqrt;
  using boost::units::cos;
  using boost::units::sin;
  using boost::units::tan;
  
  using boost::units::acos;

  using boost::units::asin;
  using boost::units::atan;
  using boost::units::atan2;
  

/// custom cmath stuff
  using boost::units::dimensionless_quantity;


template<class Y>
typename dimensionless_quantity<si::system,Y>::type
sinh(const quantity< si::plane_angle, Y > & theta )
{
    using std::sinh;
    return sinh( theta.value() );
}

template<class Y>
typename dimensionless_quantity<si::system,Y>::type
sinh(const quantity< si::dimensionless, Y > & theta )
{
    return sinh( theta.value() );
}


/// sinh of theta in other angular units
template<class System,class Y>
typename dimensionless_quantity<System,Y>::type 
sinh( const quantity<unit<plane_angle_dimension,System>,Y>& theta )
{
    return sinh( quantity<si::plane_angle,Y>(theta) );
}


/// cosh of theta in radians
template<class Y>
typename dimensionless_quantity<si::system,Y>::type 
cosh(const quantity<si::plane_angle,Y> & theta )
{
    using std::cosh;
    return cosh( theta.value() );
}

/// cosh of theta in dimensionless
template<class Y>
typename dimensionless_quantity<si::system,Y>::type 
cosh(const quantity< si::dimensionless, Y > & theta )
{
    using std::cosh;
    return cosh( theta.value() );
}

/// cos of theta in other angular units 
template<class System,class Y>
typename dimensionless_quantity<System,Y>::type 
cosh( const quantity<unit<plane_angle_dimension,System>,Y>& theta )
{
    return cosh( quantity<si::plane_angle,Y>(theta) );
}

/// tanh of theta in radians
template<class Y>
typename dimensionless_quantity<si::system,Y>::type 
tanh(const quantity<si::plane_angle,Y> & theta )
{
    using std::tanh;
    return tanh( theta.value() );
}

/// tanh of theta in dimensionless
template<class Y>
typename dimensionless_quantity<si::system,Y>::type 
tanh(const quantity< si::dimensionless, Y > & theta )
{
    using std::tanh;
    return tanh( theta.value() );
}

/// tan of theta in other angular units 
template<class System,class Y>
typename dimensionless_quantity<System,Y>::type 
tanh(const quantity<unit<plane_angle_dimension,System>,Y>& theta)
{
    return tanh( quantity<si::plane_angle,Y>(theta) );
}
  
  
} // namespace units

#endif
