//
//  stdVector2ublasVector.h
//  tat
//
//  Created by Raymond Valdes on 9/11/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef __tat__stdVector2ublasVector__
#define __tat__stdVector2ublasVector__

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <vector>

namespace algorithm {
namespace vector{

boost::numeric::ublas::vector<double>
stdVector2ublasVector( const std::vector<double>& input ) noexcept;


}}
#endif /* defined(__tat__stdVector2ublasVector__) */
