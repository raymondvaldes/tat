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
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "manyfit.hpp"
#include "tools/filesystem.hpp"
#include "thermal/analysis/kernal.hpp"
#include "algorithms/sensitivity_analysis.hpp"
#include "thermal/emission/phase99.hpp"
#include "thermal/analysis/poptea.hpp"

namespace investigations{
namespace manyfit{

void run( const class filesystem::directory dir )
{
  /// initiate poptea by importing configuration info
  using namespace thermal::analysis;
  class Poptea poptea = Poptea::loadConfigfromFile( dir );

  /// Create initial guess
  poptea.LMA.LMA_workspace.emissionNominal =
  thermal::emission::phase99( poptea.coreSystem, poptea.thermalData.omegas);


  /// execute
  for(size_t nn = 0; nn < poptea.thermalData.omegas.size() ; ++nn )
  {
    poptea.LMA.LMA_workspace.emissionExperimental[nn]
          = poptea.LMA.LMA_workspace.emissionNominal[nn];
  }

  constexpr size_t interants = 1;
  fitting( poptea, interants );
}

}
}

