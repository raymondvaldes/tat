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
#include "models/Thermal_models.h"
#include "models/numericalmodel.hpp"
#include "math/estimation/parameterestimation.hpp"
#include "tools/filesystem.hpp"
#include "thermal/model.hpp"

namespace thermalAnalysis
{

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
  LMA.LMA_workspace.MSETol = 1e-8;

  /// Heat Transfer and Emission models
  const double l_min = .04;
  const double l_max = 4;
  const size_t LendMinDecade = 50;

  // Populate the experimental phase values in parameters99
  expSetup.laser.L_end = LendMinDecade;
  expSetup.q_surface = 0;
  thermalSetup(l_min, l_max, LendMinDecade);
}

class thermalAnalysis::Kernal
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

  const std::string conjunto = "poptea.";
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
  expSetup.laser.L_end = expSetup.laser.thermalSetup(lmin_, lmax_,
                                      TBCsystem.coating.depth,
                                      TBCsystem.coating.kthermal.offset,
                                      TBCsystem.coating.psithermal.offset ,
                                      LendMin);

  LMA.LMA_workspace.updateArraySize(expSetup.laser.L_end,
                                    LMA.unknownParameters.Nsize());
}

double Kernal::bEval(void) const
{
  return expSetup.laser.radius / TBCsystem.coating.depth;
}

}
