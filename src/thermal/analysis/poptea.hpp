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
#ifndef poptea_HPP
#define poptea_HPP

#include <utility>

#include "thermal/analysis/kernal.hpp"
#include "math/estimation/parameterestimation.hpp"
#include "math/sensitivityAnalysis/estimationInterval.hpp"
#include "math/bisection.hpp"
#include "models/expEquipment.hpp"
#include "models/physicalmodel.hpp"
#include "tools/filesystem.hpp"
#include "thermal/model.hpp"
#include "thermal/thermal.hpp"

namespace thermal {
namespace analysis{

class Poptea
{
private:
  class math::estimation::unknownList unknownParameterswithBFdata;
  class math::estimation::unknownList unknownParameters;

  enum physicalModel::labels::Name currentParameterX;
//  class math::estimation::unknown currentParameter;


  std::vector<double> ref_PHASE_BF;          //phase
  std::vector<double> experimental_PHASE_BF; //phase
  std::vector<double> current_PHASE_BF;      //phase

public:
  double S1_BF;
  double S1_X;
  double S1_current;

  class Kernal coreSystem;

   explicit Poptea( const class Kernal coreSystem_) ;
  ~Poptea( void );

  void setThermalRange(const double lmin, const double lmax);
  void loadExperimentalData( const std::vector<double> data );
  void setParameterstoFit( class math::estimation::unknownList parameters );
  void setParametertoHoldX(enum physicalModel::labels::Name currentParameterX_);
  void saveListunknowns(  );

  double meanError( const std::vector<double> curveBF,
                    const std::vector<double> curveRef );

  double bestFit( class Kernal core );

  std::pair< double, double >
  parameterInterval( const enum physicalModel::labels::Name currentPx,
                     std::vector<double> emissionExperimentalOriginal );


  double Gfunc( const double x );
   ///Gfunc must work by updating kernal with unknown parameters
   ///updating experimental with predicted values;

  std::pair< double, double >
  Gsolve( enum physicalModel::labels::Name currentParameterX_ );

  void saveBestFitParameters( void );
  void setG1(void);

};


}}
#endif // poptea_HPP
