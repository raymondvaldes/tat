//
//  scopeFile.h
//  tat
//
//  Created by Raymond Valdes_New on 3/11/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_scopeFile_h
#define tat_scopeFile_h

#include <string>
#include <cstddef>
#include <cmath>

#include "tools/interface/filesystem.hpp"
#include "thermal/equipment/detector/Measurements.h"
#include "units.h"

namespace gTBC {

namespace gMeasure {

struct ScopeFile
{
  std::string label;
  
  units::quantity< units::si::wavelength > monochorometer_lambda;
  
  units::quantity< units::si::frequency > laser_modulation_frequency;
  
  size_t id_number;
  
  filesystem::path path;

  size_t cycles;
  
  ScopeFile
  (
    std::string const & label_,
    units::quantity< units::si::wavelength > const & monochorometer_lambda_,
    units::quantity< units::si::frequency > const & laser_modulation_frequency_,
    size_t const & id_number_,
    filesystem::path const & path_
  ) ;
  
  auto readMeasurements
  (
    units::quantity<units::si::electric_potential> const & steady_DetectorSignal
  )
  const noexcept -> thermal::equipment::detector::Measurements ;
  
  auto read_transient_signal( void )
  const noexcept ->
  std::vector< units::quantity<units::si::electric_potential >>;
  
};


auto const sort_lambda_predicate = [](auto const & a, auto const & b)
{
  return a.monochorometer_lambda.value() < b.monochorometer_lambda.value() ;
} ;

auto const sort_label_predicate = [](auto const & a, auto const & b)
{
  return a.label < b.label ;
} ;

auto const sort_frequency_predicate = [](auto const & a, auto const & b)
{
  return a.laser_modulation_frequency.value() < b.laser_modulation_frequency.value() ;
} ;


auto const unique_lambda_predicate = []( auto const & a, auto const & b )
{
  using std::abs;
  auto const lhs = a.monochorometer_lambda.value() ;
  auto const rhs = b.monochorometer_lambda.value() ;
  auto const tolerance = 1e-10;
  auto const not_unique = abs( lhs - rhs ) < tolerance ;
  return not_unique ;
};

auto const unique_label_predicate = []( auto const & a, auto const & b )
{
  auto const not_unique = a.label == b.label ;
  return not_unique ;
};

auto const unique_frequency_predicate = []( auto const & a, auto const & b )
{
  auto const lhs = a.laser_modulation_frequency.value() ;
  auto const rhs = b.laser_modulation_frequency.value() ;
  auto const tolerance = 1e-10;
  auto const not_unique = abs( lhs - rhs ) < tolerance ;
  return not_unique ;
};
  



  
} // namespace gMeasure
  
} // namespace gTBC

#endif
