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
#ifndef PIE_HPP
#define PIE_HPP

#include <memory>
#include "math/estimation/parameterestimation.hpp"
#include "thermal/analysis/thermalData.hpp"
#include "thermal/analysis/kernal.hpp"
#include "thermal/analysis/lmdiff_poptea.hpp"

namespace thermal{
namespace analysis{

class PIE: public baseData
{
private:
  std::shared_ptr< LMA > bestfitMethod;
  double bestFit();

  std::vector<double>SAVEExperimental;
  std::vector<double>SAVEomega;
  void parameterIntervalEstimates( void ) ;

  double Gfunc( const double x , const physicalModel::labels::Name &mylabel ) ;
  void updateExperimentalData( const std::vector<double> &input,
                               ThermalData &thermalData_in ) ;
  void saveExperimental( const ThermalData& thermalData_in ) ;

  double solveFORx( const double target , const double min, const double max,
                    const physicalModel::labels::Name mylabel,
                    const std::string &bound ) ;

public:
  explicit PIE(void ) ;
  void solve( std::shared_ptr< math::estimation::unknownList > &list_in,
               std::shared_ptr< ThermalData > &thermalData_in,
               std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in,
               std::shared_ptr< LMA > bestfitMethod_in ) ;
  ~PIE();
};

}}

#endif // PIE_HPP
