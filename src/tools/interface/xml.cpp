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

#include "assert/assertExtensions.h"
#include "tools/interface/xml.h"
#include "boost/property_tree/ptree.hpp"

namespace tools{

namespace interface{

auto getTreefromFile( std::string const & absPath ) noexcept
-> boost::property_tree::ptree
{
  assert_gt_zero( absPath.size() );

  using std::cerr;
  using boost::property_tree::read_xml;
  using boost::property_tree::ptree;
  using std::exception;
  
  ptree tree;

  try
  {
    read_xml( absPath, tree );
  }
  catch ( exception& e )
  {
  
    cerr << "file " << absPath << " not found! See --help\n";
    cerr << e.what() << "\n\n";
    throw ;
  }

  return tree;
}

auto getBranch( std::string const & trunk,
                std::string const & branch,
                boost::property_tree::ptree const & pt )
-> boost::property_tree::ptree
{
  assert_gt_zero( trunk.size() );
  assert_gt_zero( branch.size() );
  assert( !pt.empty() );

  auto const branchName = trunk + "." + branch ;

  auto const output = pt.get_child( branchName ) ;
  return output ;
}


} // namespace interface

} // namespace tools
