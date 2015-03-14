//
//  2colorPyrometery.cpp
//  tat
//
//  Created by Raymond Valdes on 12/18/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#include <cassert>

#include "investigations/twoColorPyrometery/calculateCalibrationCoefficients.h"
#include "investigations/twoColorPyrometery/temperature_prediction.h"
#include "investigations/twoColorPyrometery/phase_fitting.h"

#include "gTBC/gMeasure/import_twoColor_scope_files.h"

namespace investigations{

namespace twoColorPyrometery{

using gTBC::gMeasure::import_twoColor_scope_files;

auto run( filesystem::directory const & dir )  -> void
{
 // temperature_prediction( dir ) ;  //prototyping function
//  phase_fitting( dir ) ;  // prototyping function
  
  calculateCalibrationCoefficients( dir ) ;
  
  auto const scope_data = import_twoColor_scope_files( dir ) ;
  
}

} //namespace twoColorPyrometry

} //namespace investigations
