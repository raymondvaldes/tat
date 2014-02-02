/*----------------------------------------------------------------------------*\
  ========                      |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||                         |
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
#ifndef LMDIFF_POPTEA_HPP
#define LMDIFF_POPTEA_HPP

#include <vector>
#include <utility>
#include <memory>

#include "thermal/analysis/kernal.hpp"
#include "thermal/analysis/lmdiff_poptea.hpp"
#include "thermal/analysis/lmdiff_poptea_help.hpp"
#include "thermal/analysis/thermalData.hpp"
#include "math/estimation/parameterestimation.hpp"
#include "math/sensitivityAnalysis/estimationInterval.hpp"
#include "math/bisection.hpp"
#include "models/expEquipment.hpp"
#include "tools/filesystem.hpp"
#include "thermal/model.hpp"
#include "thermal/thermal.hpp"

namespace thermal {
namespace analysis{

class LMA
{

private:

  int nfev;
  int info;

public:
  explicit LMA( const struct math::estimation::settings &Settings_,
                const math::estimation::unknownList &unknownParameters,
                const size_t Lend_) ;
  ~LMA(void);
  ThermalData solve(
      std::shared_ptr<math::estimation::unknownList> &unknownParameters_in,
      std::shared_ptr<ThermalData> &thermalData_in,
      std::shared_ptr<Kernal> &coreSystem_in );
private:
  std::function< void( double*, double*, thermal::analysis::Kernal &) >
  myReduced;
  void ThermalProp_Analysis( double *x, double *fvec,
                             thermal::analysis::Kernal &popteaCore ) ;
  void updateBindFunc( void );
  void updateWorkSpace(const size_t Lend , const size_t N);
  ThermalData paramter_estimation(int *info, int *nfev);

  /// working objects
  std::shared_ptr< math::estimation::unknownList > unknownParameters_p;
  std::shared_ptr< ThermalData > thermalData;
  std::shared_ptr< thermal::analysis::Kernal > coreSystem_p;

//  ThermalData thermalData;
  math::estimation::settings Settings;
  LMA_workingArrays LMA_workspace;

};

}}






void printPEstimates( const class physicalModel::TBCsystem TBCSystem,
                      math::estimation::unknownList list );

#endif // LMDIFF_POPTEA_HPP
