/*----------------------------------------------------------------------------*\
  ========                |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||                   |
-------------------------------------------------------------------------------
License
    This file is part of Thermal Analysis Toolbox.

    Thermal Analysis Toolbox is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    Thermal Analysis Toolbox is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with
    Thermal Analysis Toolbox.  If not, see <http://www.gnu.org/licenses/>.

\*----------------------------------------------------------------------------*/

#ifndef PROGRAMOPTIONS_HPP
#define PROGRAMOPTIONS_HPP

#include <utility>
#include <string>
#include <sstream>
//#include <boost/program_options.hpp>

namespace tools{
namespace programoptions{

class MainArguments{

private:
    const int argc;
    const char **argv;
    mutable bool run = false ;
    mutable std::string path;
    mutable std::string sampleName;
    mutable std::string investigationName;

    bool help( void ) const ;
    bool version( void ) const ;
    bool build( void ) const ;
    void loadOptions( void ) const ;

public:
    MainArguments( const int argc_in, const char **argv_in ) ;

    bool run_analysis( void ) const ;
    std::string run_directory( void ) const ;
    std::string run_samples( void ) const ;
    std::string run_investigationName( void ) const ;
};


}}
#endif // PROGRAMOPTIONS_HPP