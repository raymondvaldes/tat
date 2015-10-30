/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#ifndef XML_H
#define XML_H

#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>


namespace tools{
namespace interface{

boost::property_tree::ptree getTreefromFile( const std::string &absPath ) noexcept;
boost::property_tree::ptree getBranch( const std::string &trunk,
                                       const std::string &branch,
                                       const boost::property_tree::ptree &pt );

template<class T>
T getItem( const boost::property_tree::ptree &branch, const std::string &item )
{
  auto const output = branch.get< T > ( item ) ;
  return output;
}

}}


#endif // XML_H
