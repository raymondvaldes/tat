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
#include <exception>
#include "thermal/analysis/kernal.hpp"
#include "models/expEquipment.hpp"
#include "models/numericalmodel.hpp"
#include "math/estimation/parameterestimation.hpp"
#include "math/utility.hpp"
#include "tools/filesystem.hpp"
#include "thermal/model.hpp"
#include "thermal/thermal.hpp"

namespace thermal {
namespace analysis{

Kernal::Kernal( class equipment::setup expSetup_,
                class physicalModel::TBCsystem TBCsystem_,
                class thermal::model thermalsys_,
                class math::estimation::settings Settings_,
                class math::estimation::unknownList unknownParameters_,
                class filesystem::directory DataDirectory_ )
  : expSetup(expSetup_),
    TBCsystem(TBCsystem_),
    thermalsys(thermalsys_),
    LMA(Settings_, unknownParameters_),
    DataDirectory(DataDirectory_)
{
  thermalsys.mesh.iter = 1000;

  /// Heat Transfer and Emission models
  const double l_min = .04;
  const double l_max = 4;
  const size_t LendMinDecade = 50;

  // Populate the experimental phase values in parameters99
  L_end = LendMinDecade;
  expSetup.q_surface = 0;
  thermalSetup(l_min, l_max, LendMinDecade);
}

class thermal::analysis::Kernal
        Kernal::loadConfig(const std::string &filename,
                           const filesystem::directory DataDirectory_)
{
  using boost::property_tree::ptree;
  ptree pt;

  try
  {
    read_xml(filename, pt);
  }
  catch (std::exception& e)
  {
    std::cout << "file " << filename << " not found! See --help\n";
    exit(-2);
  }

  const std::string conjunto = "kernal.";
  const ptree ptchild1 = pt.get_child( conjunto + "experimentalSetup" );
  const class equipment::setup
    Obj1( equipment::setup::loadConfigfromXML( ptchild1 ) );

  const ptree ptchild2 = pt.get_child( conjunto + "TBCsystem" );
  const class physicalModel::TBCsystem
    Obj2( physicalModel::TBCsystem::loadConfig( ptchild2 ) );

  const ptree ptchild3 = pt.get_child( conjunto + "thermalModel" );
  const class thermal::construct
    Construct( thermal::construct::loadConfigfromXML( ptchild3 ) );

  /// Mesh is intrinsically linked the TBCsystem and experimental setup
  const size_t M2     = ptchild3.get<size_t>( "mesh.M2" );
  const size_t Rend   = ptchild3.get<size_t>( "mesh.Rend");
  const size_t Nend   = ptchild3.get<size_t>( "mesh.Nend" );
  const double beta1  = ptchild3.get<double>( "mesh.beta1" );
  const double split  = ptchild3.get<double>( "mesh.split" );
  class numericalModel::Mesh mesh(M2, Rend, Nend, beta1, split,
                                  Obj2.coating.depth,
                                  Obj2.substrate.depth,
                                  Obj1.laser.radius,
                                  Obj2.radius);

  const class thermal::model Ojb3NEW( Construct , mesh);

  const ptree ptchild4 = pt.get_child( conjunto + "ParaEstSettings" );
  const class math::estimation::settings
    Obj4( math::estimation::settings::loadConfigfromXML( ptchild4 ) );

  const ptree ptchild5 = pt.get_child( conjunto );
  const class math::estimation::unknownList
    Obj5( math::estimation::unknownList::loadConfigfromXML( ptchild5 ) );

  //Load class object from previous objects
  class Kernal kernal( Obj1, Obj2, Ojb3NEW, Obj4, Obj5 , DataDirectory_);

  return kernal;
}

Kernal::~Kernal(void){}


void Kernal::thermalSetup(const double lmin_, const double lmax_,
                                const size_t LendMin)
{
  L_end = thermalSetupTEMP( lmin_, lmax_,
                            TBCsystem.coating.depth,
                            TBCsystem.coating.kthermal.offset,
                            TBCsystem.coating.psithermal.offset , LendMin);

  LMA.LMA_workspace.updateArraySize( L_end, LMA.unknownParameters.Nsize()  );
}

double Kernal::bEval(void) const
{
  return expSetup.laser.radius / TBCsystem.coating.depth;
}


double  Kernal::thermalSetupTEMP(const double lmin_, const double lmax_,
                           const double L_coat, const double kc,
                           const double psic, const size_t L_end_)
{
  BOOST_ASSERT_MSG( ( lmin_ < lmax_ ) , "check min-max logic\n\n" );
  BOOST_ASSERT_MSG( ( L_coat > 0 ) && ( L_end_ > 0 ) , "check L inputs\n\n" );
  BOOST_ASSERT_MSG( ( kc > 0 ) && ( psic > 0 ) , "check kc inputs\n\n" );

  constexpr size_t box = 7;
  constexpr double rangeLim[box] = {1e-3, 1e-2, 1e-1, 1e0, 1e1, 1e2, 1e3};

  BOOST_ASSERT_MSG( ( lmin_ >= rangeLim[0] ) &&
                    ( lmax_ <= rangeLim[box-1] )  , "check min-max range\n\n" );
  l_min = lmin_;
  l_max = lmax_;
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

  if( sum > 1)
  {
    L_end = L_end_;
    L_end *=sum;
  }
  else if(sum <= 1)
  {
    L_end = L_end_;
  }

  updateNMeasurements();
  math::range1og10(l_min, l_max, L_end, l_thermal);

  for (size_t i=0; i < L_end; ++i )
  {
    omegas[i] = thermal::omega(L_coat, l_thermal[i], kc, psic);
  }

  return L_end;
}


void  Kernal::updateNMeasurements()
{
  omegas.resize(L_end);
  l_thermal.resize(L_end);
}


}}
