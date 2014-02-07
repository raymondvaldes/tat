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
#ifndef THERMAL_HPP
#define THERMAL_HPP

#include <boost/bimap.hpp>
#include <boost/assign.hpp>
#include <boost/property_tree/ptree.hpp>

namespace thermal{

double effusivity( const double k, const double rhoCp );
double diffusivity( const double k, const double rhoCp );
double omega( const double L_coat, const double l_thermal, const double k_c,
              const double psi_c );

double lthermal( const double L_coat, const double k_c, const double psi_c,
                 const double omega );

enum class HeatX: uint8_t
{
  OneDimAnalytical,
  OneDimNumLin,
  OneDimNumNonLin,
  TwoDimAnalytical,
  TwoDimNumLin,
  TwoDimNumNonLin
};

typedef boost::bimap< enum HeatX , std::string > HeatXBiTYPE;
static const HeatXBiTYPE HeatXMap =
    boost::assign::list_of < HeatXBiTYPE::relation >
 ( HeatX::OneDimAnalytical , "OneDimAnalytical")
 ( HeatX::OneDimNumLin     , "OneDimNumLin")
 ( HeatX::OneDimNumNonLin  , "OneDimNumNonLin")
 ( HeatX::TwoDimAnalytical , "TwoDimAnalytical")
 ( HeatX::TwoDimNumLin     , "TwoDimNumLin")
 ( HeatX::TwoDimNumNonLin  , "TwoDimNumNonLin") ;


enum class EmissionX: uint8_t
{
  OneDimNonLin,
  TwoDimNonLin
};

typedef boost::bimap < enum EmissionX , std::string > emission_bimap;
const emission_bimap EmissionXMap =
    boost::assign::list_of < emission_bimap::relation >
 ( EmissionX::OneDimNonLin , "OneDimNonLin")
 ( EmissionX::TwoDimNonLin , "TwoDimNonLin");

}
#endif // THERMAL_HPP
