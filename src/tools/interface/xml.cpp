/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#include <iostream>

#include <cassert>
#include "tools/interface/xml.h"
#include "boost/property_tree/ptree.hpp"

namespace tools{

namespace interface{

auto getTreefromFile( std::string const & absPath ) noexcept
-> boost::property_tree::ptree
{
  assert( absPath.size() > 0 );

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
  assert( trunk.size() > 0 );
  assert( branch.size() > 0 );
  assert( !pt.empty() );

  auto const branchName = trunk + "." + branch ;

  auto const output = pt.get_child( branchName ) ;
  return output ;
}


} // namespace interface

} // namespace tools
