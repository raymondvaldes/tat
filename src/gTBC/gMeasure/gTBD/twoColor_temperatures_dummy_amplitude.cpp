//
//  twoColor_temperatures_dummy_amplitude.cpp
//  tat
//
//  Created by Raymond Valdes on 10/26/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "twoColor_temperatures_dummy_amplitude.hpp"
#include <gsl.h>

namespace gTBC {
namespace gMeasure {


using thermal::pyrometry::twoColor::Set_phase;

auto
twoColor_temperatures_dummy_amplitude
(
  meta_measurement_descriptions const & meta_1,
  meta_measurement_descriptions const & meta_2,
  thermal::pyrometry::twoColor::Set_phase set_phase
) -> thermal::model::complex::Temperatures
{
  if( meta_1.empty() ) { throw TBD_files_empty(); }
  if( meta_2.empty() ) { throw TBD_files_empty(); }
  if( meta_1.size() != meta_2.size() ) { throw TBD_files_do_not_match_size(); }

  auto t = thermal::model::complex::Temperatures();

  switch( set_phase )
  {
    case Set_phase::lambda_1:
    {
      t = meta_1.temperatures_dummy_amplitudes();
      break;
    }
    case Set_phase::lambda_2:
    {
      t = meta_2.temperatures_dummy_amplitudes();
      break;
    }
    case Set_phase::do_not_adjust:
      t = meta_2.temperatures_dummy_amplitudes();
      break;
  }

  Ensures( !t.empty() );
  return t;
}
  
} // namespace
} // namespace

