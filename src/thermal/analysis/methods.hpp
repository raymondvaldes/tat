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
#ifndef METHODS_HPP
#define METHODS_HPP

#include <string>
#include <vector>

#include "models/physicalmodel.hpp"
#include "thermal/analysis/kernal.hpp"
#include "thermal/analysis/lmdiff_poptea.hpp"
#include "math/estimation/parameterestimation.hpp"

namespace thermal{
namespace analysis{

class methods{

private:


  double Gfunc( const double x , const physicalModel::labels::Name &mylabel,
                Kernal &coreSystem, ThermalData &thermalData,
                math::estimation::unknownList &list) ;

  double optiGfun( const double xCenter, const double xRange,
                   const enum physicalModel::labels::Name &mylabel,
                   Kernal &coreSystem, ThermalData &thermalData ,
                   math::estimation::unknownList &list) ;
  void updatelthermal(const double, const double);
  void updateExperimentalData( const std::vector<double> &omegas,
                               const std::vector<double> &input,
                               Kernal &coreSystem,
                               ThermalData &thermalData );

  std::vector<double>SAVEExperimental;
  std::vector<double>SAVEomega;

  std::vector<double>TEMPExperimental;
  std::vector<double>TEMPomega;
  std::vector<double> resizeExperimental( const double center,
                                          const double range,
                                          const size_t numPos ) ;

  void saveExperimental( const ThermalData& thermalData );

  Kernal *coreSystem;
  ThermalData *thermalData;


public:
  // Working objects
  class LMA bestfitMethod;

  //constructors
  methods( const math::estimation::settings &Settings_,
           const math::estimation::unknownList &unknownParameters_,
           const ThermalData& thermalData ) ;

  //output methods
  double bestFit( Kernal &coreSystem , ThermalData &thermalData ,
                  math::estimation::unknownList &list) ;
  void parameterIntervalEstimates( Kernal &coreSystem,
                                   ThermalData &thermalData ,
                                   math::estimation::unknownList &list) ;
  void optimization( Kernal &coreSystem,
                     ThermalData &thermalData,
                     math::estimation::unknownList &list);

  double solve(const double target , const double min, const double max,
                const physicalModel::labels::Name mylabel,
                const std::string &bound, Kernal &coreSystem,
                ThermalData &thermalData, math::estimation::unknownList &list) ;
};

}}

#endif // METHODS_HPP
