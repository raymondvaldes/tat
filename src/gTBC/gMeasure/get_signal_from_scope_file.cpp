//
//  get_signal_from_scope_file.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "gTBC/gMeasure/get_signal_from_scope_file.h"

#include <cassert>

#include "algorithm/vector/stringToQuantity.h"


namespace gTBC {

namespace gMeasure {

auto get_signal_from_scope_file( filesystem::directory const & dir,
                                        std::string const & inputFileName )
-> std::vector< units::quantity<units::si::electric_potential >>
{
  assert( !inputFileName.empty() );

  using units::quantity;
  using units::si::electric_potential;
  using units::si::millivolts;

  using tools::interface::import::columnData;
  using algorithm::vector::stringToQuantity;

  auto const fileName_string = dir.abs( inputFileName ) ;
  auto const myData = columnData{ fileName_string } ;
  
  auto const raw_signal_column = 3 ;
  auto const list_strings = myData.getColumn( raw_signal_column ) ;
  
  auto const raw_detector_signals =
  stringToQuantity< electric_potential >( list_strings, millivolts  ) ;
  
  return raw_detector_signals;
}
  
} // namespace gMeasure
  
} // namespace gTBC
