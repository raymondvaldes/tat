/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#include "tools/bimap/bimap.h"

#include "thermal/define/construct.hpp"

namespace thermal{
namespace define{

using string = std::string;
  
construct::construct( const enum HeatX myHeat,
                      const enum EmissionX myEmission ) noexcept
  :heat(myHeat), emission(myEmission){}


construct construct::loadConfigfromXML( const boost::property_tree::ptree pt) noexcept
{

  typedef boost::bimap < enum EmissionX , string > emission_bimap;
  static const emission_bimap EmissionXMap =
      boost::assign::list_of < emission_bimap::relation >
  ( EmissionX::OneDimNonLin , "OneDimNonLin")
  ( EmissionX::TwoDimNonLin , "TwoDimNonLin");

  typedef boost::bimap< enum HeatX , string > HeatXBiTYPE;
  static const HeatXBiTYPE HeatXMap =
      boost::assign::list_of < HeatXBiTYPE::relation >
   ( HeatX::OneDimAnalytical , "OneDimAnalytical")
   ( HeatX::OneDimNumLin     , "OneDimNumLin")
   ( HeatX::OneDimNumNonLin  , "OneDimNumNonLin")
   ( HeatX::TwoDimAnalytical , "TwoDimAnalytical")
   ( HeatX::TwoDimNumLin     , "TwoDimNumLin")
   ( HeatX::TwoDimNumNonLin  , "TwoDimNumNonLin") ;

  // retrieve string and map it to enum
  const string heatLabel = pt.get<string>( "heatModel" );
  const enum HeatX heatModel = HeatXMap.right.at(heatLabel);

  const string emissionLabel = pt.get<string>( "emissionModel" );
  const enum EmissionX emissionModel = EmissionXMap.right.at(emissionLabel);
  const construct thermalModel( heatModel, emissionModel);

  return thermalModel;
}

void construct::update( const enum HeatX heat_in,
                        const enum EmissionX emission_in ) noexcept
{
  heat = heat_in;
  emission = emission_in;
}

construct& construct::operator = (const construct & other) noexcept
{
  if (this != &other) // protect against invalid self-assignment
  {
      // 3: assign the new memory to the object
    emission = other.emission;
    heat = other.heat;
  }
    // by convention, always return *this
  return *this;
}
  
construct::~construct(void) noexcept {}

  
  
}}
