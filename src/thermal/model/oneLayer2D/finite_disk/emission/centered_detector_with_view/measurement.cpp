//
//  measurement.cpp
//  tat
//
//  Created by Raymond Valdes on 10/16/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include <cassert>
#include <gsl.h>

#include "measurement.hpp"
#include "thermal/model/oneLayer2D/finite_disk/seperation_of_variables/lambda_generator.hpp"
#include "math/special_functions/bessel_j/J0.h"
#include "math/special_functions/bessel_j/J1.h"
#include "math/sum/converging_series.h"
#include "math/complex/properties.h"
#include "thermal/model/complex/phase.h"
#include "thermal/model/complex/amplitude.h"
#include "thermal/model/oneLayer2D/finite_disk/detector/dimensionless/view_radius.h"
#include "thermal/model/oneLayer2D/finite_disk/disk/dimensionless/thickness.hpp"
#include "thermal/model/oneLayer2D/finite_disk/disk/dimensionless/radius.hpp"
#include "thermal/model/oneLayer2D/finite_disk/dimensionless/thermal_penetration.h"

#include "thermal/model/oneLayer2D/finite_disk/dimensional/deltaT.hpp"

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace disk{
namespace emission{
namespace centered_with_view{

using namespace units;
using math::special_functions::bessel::J0;
using math::special_functions::bessel::J1;
using thermal::model::complex::Phase;
using thermal::model::complex::Amplitude;
using thermal::model::complex::Temperature;
using std::complex;

auto measurement
(
  laser_beam::Modulation_depth const m,
  detector::dimensionless::View_radius const r_e,
  disk::dimensionless::Radius_s const s,
  disk::dimensionless::Thickness_w const w,
  finite_disk::dimensionless::Biot const Bi1,
  finite_disk::dimensionless::Biot const Bi2,
  finite_disk::dimensionless::Thermal_penetration const l
)
noexcept -> thermal::model::complex::Temperature
{
  Expects( m > 0    && m <= 1. );
  Expects( r_e > 0  && isfinite(r_e) );
  Expects( s > 0    && isfinite(s) );
  Expects( w > 0    && isfinite(w));
  Expects( Bi1 > 0  && isfinite(Bi1));
  Expects( Bi2 > 0  && isfinite(Bi2));
  Expects( l > 0    && isfinite(l));

  auto const scale = ( m / ( 2. - m ) ) * ( 2. / ( M_PI * pow<2>(s) * r_e  ) );
  
  auto const a = seperation_of_variables::Lambda_generator( s , Bi2, l );

  auto const func = [&a, w, Bi1, r_e, s]( size_t const i )
  noexcept -> quantity<si::dimensionless, complex<double> >
  {
    assert( i >=0 );
    
    auto const lambda = a.real_lambda_at( i );
    auto const lambda_tilde = a.complex_lambda_at( i );
    
    auto const f1 =
      quantity<si::dimensionless, complex<double>>({1.,0.}) /
      ( lambda_tilde * tanh( lambda_tilde * w ) + Bi1 );
    
    auto const x = lambda * s;
    auto const f2 =
        exp( -pow<2>( lambda ) / 4. )
      / ( pow<2>( J0(x) ) + pow<2>( J1(x) )  );
    
    auto const f3 = J1( lambda * r_e ) / lambda;
    
    auto const f = f1 * f2 * f3 ;
    return f;
  };
  
  auto const tol = 1.e-8;
  auto const
  tolerance = quantity<si::dimensionless, complex<double>>({ tol , tol });
  
  auto const summation = math::sum::converging_series( func, tolerance );

  auto const theta = scale * summation;



  auto const phase = Phase( -arg(theta) );
  auto const amplitude = Amplitude( abs(theta) * units::si::kelvin );
  auto const temperature = Temperature( phase, amplitude );
  
  return temperature;
}

auto
measurement
(
  slab::Slab const & slab,
  Optics const & optics,
  equipment::laser::Modulation_Frequency const frequency
)
noexcept -> thermal::model::complex::Temperature
{
  using thermal::model::oneLayer2D::finite_disk::dimensionless::thermal_penetration;
  assert( frequency > 0 * si::hertz );

  auto const m = optics.laser_modulation;

  auto const R_heat = optics.laser_radius;
  
  auto const r_e =
    detector::dimensionless::view_radius( optics.view_radius, R_heat );
  
  auto const s = disk::dimensionless::radius_s( slab.radius(), R_heat ) ;
  auto const w = disk::dimensionless::thickness_w( slab.thickness() , R_heat );
  auto const alpha = slab.thermal_diffusivity();
  
  auto const Bi1 = slab.Bi1;
  auto const Bi2 = slab.Bi2;
  auto const l = thermal_penetration( alpha , frequency, R_heat );


  auto const Q_heat = optics.laser_power;
  auto const dT =
  dimensional::deltaT( slab.thermal_conductivity() , R_heat, Q_heat );
  
  auto const t_non_dim = measurement( m, r_e, s, w, Bi1, Bi2, l );
  
  auto const phase = t_non_dim.phase();
  auto const amplitude =  t_non_dim.amplitude().value() * dT;
  
  auto const T = Temperature( phase, amplitude );

  return T;
}



} // centered_point
} // dimensionless
} // disk
} // finite_disk
} // oneLayer2d
} // model
} // thermal
