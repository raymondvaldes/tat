/*----------------------------------------------------------------------------*\
  ========                  |
     ||     T Thermal       | TAT: Thermal Analysis Toolbox
     ||     A Analysis      |
     ||     T Toolbox       | Copyright (C) 2013 Raymond Valdes
     ||                     |
\*----------------------------------------------------------------------------*/
#include <string>
#include <iostream>
#include <fstream>

#include "tools/interface/exportfile.hpp"

namespace tools{

namespace interface{

void exportfile( const std::string &fullpath, const std::string &input ) noexcept
{
  std::ofstream myfile ;
  myfile.open( fullpath ) ;
  myfile << input ;
  myfile.close() ;
}

} // namespace tools

} // namespace interface
