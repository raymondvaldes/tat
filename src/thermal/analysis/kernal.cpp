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
#include <memory>

#include "thermal/analysis/kernal.hpp"
#include "thermal/equipment/setup.h"
#include "thermal/model/one_dim/numerical_2011/mesh.hpp"

#include "math/estimation/parameterestimation.hpp"
#include "math/estimation/constrained.hpp"
#include "math/utility.hpp"
#include "tools/interface/filesystem.hpp"
#include "thermal/define/model.hpp"
#include "tools/interface/xml.h"

namespace thermal {
namespace analysis{


Kernal::Kernal( const equipment::setup &expSetup_,
                const sensible::TBCsystem  &TBCsystem_,
                const define::model &thermalsys_,
                const filesystem::directory &DataDirectory_ )
  : expSetup(expSetup_),
    TBCsystem(TBCsystem_),
    thermalsys(thermalsys_),
    DataDirectory(DataDirectory_)
{

}

  
std::pair< std::shared_ptr< Kernal >, std::vector<double> >
Kernal::updateCoreOmegaFromList(
    const std::vector<double> &omegas,
    const std::vector< std::pair < enum model::labels::Name, double > > list,
    const size_t ith ) const
{
  using model::labels::Name::omega;
  using model::labels::Name::experimentalData;
  using std::make_shared;
  using std::shared_ptr;
  using std::make_pair;
  using std::vector;
  
  shared_ptr< Kernal > corePerturbed = make_shared<Kernal>(*this);
  vector<double> omegasPertrubed = omegas;
  
  const size_t N = omegas.size();
  BOOST_ASSERT( ith <= N ) ;
  BOOST_ASSERT( ith >= 0 ) ;
  
  for( auto val: list )
  {
    const bool omegaV = val.first == omega ;
    const bool experimentalV = val.first == experimentalData ;
  
    if( !omegaV && !experimentalV ) {
      corePerturbed->updateFromList( val.first, val.second ) ;
    }
    else {
      BOOST_ASSERT( ith < N && ith >= 0 ) ;
      if( omegaV ) {
        omegasPertrubed[ith] *= val.second ;
      }
    }
  }
  
  
  return make_pair( make_shared<Kernal>( *corePerturbed ) , omegasPertrubed ) ;
}


class thermal::analysis::Kernal
        Kernal::loadConfig( const boost::property_tree::ptree &pt,
                            const filesystem::directory &DataDirectory_)
{
  using boost::property_tree::ptree;

  const std::string conjunto = "kernal.";
  const ptree ptchild1 = pt.get_child( conjunto + "experimentalSetup" );
  const equipment::setup Obj1( equipment::setup::loadConfigfromXML( ptchild1 ));

  const ptree ptchild2 = pt.get_child( conjunto + "TBCsystem" );
  const sensible::TBCsystem 
    Obj2( sensible::TBCsystem ::loadConfig( ptchild2 ) );

  const ptree ptchild3 = pt.get_child( conjunto + "thermalModel" );
  const define::construct
    Construct( define::construct::loadConfigfromXML( ptchild3 ) );

  /// Mesh is intrinsically linked the TBCsystem and experimental setup
  const size_t M2     = ptchild3.get<size_t>( "mesh.M2" );
  const size_t Rend   = ptchild3.get<size_t>( "mesh.Rend");
  const size_t Nend   = ptchild3.get<size_t>( "mesh.Nend" );
  const double beta1  = ptchild3.get<double>( "mesh.beta1" );
  const double split  = ptchild3.get<double>( "mesh.split" );
  const size_t iter   = ptchild3.get<size_t>( "mesh.num_iter" );
  const numericalModel::Mesh mesh( M2, Rend, Nend, beta1, split,
                                   Obj2.coating.getDepth(),
                                   Obj2.substrate.getDepth(),
                                   Obj1.laser.radius,
                                   Obj2.radius, iter);

  const define::model Ojb3NEW( Construct , mesh);

  //Load class object from previous objects
  const Kernal kernal( Obj1, Obj2, Ojb3NEW, DataDirectory_);
  return kernal;
}

Kernal::~Kernal(void){}




double Kernal::bEval(void) const
{
  return expSetup.laser.radius / TBCsystem.coating.getDepth();
}

void Kernal::updatefromBestFit( std::vector< math::estimation::unknown > list )
{
  for( const auto& unknown :  list ) {
    const double val = unknown.bestfit();
    TBCsystem.updateVal( unknown.label() , val );
  }
  TBCsystem.updateCoat();
}

void Kernal::updatefromInitial( std::vector< math::estimation::unknown > list )
{
  using math::estimation::unknown;
  for( const auto& unknown :  list ) {
    const double val = unknown.initialVal();
    TBCsystem.updateVal( unknown.label() , val );
  }
  TBCsystem.updateCoat();
}

void Kernal::updateFromList( const enum model::labels::Name mylabel ,
                             const double percentChange )
{
  BOOST_ASSERT( percentChange > 0 ) ;
  
  const double val = TBCsystem.returnVal( mylabel ) ;
  const double val_change = val * percentChange ;


  TBCsystem.updateVal( mylabel , val_change ) ;
  TBCsystem.updateCoat();
}


class Kernal
    loadWorkingDirectoryKernal( const filesystem::directory &dir )
{
  using boost::property_tree::ptree;

  const std::string filename = "kernal.xml";
  const std::string fullpath = dir.abs( filename );
  ptree pt = tools::interface::getTreefromFile( fullpath ) ;

  return Kernal::loadConfig( pt , dir);
}


  void Kernal::reloadthermalsys( const define::construct &other )
{
  
  thermalsys.reloadThermalConstruct( other );
  
  return;
}
  
  
}}
