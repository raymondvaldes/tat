//
//  2colorPyrometery.cpp
//  tat
//
//  Created by Raymond Valdes on 12/18/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#include "investigations/twoColorPyrometery.h"
#include "thermal/analysis/poptea.hpp"
#include "thermal/analysis/poptea_initialize.h"

namespace investigations{
namespace twoColorPyrometery{
  
void run( const filesystem::directory &dir ) {

  using std::cout;
  using thermal::analysis::Poptea;
  
  Poptea poptea = thermal::analysis::initializePopTeaAndLoadSimuEmission( dir );
  poptea.bestFit() ;
  
  
  cout << poptea.ppUnknownParameters() << "\n";
}
  
}}