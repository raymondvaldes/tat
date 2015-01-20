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
//#include "math/estimation/cosfit.hpp"
//#include "math/estimation/parameterestimation.hpp"

namespace math {

namespace curveFit {

struct propertiesToFit{
  const bool offset;
  const bool amplitude;
  const bool phase;
  const bool frequency;
  
  explicit propertiesToFit( const bool offsetIn, const bool amplitudeIn,
                            const bool phaseIn, const bool frequencyIn  )
                            : offset(offsetIn), amplitude( amplitudeIn ),
                              phase( phaseIn ), frequency( frequencyIn ) {}
};

template< typename T >
auto cosine( const std::vector< units::quantity< units::si::time > > &inputTime,
             const std::vector< units::quantity< T > > &inputVector,
             const functions::PeriodicProperties< T > initialConditions,
             const propertiesToFit fittingGuide =
             propertiesToFit{true, true, true, false} )
noexcept
-> void
{
  int nfev = 0;
  int info = -1;
  
//  math::estimation::settings Settings;

  
  

};

} // namespace curveFit

} // namespace math

#endif /* defined(__tat__math__curveFit__cosine__) */
