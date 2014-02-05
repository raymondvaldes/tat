/*----------------------------------------------------------------------------*\
  ========                  |
     ||     T Thermal       | TAT: Thermal Analysis Toolbox
     ||     A Analysis      |
     ||     T Toolbox       | Copyright (C) 2013 Raymond Valdes
     ||                     |
--------------------------------------------------------------------------------
License
    This file is part of Thermal Analysis Toolbox.

    Thermal Analysis Toolbox is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    Thermal Analysis Toolbox is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
    Public License for more details.

    You should have received a copy of the GNU General Public License along with
    Thermal Analysis Toolbox.  If not, see <http://www.gnu.org/licenses/>.

\*----------------------------------------------------------------------------*/

#ifndef THERMALSWEEPOPTIMIZER_HPP
#define THERMALSWEEPOPTIMIZER_HPP

#include <cstddef>
#include <memory>

#include "thermal/analysis/kernal.hpp"
#include "thermal/analysis/thermalData.hpp"
#include "thermal/analysis/lmdiff_poptea.hpp"
#include "thermal/analysis/pie.hpp"
#include "models/physicalmodel.hpp"

namespace thermal{
namespace analysis{


class ThermalSweepOptimizer: private LMA_BASE
{
private:
  // overide methods inherited
  void updateWorkSpace( const size_t Lend , const size_t N ) override;
  void updateWorkSpace(
      const math::estimation::unknownList &thermalSweepSearch_in,
      const std::vector<physicalModel::labels> &sweepOptimizationGoal_in);

  void ThermalProp_Analysis( double *x, double *fvec,
                             thermal::analysis::Kernal &popteaCore ) override;
  void solve(
    const std::shared_ptr<math::estimation::unknownList>&unknownParameters_in,
    const std::shared_ptr<ThermalData> &thermalData_in,
    const std::shared_ptr<Kernal> &coreSystem_in ) override;

  // settings Objects
  math::estimation::unknownList thermalSweepSearch;
  std::vector<physicalModel::labels> sweepOptimizationGoal ;

  // worker Objects
  std::shared_ptr< physicalModel::layer > coatingTOinterpretFullRange;
  std::shared_ptr< ThermalData > fullRangeThermalData;
  std::shared_ptr< LMA > bestfitMethod;
  std::shared_ptr< PIE > intervalEstimates;
  std::pair<double, double> xSweep;

  // worker methods
  ThermalData sliceThermalData( const double xCenter, const double xRange,
                                const physicalModel::layer updatedCoating ) ;
  std::pair< double, double >
  updateVal(const std::pair<double, double> xSweep) ;
  // solvers
//  double bestFit( void ) ;
//  void pieAnalysis( void ) ;
  void optimizer(void);

public:
  // constructors and destructors
  explicit ThermalSweepOptimizer(
      const math::estimation::settings &Settings_in,
      const ThermalData &thermalData_in,
      const math::estimation::unknownList &unknownParameters_,
      const std::shared_ptr< LMA > &bestfitMethod_in,
      const std::shared_ptr< PIE > &intervalEstimates_in,
      const math::estimation::unknownList thermalSweepSearch_in,
      const std::vector< physicalModel::labels > sweepOptimizationGoal_in,
      const physicalModel::layer coating ) ;
  ~ThermalSweepOptimizer( void ) ;

  // public solver (yes just give it all this shit and it'll do the work for u)
  void solve(
     const std::shared_ptr<math::estimation::unknownList> &unknownParameters_in,
     const std::shared_ptr<ThermalData> &thermalData_in,
     const std::shared_ptr<Kernal> &coreSystem_in,
     const std::shared_ptr< LMA > &bestfitMethod_in,
     const std::shared_ptr< PIE > &intervalEstimates_in
     );
};

}}

#endif // THERMALSWEEPOPTIMIZER_HPP
