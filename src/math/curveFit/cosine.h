//
//  cosine.h
//  tat
//
//  Created by Raymond Valdes on 1/19/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__math__curveFit__cosine__
#define __tat__math__curveFit__cosine__

#include <vector>
#include "math/functions/cosine.h"

namespace math {

namespace curveFit {

template< typename T >
auto cosine( const std::vector< units::quantity< units::si::time > > &inputTime,
             const std::vector< units::quantity< T > > &inputVector,
             const functions::PeriodicProperties<T> initialConditions )
noexcept
-> void
{

};

} // namespace curveFit

} // namespace math

#endif /* defined(__tat__math__curveFit__cosine__) */
