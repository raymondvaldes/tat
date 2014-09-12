//
//  ifzero.h
//  tat
//
//  Created by Raymond Valdes on 9/12/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef __tat__ifzero__
#define __tat__ifzero__

#include <vector>

namespace algorithm {
namespace vector{

bool ifzero( const double* vec, const size_t N ) ;
bool if_not_zero( const double* vec, const size_t N ) ;

bool ifzero( const std::vector<double>& vec );
bool if_not_zero( const std::vector<double>& vec );

}}
#endif /* defined(__tat__ifzero__) */