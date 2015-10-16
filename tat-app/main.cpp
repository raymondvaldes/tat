/*----------------------------------------------------------------------------*\
  ========                  |
     ||     T Thermal       | TAT: Thermal Analysis Toolbox
     ||     A Analysis      |
     ||     T Toolbox       | Copyright (C) 2013 Raymond Valdes
     ||                     |
\*----------------------------------------------------------------------------*/
//#define NDEBUG
#include <cassert>
#include <vector>
#include <string>
#include <iostream>

#include "investigations/main-app.h"
#include "algorithm/vector/vector2cstringArray.h"

using std::vector;
using std::string;
using std::cout;
using investigations::main_app;
using algorithm::vector::string2charPtr;

int main( const int /*argc*/, const char *argv[ ] )
{
  auto const myArguments = vector<string>
  {
    "/tmp/tat-app.dst/Users/raymondvaldes/usr/bin/tat-app",
    "--run",
    "/Users/raymondvaldes/Dropbox/investigations/2color/poco_graphite/25mm",
    "--sample",         "adiabatic_april28_wav",
//    "--investigation",  "twoColorPyrometery"
    "--investigation",  "bulkDiffusivityMeasurements2015"
  };
  
  vector<char const *> vec2 = string2charPtr( myArguments );

  main_app( int(vec2.size()) , vec2.data() );

  cout << "\nend program\n";
}
