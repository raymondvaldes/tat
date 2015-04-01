/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef __TAT__CONSTRUCT_HPP
#define __TAT__CONSTRUCT_HPP

#include "thermal/define/model_type.h"
#include <boost/property_tree/ptree.hpp>

namespace thermal{
  namespace define{
  
class construct
{

public:
  enum HeatX heat;
  enum EmissionX emission;

  construct & operator = (const construct & other) noexcept;
  explicit construct( const enum HeatX myHeat,
                      const enum EmissionX myEmission ) noexcept;

  void update( const enum HeatX heat_in, const enum EmissionX emission_in ) noexcept;
  static construct loadConfigfromXML( const boost::property_tree::ptree pt ) noexcept;

  ~construct(void) noexcept;
};

}}

#endif // __TAT__CONSTRUCT_HPP
