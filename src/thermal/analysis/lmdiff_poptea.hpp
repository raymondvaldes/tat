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
#ifndef LMDIFF_POPTEA_HPP
#define LMDIFF_POPTEA_HPP

#include <vector>
#include <utility>

#include "thermal/analysis/kernal.hpp"
#include "thermal/analysis/lmdiff_poptea.hpp"
#include "thermal/analysis/lmdiff_poptea_help.hpp"
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
  std::function<void(int, int, double*, double*, int*,
                           class thermal::analysis::Kernal)> myReduced =
  std::bind(&LMA::ThermalProp_Analysis, this , std::placeholders::_1,
            std::placeholders::_2, std::placeholders::_3, std::placeholders::_4,
            std::placeholders::_5, std::placeholders::_6);

public:
  class LMA_workingArrays LMA_workspace;
  class math::estimation::settings Settings;
  class math::estimation::unknownList unknownParameters;

  std::vector<double> omegas;
  std::vector<double> experimental;
  std::vector<double> xInitial{ 2.1, 3.7, 40, 0.75, 0.5 } ; //FIX THIS TODO BUG
  std::vector<double> xpredicted;  //FIX THIS TODO BUG
  std::vector<double> xguessAuto;  //FIX THIS TODO BUG

  explicit LMA( const struct math::estimation::settings Settings_,
                const class math::estimation::unknownList unknownParameters) ;
  ~LMA(void);
  void resetInitialGuess(const std::vector<double> input);

  void ThermalProp_Analysis( int /*P*/, int /*N*/, double *x, double *fvec,
                             int * /*iflag*/,
                             class thermal::analysis::Kernal popteaCore);

  std::vector<double>
  paramter_estimation( int *info, int *nfev,
                            class Kernal coreSystem );
};






}
}

#endif // LMDIFF_POPTEA_HPP
