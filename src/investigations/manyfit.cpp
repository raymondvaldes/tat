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
#include <array>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "manyfit.hpp"
#include "tools/interface/filesystem.hpp"
#include "thermal/analysis/kernal.hpp"
#include "thermal/emission/phase99.hpp"
#include "thermal/analysis/poptea.hpp"
#include "math/utility.hpp"

namespace investigations{
namespace manyfit{

void run( const class filesystem::directory dir )
{
  /// initiate poptea by importing configuration info
  using namespace thermal::analysis;
  class Poptea poptea = Poptea::loadConfigfromFile( dir );

  /// Create initial guess
  std::vector<double>emissionNominal=
  thermal::emission::phase99( *(poptea.coreSystem), poptea.thermalData->omegas );

  /// execute
  for(size_t nn = 0; nn < poptea.thermalData->omegas.size() ; ++nn )
  {
    poptea.thermalData->experimentalEmission[nn]
          = emissionNominal[nn];

    std::cout << poptea.thermalData->experimentalEmission[nn] << "\t"
              << emissionNominal[nn] << "\n";
  }

  constexpr size_t interants = 10;
  fitting( poptea, interants );
}

}}


void fitting( class thermal::analysis::Poptea poptea,
              const size_t interants )
{
  std::vector<double>xInitial;
  for( const auto &unknown : (*poptea.unknownParameters)() )
    { xInitial.push_back( unknown.initialVal() ); }

/// Scale jacobian if enabled
  std::ofstream myfile;
  std::stringstream filename;
  filename <<  "../data/fittingData.dat";
  myfile.open(filename.str().c_str());
  myfile << std::setprecision(8);
  myfile << "#run\tasub_0\tgamma_0\tEsigma_0\tR1_0\tlambda_0";
  myfile << "\tasub\tgamma\tEsigma\tR1\tlambda\n";

  std::vector<double>xSave(xInitial);

  for( size_t i=0; i<interants; ++i )
  {
      myfile << i << "\t";

      poptea.bestFit();

//      myfile << *(poptea.coreSystem).TBCsystem.gammaEval() << "\t"
//             << *(poptea.coreSystem).TBCsystem.a_subEval() << "\t"
//             << *(poptea.coreSystem).TBCsystem.optical.Emit1 << "\t"
//             << *(poptea.coreSystem).TBCsystem.optical.R1<< "\t"
//             << *(poptea.coreSystem).TBCsystem.coating.lambda << "\n"

//      printPEstimates( *(poptea.coreSystem).TBCsystem,
//                       *(poptea.unknownParameters) ) ;
  }

  myfile.close();


  return;
}



