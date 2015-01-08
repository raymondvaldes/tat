//
//  taylor_uncertainty.cpp
//  tat
//
//  Created by Raymond Valdes on 9/10/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#include "investigations/taylor_uncertainty.h"
#include "thermal/analysis/poptea.hpp"
#include "thermal/analysis/poptea_initialize.h"


namespace investigations{
  namespace taylor_uncertainty{
    
void run( const filesystem::directory &dir ) noexcept {

  using std::cout;
  using thermal::analysis::Poptea;
  
  Poptea poptea = thermal::analysis::initializePopTeaAndLoadSimuEmission( dir );
  poptea.bestFit() ;
  poptea.taylor_uncertainty();
  
  
  cout << poptea.ppUnknownParameters() << "\n";
}
    
}}
