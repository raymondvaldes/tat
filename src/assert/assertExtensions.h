//
//  assertExtensions.h
//  tat
//
//  Created by Raymond Valdes on 1/28/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__assertExtensions__
#define __tat__assertExtensions__

#include <cmath>
#include <cassert>
#include "units.h"
/*
assert()
assert_close()
assert_close_fraction()

assert_equal_collection()

assert_predicate()
*/


template < typename Type >
inline auto assert_equal( Type const a, Type const b ) {
  assert( a == b ) ;
}


template < typename Type >
inline auto assert_small( Type const a, Type const tol ) {
  assert( a  < tol ) ;
  assert( a > -tol ) ;
}


template < typename Type >
inline auto assert_gt( Type const a, Type const b ) {
  assert( a  > b ) ;
}

template < typename Type >
inline auto assert_gt_zero( Type const a ) {
  assert( a  > 0 ) ;
}

template < typename Type >
inline auto assert_gt_zero( units::quantity<Type> const & a ) {
  assert( a.value() > 0 ) ;
}

template < typename Type >
inline auto assert_ge_zero( Type const a ) {
  assert( a  >= 0. ) ;
}

template < typename Type >
inline auto assert_ge_zero( units::quantity<Type> const & a ) {
  assert( a.value() >= 0 ) ;
}

template < typename Type >
inline auto assert_ge( Type const a, Type const b ) {
  assert( a  >= b ) ;
}


template < typename Type >
inline auto assert_lt( Type const a, Type const b ) {
  assert( a < b ) ;
}


template < typename Type >
inline auto assert_le( Type const a, Type const b ) {
  assert( a <= b ) ;
}

template < typename Type >
inline auto assert_ne( Type const a, Type const b ) {
  assert( a != b ) ;
}


template < typename Type >
inline auto assert_positive( Type const a ) {
  assert( a > 0 ) ;
}


template < typename Type >
inline auto assert_negative( Type const a ) {
  assert( a < 0 ) ;
}


template < typename Type >
inline auto assert_bitwise_equal( Type const a , Type const b ) {
  assert( !(a ^ b) ) ;
}





/*
assert_throw()
assert_error()
assert_fail()
assert_is_defined()
*/

#endif /* defined(__tat__assertExtensions__) */
