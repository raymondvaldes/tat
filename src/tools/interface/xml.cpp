/*----------------------------------------------------------------------------*\
  ========                      |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||   	  		|
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
#include <iostream>

#include "tools/interface/xml.h"
#include "boost/property_tree/ptree.hpp"

namespace tools{
namespace interface{

boost::property_tree::ptree getTreefromFile( const std::string &absPath )
{
  boost::property_tree::ptree tree;

  try
  {
    boost::property_tree::read_xml( absPath, tree );
  }
  catch (std::exception& e)
  {
    std::cerr << "file " << absPath << " not found! See --help\n";
    std::cerr << e.what() << "\n\n";
    exit(-2) ;
  }

  return tree;
}

boost::property_tree::ptree getBranch( const std::string &trunk,
                                       const std::string &branch,
                                       const boost::property_tree::ptree &pt )
{
  const std::string branchName = trunk + "." + branch ;

  boost::property_tree::ptree output;
  output = pt.get_child( branchName ) ;
  return output ;
}



}}
