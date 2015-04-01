/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#include "thermal/model/labels.h"

namespace thermal{
  namespace model{


labels& labels::operator=( const labels& that ) noexcept
{
  if(this != &that)
  {
    name = that.name;
  }
  return *this;
}


labels::labels(void) noexcept {}

labels::labels(const Name name_) noexcept:name(name_){}

enum labels::Name labels::getName(void) const noexcept
{
  return name;
}

std::string labels::getNameString(void) const noexcept
{
  return nameMap.left.at( name ) ;
}

    
  }
}
