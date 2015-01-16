//
//  main-app.cpp
//  tat
//
//  Created by Raymond Valdes on 1/13/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <string>
#include <vector>
#include <iostream>


#include "investigations/main-app.h"

#include "tools/programoptions/programoptions.hpp"
#include "tools/timing.h"
#include "investigations/execute.h"


namespace investigations{

using std::string;
using tools::programoptions::MainArguments;

inline auto executeAnalysis( const MainArguments& runArgs ) noexcept
  -> string
{
  auto globalStopWatch = tools::stopwatch{} ;

  investigations::execute(
    runArgs.run_directory(),
    runArgs.run_samples(),
    runArgs.run_investigationName()
    ) ;

  return globalStopWatch.readoutLoud();
}

int main_app( const int argc, const char *argv[ ] ) noexcept
{

  const auto runArgs = MainArguments{ argc, argv };

  if( runArgs.run_analysis() ) {
    using std::cout;
    
    const auto exeTimer = executeAnalysis( runArgs ) ;
    
    cout << exeTimer << "\n" ;
  }

  return 0 ;
}


}
