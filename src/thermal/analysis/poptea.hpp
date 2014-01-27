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

#include "thermal/analysis/kernal.hpp"
#include "thermal/analysis/lmdiff_poptea.hpp"
#include "thermal/analysis/sa_sensitivity.hpp"
#include "thermal/analysis/solution.hpp"

#include "math/estimation/parameterestimation.hpp"
#include "models/physicalmodel.hpp"

namespace thermal {
namespace analysis{

class Poptea
{
private:
  void updateNMeasurements( const double L_end );

public:
  class Kernal coreSystem;
  class ThermalData thermalData;
  class LMA LMA;
  class SA_Sensitivity SA;

  explicit Poptea( const class Kernal &coreSystem_ ,
                   const class ThermalData &thermaldata_,
                   const class math::estimation::settings &Settings_,
                   const math::estimation::unknownList &unknownParameters_) ;

  static Poptea loadConfig( const Kernal &coreSystem_,
                            const boost::property_tree::ptree &pt ) ;

  static Poptea loadConfigfromFile( const class filesystem::directory &dir ) ;
  ~Poptea( void );

  void updatelthermal( const double lmin, const double lmax,
                       const double lminperDecade);


  /// These should be pushed down another level
  double bestFit( class Kernal core );  //REMOVE
  std::pair< double, double >
  parameterInterval( const enum physicalModel::labels::Name currentPx,
                     std::vector<double> emissionExperimentalOriginal );  //HIGHER LEVEL BUT YES
  void loadExperimentalData( const std::vector<double> data );
  void setParameterstoFit( class math::estimation::unknownList parameters );
  void setParametertoHoldX( enum physicalModel::labels::Name currentParameterX_);
};


}}
#endif // poptea_HPP
