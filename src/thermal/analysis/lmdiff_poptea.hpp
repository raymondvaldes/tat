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
#include <functional>

#include "sensible/TBCsystem.h"
#include "math/estimation/lmdiff.hpp"
#include "thermal/analysis/kernal.hpp"
#include "thermal/analysis/lmdiff_poptea.hpp"
#include "thermal/analysis/lmdiff_poptea_help.hpp"
#include "thermal/analysis/thermalData.hpp"
#include "math/estimation/parameterestimation.hpp"
#include "math/bisection.hpp"
#include "tools/interface/filesystem.hpp"
#include "thermal/define/model.hpp"
#include "thermal/analysis/basedata.hpp"

namespace thermal {
namespace analysis{

class LMA_BASE: public baseData
{
protected:
  /// working objects
  math::estimation::settings Settings;
  LMA_workingArrays LMA_workspace;

  int nfev = 0;
  int info = -1;
  std::function< void( double*, double* ) > myReduced;

  virtual void ThermalProp_Analysis( double *x, double *fvec ) noexcept = 0 ;
  void updateBindFunc( void ) noexcept;
  virtual void updateWorkSpace(const size_t Lend , const size_t N) noexcept = 0;

public:
  explicit LMA_BASE( const math::estimation::settings &Settings_,
                     const math::estimation::unknownList &unknownParameters_,
                     const size_t Lend_ ) noexcept;
  virtual ~LMA_BASE() noexcept;

  virtual void solve(
      const std::shared_ptr<math::estimation::unknownList>&unknownParameters_in,
      const std::shared_ptr<ThermalData> &thermalData_in,
      const std::shared_ptr<Kernal> &coreSystem_in ) noexcept = 0 ;
};



class LMA: public LMA_BASE
{
private:
  void ThermalProp_Analysis( double *x, double *fvec ) noexcept override ;
  ThermalData paramter_estimation(int *info, int *nfev) noexcept;
  void updateWorkSpace(const size_t Lend , const size_t N) noexcept override ;

public:
  class BestFitAnalysisOutput
  {
    public:
    void clear( void ) noexcept;
  };

  explicit LMA( const math::estimation::settings &Settings_,
                const math::estimation::unknownList &unknownParameters,
                const size_t Lend_) noexcept;
  ~LMA(void) noexcept;
  void solve(
      const std::shared_ptr<math::estimation::unknownList> &unknownParameters_in,
      const std::shared_ptr<ThermalData> &thermalData_in,
      const std::shared_ptr<Kernal> &coreSystem_in ) noexcept override ;
};


}}


void printPEstimates( const sensible::TBCsystem TBCSystem,
                      math::estimation::unknownList list ) noexcept;

#endif // LMDIFF_POPTEA_HPP
