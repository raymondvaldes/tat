//
//  analytical.h
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__analytical__
#define __tat__analytical__

#include <cmath>
#include <complex>

namespace math {

namespace differential {

namespace waveEquation {

auto analytical_solution_00( double const x, std::complex<double> const Kappa )
noexcept -> std::complex<double>;
  
auto analytical_solution_10( double const x, std::complex<double> const Kappa )
noexcept -> std::complex<double>;
  
} // namespace waveEquation
  
} // namespace differential

} // namespace math

#endif /* defined(__tat__analytical__) */
