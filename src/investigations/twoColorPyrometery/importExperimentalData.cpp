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

#include "algorithm/algorithm.h"

namespace investigations {

namespace twoColorPyrometery {


using algorithm::for_each;

auto importExperimentalData( filesystem::directory const & dir ) -> void
{
  using gTBC::gMeasure::read_scope_file;
  using gTBC::gMeasure::scopeFiles_from_datafiles;
  using gTBC::gMeasure::sort_label_predicate  ;
  using gTBC::gMeasure::sort_frequency_predicate;
  using gTBC::gMeasure::sort_lambda_predicate;
  using gTBC::gMeasure::find_unique_measurements;
  using gTBC::gMeasure::find_unique_frequencies_in_files;
  using gTBC::gMeasure::get_pair_measurements_at_frequency;

  auto const getDataFiles = dir.ls_files( ".dat" );
  auto const scopeFiles = scopeFiles_from_datafiles( getDataFiles ) ;
  
  auto const unique_lambdas = find_unique_lambdas_in_files( scopeFiles ) ;
  assert( unique_lambdas.first.size() == 2 ) ;
  
  auto const unique_frequencies = find_unique_frequencies_in_files( scopeFiles ) ;

  // At this point I have looked into my "case" directory and the I have pull
  // out all the files and file meta deta from there.  I haven't yet read
  // the info the files because i am just operating at the filename level.
  
  auto const unique_measurements = find_unique_measurements( scopeFiles ) ;
  
  //for each frequency i need to get the two measurements and do my analysis
  // now that i have my unique measurements, i need to be able to
  // cycle through all the frequencies and get my two lambdas.

  for_each( unique_frequencies.second, [&]( auto const & freq ) noexcept
  {
    get_pair_measurements_at_frequency( unique_measurements, freq ) ;
  });
  
  
  
  //auto const parsedFiles =
  
//  auto const scopeFiles_at_lambda1 = parsedFiles.first;
//  auto const scopeFiles_at_lambda2 = parsedFiles.second;

  //Nice, now that everything is split


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
