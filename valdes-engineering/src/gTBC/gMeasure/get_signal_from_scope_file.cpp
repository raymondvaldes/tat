//
//  get_signal_from_scope_file.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//



#include "gTBC/gMeasure/get_signal_from_scope_file.h"


#include "units/container/string_to_quantity.h"

namespace gTBC {

namespace gMeasure {

using units::quantity;
using units::si::electric_potential;
using units::si::millivolts;

using tools::interface::import::columnData;
using units::container::string_to_quantity;

auto get_signal_from_scope_file( filesystem::directory const & dir,
                                  std::string const & inputFileName )
-> std::vector< units::quantity<units::si::electric_potential >>
{
  assert( !inputFileName.empty() );

  auto const fileName_string = dir.abs( inputFileName ) ;
  auto const myData = columnData{ fileName_string } ;
  
  auto const raw_signal_column = 3 ;
  auto const list_strings = myData.getColumn( raw_signal_column ) ;
  
  auto const raw_detector_signals =
  string_to_quantity< electric_potential >( list_strings, millivolts  ) ;
  
  return raw_detector_signals;
}

auto get_signal_from_scope_file(  filesystem::path const & path )
-> std::vector< units::quantity< units::si::electric_potential, double > >
{
  auto const fileName_string = path.string();
  assert( !fileName_string.empty() );
  
  auto const myData = columnData{ fileName_string } ;
  
  auto const raw_signal_column = 3 ;
  auto const list_strings = myData.getColumn( raw_signal_column ) ;

  auto const count = list_strings.size();
  if( count != 2049 )
  {
    std::cout << list_strings.size() << "\t";
    std::cout << fileName_string <<"\n";
    throw;
  }
  assert( 2049 ==  list_strings.size() );

  
  auto const raw_detector_signals =
  string_to_quantity< electric_potential >( list_strings, millivolts  ) ;
  
  
  return raw_detector_signals;
}
  
} // namespace gMeasure
  
} // namespace gTBC
