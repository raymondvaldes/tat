/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
 -------------------------------------------------------------------------------
 License
 This file is part of Thermal Analysis Toolbox.
 
 Thermal Analysis Toolbox is free software: you can redistribute it and/or
 modify it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or (at your
 option) any later version.
 
 Thermal Analysis Toolbox is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License along with
 Thermal Analysis Toolbox.  If not, see <http://www.gnu.org/licenses/>.
 
\*----------------------------------------------------------------------------*/

#include "math/geometry/interval.h"
#include "math/utility.hpp"
#include <cmath>
#include <boost/assert.hpp>

using std::pair;
using std::vector;
using std::make_pair;

using std::floor;
using std::sqrt;
using std::cout;

namespace math {
//namespace geometry {

Interval::Interval( const pair<double, double> endpoints_input )
  : left_end( endpoints_input.first ), right_end( endpoints_input.second ) {
}


double Interval::get_left_end() const {
  return left_end ;
}

double Interval::get_right_end() const {
  return right_end ;
}

bool Interval::is_valid() const {
  return left_end < right_end ;
}

bool Interval::is_invalid() const {
  return left_end >= right_end ;
}

void Interval::set_ends( const pair<double, double> endpoints_input) {
  left_end = endpoints_input.first ;
  right_end = endpoints_input.second ;
}

  pair<double, double> Interval::get_pair() const {
  return make_pair( left_end, right_end ) ;
}


vector< vector < double > >
Interval::random_group_xCR( const size_t iter ) const
{
  typedef const pair<double, double > pairDD ;

  vector< vector<double>> group_x_CR( iter ) ;


  for( size_t i = 0; i < iter ; ++i )
  {
    pairDD x_initial_CR = math::random_CR_from_limits( *this ) ;
    double x[2] = { x_initial_CR.first, x_initial_CR.second } ;
    group_x_CR[i].assign( x, x + 2 ) ;
  }
  
  return group_x_CR ;
}

vector< vector<double> >
Interval::ordered_group_xCR( const size_t iter ) const
{
  size_t numberOfIntervals = floor( sqrt( iter * 2 ) ) ;
  if ( even( numberOfIntervals ) ) {
    numberOfIntervals++;
  }
  
  typedef pair<double, double > boundPair ;
  vector< boundPair > boundPairs( numberOfIntervals ) ;
  typedef const vector<double> groupBounds ;
  vector< vector<double > > group_x_CR ;
  
  groupBounds boundInterval =
    range1og10( get_left_end() , get_right_end(), numberOfIntervals ) ;
  
  for ( const auto lowerBound : boundInterval ) {
    for ( const auto upperBound : boundInterval ) {
      //if( lowerBound < upperBound ) {
        vector<double> myvect = myX_CR( lowerBound, upperBound ) ;
        group_x_CR.push_back( myvect ) ;
      //}
    }
  }
  
  return group_x_CR ;
}

vector<double> Interval::myX_CR( const double lmin, const double lmax ) const {
  BOOST_ASSERT( lmin < lmax ) ;
  BOOST_ASSERT( lmin >= left_end ) ;
  BOOST_ASSERT( lmax <= right_end ) ;

  typedef const pair< const double, const double > boundPair ;

  boundPair subInterval( lmin, lmax ) ;
  boundPair xCRpair = CRfromSweepLimits( subInterval, get_pair() ) ;
  vector<double> xCR={ xCRpair.first, xCRpair.second } ;

  return xCR;
}


Interval Interval::get_log10_random_subInterval() const {
  //given an absolute bound, return a random new set of inner limits
  //randomly generated such that the distribution is uniform in log10 space

  BOOST_ASSERT( this->is_valid() ) ;
  using std::make_pair;
  typedef const std::pair<double, double> constPairDD;
  
  Interval myInterval( make_pair(0 , 0) ) ;
  
  do {
    constPairDD myRandoms = math::get_log10_random_pair( left_end, right_end ) ;
    myInterval.set_ends( myRandoms ) ;
  } while ( myInterval.is_invalid() ) ;

  return myInterval ;
}

//}
}
