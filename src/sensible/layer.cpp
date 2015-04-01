/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#include "sensible/layer.h"
#include "thermal/define/diffusivity.h"
#include "thermal/define/effusivity.hpp"

namespace sensible{
  
  using boost::property_tree::ptree;
  
  
layer::layer( const property & kthermal_, const property & psithermal_,
              const double depth_, const double lambda_ ) noexcept
: kthermal( kthermal_ ),
  psithermal( psithermal_ ),
  depth( depth_ ),
  Lambda( lambda_ )
{
  BOOST_ASSERT( depth_ > 0 ) ;
  BOOST_ASSERT( lambda_ >= 0 ) ;
}

double layer::opticalPenetration(void) const noexcept
{
  return Lambda * depth;
}

double layer::getDepth(void) const noexcept{
  return depth;
}

double layer::getLambda( void ) const noexcept{
  return Lambda;
}

void layer::setDepth( const double depth_in ) noexcept{
  BOOST_ASSERT( depth_in > 0 ) ;

  const double deltaOpt = opticalPenetration();
  depth = depth_in;
  Lambda = deltaOpt / depth;
}

void layer::setLambda( const double Lambda_in ) noexcept{
  BOOST_ASSERT( Lambda_in > 0 ) ;

  const double deltaOpt = opticalPenetration() ;
  Lambda = Lambda_in ;
  depth = deltaOpt / Lambda ;
}


double layer::getOpticalPenetration( void ) noexcept{
  return depth * Lambda ;
}


double layer::thermalDiffusivity( void ) const noexcept
{
  using thermal::define::diffusivity;
  return diffusivity( kthermal.offset, psithermal.offset );
}
double layer::thermalEffusivity( void ) const noexcept
{
  using thermal::define::effusivity;
  return effusivity( kthermal.offset, psithermal.offset );
}

layer::~layer(void) noexcept{}

layer layer::loadConfigfromXMLTree( const ptree pt ) noexcept
{
  
  const ptree branch1 = pt.get_child("conductivity");
  const property conductivity_ = property::loadConfigfromXMLTree(branch1);
  
  const ptree branch2 = pt.get_child("thermalmass");
  const property thermalMass_  = property::loadConfigfromXMLTree(branch2);
  
  const double lambda_ = pt.get<double>("lambda");
  const double length_ = pt.get<double>("length");
  
  layer layerObj(conductivity_, thermalMass_, length_, lambda_ );
  return layerObj;
}
  

}
