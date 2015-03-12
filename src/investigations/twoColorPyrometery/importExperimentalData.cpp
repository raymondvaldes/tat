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

namespace investigations {

namespace twoColorPyrometery {

auto importExperimentalData( filesystem::directory const & dir ) -> void
{

  auto const directoryPath = dir.path() ;
  auto const filePath = dir.filePath( "CrWO6_200F_feb26_4.6_2_0.dat" );
  
  using gTBC::gMeasure::read_scope_file;
  using gTBC::gMeasure::scopeFiles_from_datafiles;
  
  auto const getDataFiles = dir.ls_files( ".dat" );
  auto const scopeFiles = scopeFiles_from_datafiles( getDataFiles ) ;
}
  
} // namespace twoColorPyrometery
  
} // namespace investigations
