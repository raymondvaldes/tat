//
//  twoColor_temperatures_dummy_amplitude.hpp
//  tat
//
//  Created by Raymond Valdes on 10/26/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef twoColor_temperatures_dummy_amplitude_hpp
#define twoColor_temperatures_dummy_amplitude_hpp

#include "thermal/pyrometry/twoColor/set_phase.h"
#include "gTBC/gMeasure/gTBD/meta_measurement_descriptions.hpp"
#include "gTBC/gMeasure/Processed_tbd_files.hpp"
#include "thermal/model/complex/temperatures.h"
#include <exception>

namespace gTBC {
namespace gMeasure {


class TBD_files_do_not_match_size: public std::exception
{
  virtual const char* what() const throw()
  {
    return "TBD files used do not have the same number of measurements.";
  }
};

class TBD_files_empty: public std::exception
{
  virtual const char* what() const throw()
  {
    return "At least one of the TBD files used do not have any measurements.";
  }
};


auto
twoColor_temperatures_dummy_amplitude
(
  meta_measurement_descriptions const & meta_data_1,
  meta_measurement_descriptions const & meta_data_2,
  thermal::pyrometry::twoColor::Set_phase set_phase
) -> thermal::model::complex::Temperatures;
  
} // namespace
} // namespace

#endif /* twoColor_temperatures_dummy_amplitude_hpp */
