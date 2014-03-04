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
#include <vector>
#include <string>
#include <functional>
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>

#include "thermal/analysis/kernal.hpp"
#include "thermal/analysis/methods.hpp"
#include "thermal/analysis/pie.hpp"
#include "math/estimation/parameterestimation.hpp"
#include "models/physicalmodel.hpp"
#include "math/algorithms/combinations.hpp"
#include "math/utility.hpp"

namespace thermal{
namespace analysis{

methods::methods(
    const math::estimation::settings &Settings_in,
    const math::estimation::unknownList &unknownParameters_in,
    const ThermalData& thermalData_in ,
    const math::estimation::unknownList &thermalSweepSearch ,
    const std::vector<physicalModel::labels> &sweepOptimizationGoal,
                 const physicalModel::layer coating, const size_t iter )
  : bestfitMethod( new LMA( Settings_in, unknownParameters_in,
                            thermalData_in.size() ) ),
    intervalEstimates( new PIE() ),
    lthermalSweepOptimizer(
      new ThermalSweepOptimizer( Settings_in,
                                 thermalData_in,
                                 unknownParameters_in,
                                 bestfitMethod,
                                 intervalEstimates ,
                                 thermalSweepSearch,
                                 sweepOptimizationGoal,
                                 coating, iter) )
{
}

methods& methods::operator=( const methods& that )
{
  if(this != &that)
  {
     bestfitMethod = that.bestfitMethod;
     intervalEstimates = that.intervalEstimates;
     lthermalSweepOptimizer = that.lthermalSweepOptimizer;
  }
  return *this;
}

double methods::bestFit(
    const std::shared_ptr< math::estimation::unknownList > &list_in,
    const std::shared_ptr< ThermalData > &thermalData_in,
    const std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in )
{
  bestfitMethod->solve( list_in, thermalData_in, coreSystem_in );
  return thermalData_in->MSE;
}

PIE::PIEAnalysisOutput
methods::parameterIntervalEstimates(
    const std::shared_ptr< math::estimation::unknownList > &list_in,
    const std::shared_ptr< ThermalData > &thermalData_in,
    const std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in )
{
  return intervalEstimates->solve( list_in, thermalData_in, coreSystem_in,
                            bestfitMethod );
}

ThermalSweepOptimizer::OptimizerOutput methods::optimization(
    const std::shared_ptr< math::estimation::unknownList > &list_in,
    const std::shared_ptr< ThermalData > &thermalData_in,
    const std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in )
{
  return lthermalSweepOptimizer->solve( list_in, thermalData_in, coreSystem_in,
                                        bestfitMethod, intervalEstimates ) ;

}

std::string methods::montecarloMap(
    const std::shared_ptr< math::estimation::unknownList > &list_in,
    const std::shared_ptr< ThermalData > &thermalData_in,
    const std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in)
{
  return lthermalSweepOptimizer->montecarloMap( list_in, thermalData_in,
                                                coreSystem_in, bestfitMethod,
                                                intervalEstimates ) ;
}

void methods::resetThermalSweepIni(void)
{
  lthermalSweepOptimizer->upSweepStartReset();
}





methods
loadMethodsfromFile( const boost::property_tree::ptree &mybranch,
                     const math::estimation::unknownList &parameterEstimation,
                     const ThermalData &thermData,
                     const physicalModel::layer &coating )
{
  using math::estimation::unknownList;
  using math::estimation::settings;
  using boost::property_tree::ptree;

  const ptree ptchild2 = mybranch.get_child( "ParaEstSettings" ) ;
  const settings estSettings( settings::loadConfigfromXML( ptchild2 ) ) ;


  const unknownList thermalSweep( unknownList::loadConfigfromXML( mybranch ) ) ;

  std::vector< physicalModel::labels > sweepOptimizationGoal ;
  BOOST_FOREACH( const ptree::value_type &v,
                 mybranch.get_child( "parameters" ) )
  {
    //retrieve subtree
    const ptree& child = v.second ;

    //access members of subtree
    physicalModel::labels labelmaker ;
    const std::string nameLabel = child.get< std::string >( "label" ) ;
    enum physicalModel::labels::Name mylabel ;
    try
    {
      mylabel = labelmaker.nameMap.right.at( nameLabel ) ;
    }
    catch( std::exception& e )
    {
      std::cerr << "Error with mylabel in poptea.xml labelmaker\n";
      exit( 1 ) ;
    }
    const physicalModel::labels output( mylabel ) ;
    sweepOptimizationGoal.push_back( output ) ;
  }

  const size_t iter = mybranch.get< size_t > ( "mappingIterations" );
  const methods analysis( estSettings, parameterEstimation, thermData,
                          thermalSweep, sweepOptimizationGoal,
                          coating, iter  ) ;
  return analysis;
}

}}
