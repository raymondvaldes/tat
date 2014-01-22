/*----------------------------------------------------------------------------*\
  ========                  |
     ||     T Thermal       | TAT: Thermal Analysis Toolbox
     ||     A Analysis      |
     ||     T Toolbox       | Copyright (C) 2013 Raymond Valdes
     ||                     |
--------------------------------------------------------------------------------
License                                                                         
    This file is part of Thermal Analysis Toolbox.

    Thermal Analysis Toolbox is free software: you can redistribute it and/or 
    modify it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or (at your 
    option) any later version.

    Thermal Analysis Toolbox is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
    Public License for more details.

    You should have received a copy of the GNU General Public License along with 
    Thermal Analysis Toolbox.  If not, see <http://www.gnu.org/licenses/>.

\*----------------------------------------------------------------------------*/
#include "Header.h"
int main( int argc, char *argv[ ] )
{
  std::string path;
  bool run = tools::loadProgramOptions( argc, argv, path );

  if(run)
  {
      std::cout << "Welcome back, Raymond!\n\n";
      class stopwatch globalStopWatch;

      /// Retrieve working directory
      const class filesystem::directory dir(path);

      /// Run investigations
      investigations::sensitivityvaldes2013::run( dir );

    //  //Prepare figures and data for paper Sensitivity
    ////    SensitivityValdes2013::CC_APS2(poptea);
    ////    SensitivityValdes2013::figureSensitivityIntro(poptea);

      /// Test investigation
    //  investigations::manyfit::run( dir );

      globalStopWatch.displayTime();
  }

  return 0;
}
