//
//  cmath.h
//  tat
//
//  Created by Raymond Valdes on 1/27/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_cmath_h
#define tat_cmath_h

#include <boost/units/cmath.hpp>

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
  
  
} // namespace units

#endif
