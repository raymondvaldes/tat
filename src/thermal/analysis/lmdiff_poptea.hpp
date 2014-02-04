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

class LMA_BASE
{
protected:
  /// working objects
  std::shared_ptr< math::estimation::unknownList > unknownParameters_p;
  std::shared_ptr< ThermalData > thermalData;
  std::shared_ptr< Kernal > coreSystem_p;
  math::estimation::settings Settings;
  LMA_workingArrays LMA_workspace;

  int nfev;
  int info;
  std::function< void( double*, double*, Kernal &) >
  myReduced;
  virtual void ThermalProp_Analysis( double *x, double *fvec,
                                     Kernal &popteaCore ) = 0 ;
  void updateBindFunc( void );
  virtual void updateWorkSpace(const size_t Lend , const size_t N) = 0;

public:
  explicit LMA_BASE( const math::estimation::settings &Settings_,
                     const math::estimation::unknownList &unknownParameters_,
                     const size_t Lend_ );

  virtual void solve(
      std::shared_ptr<math::estimation::unknownList> &unknownParameters_in,
      std::shared_ptr<ThermalData> &thermalData_in,
      std::shared_ptr<Kernal> &coreSystem_in ) = 0;
};



class LMA: public LMA_BASE
{
private:
  void ThermalProp_Analysis( double *x, double *fvec,
                             Kernal &popteaCore ) override;
  ThermalData paramter_estimation(int *info, int *nfev);
  void updateWorkSpace(const size_t Lend , const size_t N) override;

public:
  explicit LMA( const math::estimation::settings &Settings_,
                const math::estimation::unknownList &unknownParameters,
                const size_t Lend_) ;
  ~LMA(void);
  void solve(
      std::shared_ptr<math::estimation::unknownList> &unknownParameters_in,
      std::shared_ptr<ThermalData> &thermalData_in,
      std::shared_ptr<Kernal> &coreSystem_in ) override;
};

class ThermalSweepOptimizer: public LMA_BASE
{
private:
//  void ThermalProp_Analysis( double *x, double *fvec,
//                             thermal::analysis::Kernal &popteaCore ) override;
//  void updateWorkSpace(const size_t Lend , const size_t N) override;

//  ThermalData paramter_estimation(int *info, int *nfev);

public:
  explicit ThermalSweepOptimizer(
      const math::estimation::settings &Settings_,
      const math::estimation::unknownList &unknownParameters,
      const size_t Lend_) ;
  ~ThermalSweepOptimizer(void);

  void solve(
      std::shared_ptr<math::estimation::unknownList> &unknownParameters_in,
      std::shared_ptr<ThermalData> &thermalData_in,
      std::shared_ptr<Kernal> &coreSystem_in ) override;
};


}}


void printPEstimates( const physicalModel::TBCsystem TBCSystem,
                      math::estimation::unknownList list );

#endif // LMDIFF_POPTEA_HPP
