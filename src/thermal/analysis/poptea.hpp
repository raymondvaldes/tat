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
#ifndef poptea_HPP
#define poptea_HPP

#include <vector>
#include <utility>
#include <boost/property_tree/ptree.hpp>

#include "thermal/analysis/kernal.hpp"
#include "thermal/analysis/thermalData.hpp"
#include "thermal/analysis/methods.hpp"

namespace thermal {
namespace analysis{

class Poptea: public baseData
{
private:
  bool loadedExperimental = false;
  bool runbestfit = false;
  methods analysis;

public:
  /// constructors and object creators
  explicit Poptea(
      const Kernal &coreSystem_ ,
      const ThermalData &thermaldata_,
      const math::estimation::settings &Settings_,
      const math::estimation::unknownList &unknownParameters_,
      const math::estimation::unknownList &thermalSweepSearch,
      const std::vector< physicalModel::labels > sweepOptimizationGoal) ;

  static Poptea loadConfig( const Kernal &coreSystem_,
                            const boost::property_tree::ptree &pt ) ;
  static Poptea loadConfigfromFile( const filesystem::directory &dir ) ;
  ~Poptea( void );

  /// Member operations that update on multiple members
  void updateExperimentalData( const std::vector<double> &omegas,
                               const std::vector<double> &input ) ;

  /// Operations that give results
  double bestFit( void ) ;
  void PIE ( void );
  void optimization(void);
  std::vector<double> thermalSweep(void) const;

  void parameterIntervalEstimates( void ) ;
} ;

class Poptea
loadWorkingDirectoryPoptea( const filesystem::directory dir,
                            const Kernal &popteaCore);
}}
#endif // poptea_HPP
