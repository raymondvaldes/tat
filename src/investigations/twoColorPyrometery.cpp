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
  
void run( const filesystem::directory &dir ) noexcept {

  using thermal::analysis::Poptea;
  using thermal::analysis::initializePopTeaAndLoadSimuEmission;
  
  Poptea poptea = initializePopTeaAndLoadSimuEmission( dir );
  poptea.bestFit() ;
  
  std::cout << "this is where the breakpoint should be:!!!!"<< "\n\n";
  using std::cout;
  cout << poptea.ppUnknownParameters() << "\n";
}
  
}}
