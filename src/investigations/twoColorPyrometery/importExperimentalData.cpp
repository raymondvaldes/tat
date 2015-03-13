//
//  importExperimentalData.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/11/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "investigations/twoColorPyrometery/importExperimentalData.h"
#include "gTBC/gMeasure/scopeFile.h"
#include "gTBC/gMeasure/get_signal_from_scope_file.h"
#include "gTBC/gMeasure/read_scope_file.h"
#include "gTBC/gMeasure/is_scope_file.h"
#include "gTBC/gMeasure/scopeFiles_from_datafiles.h"
#include "gTBC/gMeasure/find_unique_lambdas_in_files.h"
#include "gTBC/gMeasure/find_unique_measurements.h"
#include "gTBC/gMeasure/find_unique_frequencies_in_files.h"
#include "gTBC/gMeasure/get_pair_measurements_at_frequency.h"
#include "gTBC/gMeasure/unique_measurement_pair.h"
#include "gTBC/gMeasure/total_calibrated_emission_pairs.h"

#include "algorithm/algorithm.h"

namespace investigations {

namespace twoColorPyrometery {

auto importExperimentalData( filesystem::directory const & dir ) -> void
{
  using gTBC::gMeasure::scopeFiles_from_datafiles;
  using gTBC::gMeasure::find_unique_measurements;
  using gTBC::gMeasure::unique_measurement_pairs;
  using gTBC::gMeasure::total_calibrated_emission_pairs;

  auto const getDataFiles = dir.ls_files( ".dat" );
  auto const scopeFiles = scopeFiles_from_datafiles( getDataFiles ) ;
  
  auto const lambdas = find_unique_lambdas_in_files( scopeFiles ) ;
  
  auto const frequencies = find_unique_frequencies_in_files( scopeFiles ) ;

  // At this point I have looked into my "case" directory and the I have pull
  // out all the files and file meta deta from there.  I haven't yet read
  // the info the files because i am just operating at the filename level.
  
  auto const unique_measurements = find_unique_measurements( scopeFiles ) ;
  
  //for each frequency i need to get the two measurements and do my analysis
  // now that i have my unique measurements, i need to be able to
  // cycle through all the frequencies and get my two lambdas.

  auto const measurements_frequency_pair =
  unique_measurement_pairs( unique_measurements, frequencies.second );
  
//  auto const calibrated_emission_pairs =
//  total_calibrated_emission_pairs( measurements_frequency_pair,
//    make_pair(),
//    make_pair(),
//    wavelength_offset
//  );


  //What I want to do
  //The end result that I want to deliver is something that looks like this:
  // list of { omegas, phases } at wavelength X
  // list of { omegas, phases } at wavelength Y
  // There can only be two wavelengths because only two are being tested with
  // the code.  The code only really needs is the DC info at the first wavelength
  // and the DC info for the second wavelength.  This is the offset DC
  // at this point it is presumed that the background has already been
  // subtracted away.
  ///

}
  
} // namespace twoColorPyrometery
  
} // namespace investigations
