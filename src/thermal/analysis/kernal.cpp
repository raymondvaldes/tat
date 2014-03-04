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
#include <exception>

#include "thermal/analysis/kernal.hpp"
#include "models/expEquipment.hpp"
#include "thermal/simulations/numericalmodel.hpp"
#include "math/estimation/parameterestimation.hpp"
#include "math/estimation/constrained.hpp"
#include "math/utility.hpp"
#include "tools/interface/filesystem.hpp"
#include "thermal/model.hpp"
#include "thermal/thermal.hpp"
#include "tools/interface/xml.h"

namespace thermal {
namespace analysis{



Kernal::Kernal( const equipment::setup &expSetup_,
                const physicalModel::TBCsystem &TBCsystem_,
                const model &thermalsys_,
                const filesystem::directory &DataDirectory_ )
  : expSetup(expSetup_),
    TBCsystem(TBCsystem_),
    thermalsys(thermalsys_),
    DataDirectory(DataDirectory_)
{

}

class thermal::analysis::Kernal
        Kernal::loadConfig( const boost::property_tree::ptree &pt,
                            const filesystem::directory &DataDirectory_)
{
  using boost::property_tree::ptree;

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
  const size_t iter   = ptchild3.get<size_t>( "mesh.num_iter" );
  const class numericalModel::Mesh mesh(M2, Rend, Nend, beta1, split,
                                  Obj2.coating.depth,
                                  Obj2.substrate.depth,
                                  Obj1.laser.radius,
                                  Obj2.radius, iter);

  const class thermal::model Ojb3NEW( Construct , mesh);

  //Load class object from previous objects
  const class Kernal kernal( Obj1, Obj2, Ojb3NEW, DataDirectory_);
  return kernal;
}

Kernal::~Kernal(void){}




double Kernal::bEval(void) const
{
  return expSetup.laser.radius / TBCsystem.coating.depth;
}

void Kernal::updatefromBestFit( std::vector< math::estimation::unknown > list )
{
  for( const auto& unknown :  list )
  {
    const double val = unknown.bestfit();
    TBCsystem.updateVal( unknown.label() , val );
  }
  TBCsystem.updateCoat();
}

class Kernal
    loadWorkingDirectoryKernal( const class filesystem::directory &dir )
{
  const std::string filename = "kernal.xml";
  boost::property_tree::ptree pt;
  try
  {
    boost::property_tree::read_xml( dir.abs( filename ), pt);
  }
  catch (std::exception& e)
  {
    std::cout << "file " << dir.abs( filename ) << " not found! See --help\n";
    exit(-2);
  }

  return Kernal::loadConfig( pt , dir);
}


}}
