
/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
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

#include "sensible/TBCsystem.h"

namespace sensible{
  
  
TBCsystem::TBCsystem( const layer &coating_,
                      const layer &substrate_,
                      const temperatureScale &Temp_,
                      const radiativeSysProp &optical_,
                      const double radius_ )
: coating(coating_), substrate(substrate_), Temp(Temp_), optical(optical_),
radius(radius_)
{
  gamma = gammaEval();
  a_sub = a_subEval();
}
  
TBCsystem::~TBCsystem(void){}

TBCsystem TBCsystem::loadConfig(const boost::property_tree::ptree &pt)
{
  using boost::property_tree::ptree;
  
  const ptree pcoat = pt.get_child( "coating" );
  const layer coating_( layer::loadConfigfromXMLTree( pcoat ) );
  
  const ptree psub = pt.get_child( "substrate" );
  const layer substrate_( layer::loadConfigfromXMLTree( psub ) );
  
  const ptree ptmp = pt.get_child( "TemperatureScale" );
  const temperatureScale Temp_( temperatureScale::loadConfigfromXML( ptmp ) );
  
  const ptree prad = pt.get_child( "RadiationProperties" );
  const radiativeSysProp optical_( radiativeSysProp::loadConfig( prad ) );
  
  const double radius_ = pt.get< double >( "radialDomain" );
  
  const TBCsystem TBCsystemObj( coating_, substrate_, Temp_, optical_,
                                     radius_ );
  return  TBCsystemObj;
}

void TBCsystem::updateVal( const enum labels::Name mylabel , const double val )
{
  switch( mylabel )
  {
    case labels::Name::asub :
      a_sub = val;
      break;
    case labels::Name::E1 :
      optical.Emit1 = val;
      break;
    case labels::Name::gammaEff :
      gamma = val;
      break;
    case labels::Name::R1 :
      optical.R1 = val;
      break;
    case labels::Name::lambda :
      coating.lambda = val;
      break;
    case labels::Name::thermalCenter:
      std::cout << "not yet implemented, error!!"; exit(-68);
      break;
    case labels::Name::thermalRange:
      std::cout << "not yet implemented, error!!"; exit(-68);
      break;      
    default:
      std::cout << "\nSwitch Error!!\n";
      exit(-68);
      break;
  }
}




double TBCsystem::returnVal( const enum labels::Name mylabel ) const
{
  double val( 0 ) ;
  
  switch ( mylabel )
  {
    case labels::Name::asub :
      val = a_sub ;
      break;
    case labels::Name::E1 :
      val = optical.Emit1 ;
      break;
    case labels::Name::gammaEff :
      val = gamma;
      break;
    case labels::Name::R1 :
      val = optical.R1;
      break;
    case labels::Name::lambda :
      val = coating.lambda;
      break;
    case labels::Name::thermalCenter:
      std::cout << "not yet implemented, error!!"; exit(-68);
      break;
    case labels::Name::thermalRange:
      std::cout << "not yet implemented, error!!"; exit(-68);
      break;
    default:
      std::cout << "\nSwitch Error!!\n";
      exit(-69);
      break;
  }
  return val;
}

double TBCsystem::gammaEval(void) const
{
  return substrate.thermalEffusivity() / coating.thermalEffusivity();
}

double TBCsystem::a_subEval(void) const
{
  using std::sqrt;
  return sqrt(substrate.thermalDiffusivity() / coating.thermalDiffusivity());
}

void TBCsystem::updateCoat(void)
{
  using std::pow;
  using std::sqrt;

  const double effusivity_coat = substrate.thermalEffusivity() / gamma;
  const double diffusivty_coat = substrate.thermalDiffusivity() / pow(a_sub,2);
  
  coating.psithermal.offset = effusivity_coat / sqrt(diffusivty_coat);
  coating.kthermal.offset = coating.psithermal.offset * diffusivty_coat;
  return;
}
  
  
}
