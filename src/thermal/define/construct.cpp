/*----------------------------------------------------------------------------*\
  ========                |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||   	  	        	|
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
#include "tools/bimap/bimap.h"

#include "thermal/define/construct.hpp"

namespace thermal{
namespace define{
  
construct::construct( const enum HeatX myHeat,
                      const enum EmissionX myEmission ) noexcept
  :heat(myHeat), emission(myEmission){}


construct construct::loadConfigfromXML( const boost::property_tree::ptree pt) noexcept
{
  using std::string;

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
