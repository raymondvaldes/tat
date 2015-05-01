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
#include <cmath>

#include <boost/units/cmath.hpp>
#include <boost/units/dimensionless_quantity.hpp>
#include "units/physical_dimensions.h"
#include "math/functions/trigonometric/csc.h"
#include "math/functions/trigonometric/sec.h"
#include "math/functions/trigonometric/coth.h"
#include "math/functions/trigonometric/csch.h"

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

template< class Y , class Z >
auto
arg( quantity< Y, std::complex< Z > > const & myComplex )
noexcept -> quantity< units::si::plane_angle, Z >
{
  using std::atan2;
  using units::si::radians;
  auto const x = myComplex.value();

  auto const phase = atan2( x.imag(), x.real() );
  auto const phase_dimensioned = phase * radians;

  return phase_dimensioned;
}

template< class Y , class Z >
auto
abs( quantity< Y, std::complex< Z > > const & myComplex )
noexcept -> quantity< Y, Z >
{
  using std::hypot;
  
  auto const x = myComplex.value();

  auto const abs_value = hypot( x.imag(), x.real() );
  auto const abs_dimensioned = quantity< Y, Z >::from_value( abs_value ) ;

  return abs_dimensioned;
}

template< class Y , class Z >
auto
imag( quantity< Y, std::complex< Z > > const & myComplex )
noexcept -> quantity< Y, Z >
{
  using std::hypot;
  
  auto const x = myComplex.value();

  auto const imag_dimensioned = quantity< Y, Z >::from_value( x.imag() ) ;

  return imag_dimensioned;
}

template< class Y , class Z >
auto
real( quantity< Y, std::complex< Z > > const & myComplex )
noexcept -> quantity< Y, Z >
{
  using std::hypot;
  
  auto const x = myComplex.value();

  auto const real_dimensioned = quantity< Y, Z >::from_value( x.real() ) ;

  return real_dimensioned;
}


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



/// coth of theta in radians
template<class Y>
typename dimensionless_quantity<si::system,Y>::type 
coth(const quantity<si::plane_angle,Y> & theta )
{
  using math::functions::trigonometric::coth;
  return coth( theta.value() ) ;
}

/// coth of theta in dimensionless
template<class Y>
typename dimensionless_quantity<si::system,Y>::type
coth(const quantity< si::dimensionless, Y > & theta )
{
  using math::functions::trigonometric::coth;
  return coth( theta.value() ) ;
}

/// cos of theta in other angular units 
template<class System,class Y>
typename dimensionless_quantity<System,Y>::type 
coth( const quantity<unit<plane_angle_dimension,System>,Y>& theta )
{
  return coth( quantity<si::plane_angle,Y>(theta) );
}


/// coth of theta in radians
template<class Y>
typename dimensionless_quantity<si::system,Y>::type 
csch(const quantity<si::plane_angle,Y> & theta )
{
  using math::functions::trigonometric::csch;
  return csch( theta.value() ) ;
}

/// coth of theta in dimensionless
template<class Y>
typename dimensionless_quantity<si::system,Y>::type
csch(const quantity< si::dimensionless, Y > & theta )
{
  using math::functions::trigonometric::csch;
  return csch( theta.value() ) ;
}

/// cos of theta in other angular units 
template<class System,class Y>
typename dimensionless_quantity<System,Y>::type 
csch( const quantity<unit<plane_angle_dimension,System>,Y>& theta )
{
  return csch( quantity<si::plane_angle,Y>(theta) );
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

/// tanh of theta in other angular units
template<class System,class Y>
typename dimensionless_quantity<System,Y>::type 
tanh(const quantity<unit<plane_angle_dimension,System>,Y>& theta)
{
    return tanh( quantity<si::plane_angle,Y>(theta) );
}

/// csc of theta in radians
template<class Y>
typename dimensionless_quantity<si::system,Y>::type 
csc(const quantity<si::plane_angle,Y> & theta )
{
    using math::functions::trigonometric::csc;
    return csc( theta.value() );
}

/// csc of theta in dimensionless
template<class Y>
typename dimensionless_quantity<si::system,Y>::type 
csc(const quantity< si::dimensionless, Y > & theta )
{
    using math::functions::trigonometric::csc;
    return csc( theta.value() );
}

/// csc of theta in other angular units
template<class System,class Y>
typename dimensionless_quantity<System,Y>::type 
csc(const quantity<unit<plane_angle_dimension,System>,Y>& theta)
{
    return csc( quantity<si::plane_angle,Y>(theta) );
}

/// sec of theta in radians
template<class Y>
typename dimensionless_quantity<si::system,Y>::type 
sec(const quantity<si::plane_angle,Y> & theta )
{
    using math::functions::trigonometric::sec;
    return sec( theta.value() );
}

/// sec of theta in dimensionless
template<class Y>
typename dimensionless_quantity<si::system,Y>::type 
sec(const quantity< si::dimensionless, Y > & theta )
{
    using math::functions::trigonometric::sec;
    return sec( theta.value() );
}

/// sec of theta in other angular units
template<class System,class Y>
typename dimensionless_quantity<System,Y>::type 
sec(const quantity<unit<plane_angle_dimension,System>,Y>& theta)
{
    return sec( quantity<si::plane_angle,Y>(theta) );
}
  
  
} // namespace units

#endif
