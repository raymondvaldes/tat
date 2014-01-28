/*----------------------------------------------------------------------------*\
  ========                |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||                   |
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
#include <cstddef>
#include "thermal/analysis/thermalData.hpp"
#include "thermal/thermal.hpp"
#include "models/physicalmodel.hpp"
#include "math/utility.hpp"

namespace thermal {
namespace analysis{

ThermalData::ThermalData( const double l_min, const double l_max,
                          const size_t lminPerDecarde,
                          const physicalModel::layer &coating )
{
  // Populate the experimental phase values in parameters99
  thermalSetup( l_min, l_max, lminPerDecarde ,coating );
}

ThermalData::~ThermalData(){}

size_t ThermalData::thermalSetup( const double lmin, const double lmax,
                                  const size_t lminPerDecarde ,
                                  const physicalModel::layer &coating  )
{
  size_t L_end = thermalSetupTEMP( lmin, lmax, lminPerDecarde,
                                   coating.depth, coating.kthermal.offset,
                                   coating.psithermal.offset );
  updateNMeasurements( L_end );
  math::range1og10(lmin, lmax, L_end, l_thermal);

  for (size_t i=0; i < L_end; ++i )
  {
    omegas[i] = thermal::omega( coating.depth, l_thermal[i],
                                coating.kthermal.offset,
                                coating.psithermal.offset ) ;
  }

  return L_end;
}


void ThermalData::updateOmegas( const std::vector<double>  input,
                                const physicalModel::layer &coating)
{
  l_thermal.clear();
  omegas.clear();

  omegas = input;

  const size_t  L_end = input.size();
  for (size_t i=0; i < L_end; ++i )
  {
    l_thermal[i] = thermal::lthermal( coating.depth,
                                      coating.kthermal.offset,
                                      coating.psithermal.offset,
                                      omegas[i] ) ;
  }
}

void ThermalData::updateLthermal( const std::vector<double> &input,
                                  const physicalModel::layer &coating )
{
  l_thermal.clear();
  l_thermal = input;

  const size_t  L_end = input.size();
  omegas.clear();
  for (size_t i=0; i < L_end; ++i )
  {
    omegas[i] = thermal::omega( coating.depth, l_thermal[i],
                                coating.kthermal.offset,
                                coating.psithermal.offset ) ;
  }
}

ThermalData& ThermalData::operator=(const ThermalData& that)
{
  if(this != &that)
  {
    omegas = that.omegas;
    l_thermal = that.l_thermal;
  }
  return *this;
}

double ThermalData::thermalSetupTEMP( const double l_min, const double l_max,
                                      const size_t lminPerDecarde,
                                      const double L_coat, const double kc,
                                      const double psic )
{
  const size_t L_end = lminPerDecarde;
  BOOST_ASSERT_MSG( ( l_min < l_max ) , "check min-max logic\n\n" );
  BOOST_ASSERT_MSG( ( L_coat > 0 ) && ( L_end > 0 ) , "check L inputs\n\n" );
  BOOST_ASSERT_MSG( ( kc > 0 ) && ( psic > 0 ) , "check kc inputs\n\n" );

  constexpr size_t box = 7;
  constexpr double rangeLim[box] = {1e-3, 1e-2, 1e-1, 1e0, 1e1, 1e2, 1e3};

  BOOST_ASSERT_MSG( ( l_min >= rangeLim[0] ) &&
                    ( l_max <= rangeLim[box-1] )  , "check min-max range\n\n" );

  /* I need to create a function that determines the number of measurements
  necessary to satisfy L_end_ which is the minimum  number of measurements per
  decade. Once I determine the number of measurements I need then I can use
  the ::rangelog10 function to populate the range.*/

  double rangeFills[box-1] = {0};
  for(size_t i = 0; i < box-1 ; ++i)
  {
    if( l_min >= rangeLim[i+1]  || l_max <= rangeLim[i])
    {
      rangeFills[i] = 0;
    }
    else if( l_min <= rangeLim[i] && l_max >= rangeLim[i+1])
    {
      rangeFills[i] = 1;
    }
    else
    {
      double start = 0;
      if(l_min <= rangeLim[i])
      {
        start = 0;
      }
      else if( l_min < rangeLim[i+1] )
      {
        start = math::percentilelog10(rangeLim[i], rangeLim[i+1], l_min);
      }

      double end1 = 1;
      if(l_max >= rangeLim[i+1])
      {
        end1 = 1;
      }
      else if( l_max < rangeLim[i+1] )
      {
        end1 = math::percentilelog10(rangeLim[i], rangeLim[i+1], l_max);
      }

      rangeFills[i] = end1 - start;
    }
  }

  double sum = 0;
  for(size_t i = 0; i < box-1 ; ++i)
  {
    sum += rangeFills[i];
  }

  size_t Lnew = L_end;

  if( sum > 1)
  {
    Lnew = L_end;
    Lnew *=sum;
  }
  else if(sum <= 1)  //TODO REMOVE?
  {
    Lnew = L_end;
  }

  return Lnew;
}


void  ThermalData::updateNMeasurements( const double L_end )
{
  omegas.resize(L_end);
  l_thermal.resize(L_end);
}


class ThermalData ThermalData::
        loadConfigfromXML( const boost::property_tree::ptree pt,
                           const physicalModel::layer &coating )
{
  using boost::property_tree::ptree;

  // Iterate over 'unknown' branches
  const double start  = pt.get<double>( "thermal_penetration.start" );
  const double end    = pt.get<double>( "thermal_penetration.end" );
  const size_t minperDecade = pt.get<size_t> ("minperDecade");

  class ThermalData thermalData( start, end, minperDecade, coating );

  return thermalData;
}




}}
