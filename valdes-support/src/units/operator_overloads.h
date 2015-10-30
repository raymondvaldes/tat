//
//  Header.h
//  tat
//
//  Created by Raymond Valdes on 5/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_units_overloads_h
#define tat_units_overloads_h

#include "units/quantity.h"
#include "units/si/predefined.h"

namespace units{

template< typename T >
auto
operator/ ( quantity<T> const value, int const scalar ) noexcept
-> units::quantity<T>
{
  auto const scalar_dimensioned = quantity< si::dimensionless, double >::from_value( scalar );

  return value / scalar_dimensioned;
}

template< typename T >
auto
operator/ ( quantity<T> const value, size_t const scalar ) noexcept
-> units::quantity<T>
{
  auto const scalar_dimensioned = quantity< si::dimensionless, double >::from_value( scalar );

  return value / scalar_dimensioned;
}

template< typename T >
auto
operator/ ( quantity<T> const value, double const scalar ) noexcept
-> units::quantity<T>
{
  auto const scalar_dimensioned = quantity< si::dimensionless, double >::from_value( scalar );

  return value / scalar_dimensioned;
}



}

#endif
