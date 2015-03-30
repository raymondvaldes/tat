//
//  inverseHankel.cpp
//  tat
//
//  Created by Raymond Valdes on 3/27/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "inverseHankel.h"
#include "algorithm/algorithm.h"

namespace math {

namespace transform {

iHankelSettings::iHankelSettings
(
  units::quantity< units::si::dimensionless > const nu_start_,
  units::quantity< units::si::dimensionless > const nu_end_,
  size_t const nu_points_
) noexcept
: nu_start( nu_start_ ), nu_end( nu_end_ ),nu_points(  nu_points_ )
{};


auto
inverseHankel
(
  std::function<
  units::quantity< units::si::dimensionless, std::complex<double> >
  ( units::quantity< units::si::dimensionless > const,
    units::quantity< units::si::dimensionless > const)> const & h,
  units::quantity< units::si::dimensionless > const z,
  units::quantity< units::si::dimensionless > const r,
  iHankelSettings const & settings 
)
noexcept -> units::quantity< units::si::dimensionless, std::complex<double>>
{
//The inverse hankel involves doing an integration over nu space
// basically i can first evaluate the complex values over the integration
// space and then i can split those into the real and imag values.
// integrate through each one individually.

  /*
  The definite integral of a complex integrand is the sum if the
  intregral of real and complex parts.

  Int[f(x),a,b] = Int[u(x)+i*v[x],a,b] = Int[u(x),a,b] + i * Int[v[x],a,b]
  */
  
//  funcComplex = new std::complex<double>[nuSize] ;
//  funcComplexR = new std::complex<double>[nuSize * mesh.Rend] ;
//  funcComplexZ = new std::complex<double>[nuSize * mesh.M2] ;
//  nuSpace = new double[nuSize] ;
//
//  funcReal = new double[nuSize] ;
//  funcImag = new double[nuSize] ;
//
//  math::range( nuSpace, nuStart, nuEnd, nuSize ) ;
  
//
//  for(size_t i = 0; i < nuSize ;  ++i)
//  {
//      const double nu = nuSpace[i];
//      funcComplex[i] = (this->*hfunc)(nu, ltherm, z);
//      funcComplex[i] *= gsl_sf_bessel_J0( nu * r ) * nu;
//
//      funcReal[i] = funcComplex[i].real();
//      funcImag[i] = funcComplex[i].imag();
//  }

//  ///Integrate each one independently
//  const size_t xlow =  0;
//  const size_t xhigh = nuSize-1;
//
//  const double
//  sumReal = math::numIntegration::simpson_3_8(funcReal, nuSpace, xlow, xhigh);
//
//  const double
//  sumImag = math::numIntegration::simpson_3_8(funcImag, nuSpace, xlow, xhigh);
//
//  ///Cleanup
//  const std::complex<double> sum (sumReal, sumImag);
//  return sum;



  return units::quantity< units::si::dimensionless, std::complex<double>>();
}

} // namespace transform
  
} // namespace math
