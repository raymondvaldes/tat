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

#include "thermal/analysis/kernal.hpp"
#include "thermal/analysis/thermalData.hpp"
#include "thermal/analysis/lmdiff_poptea.hpp"
#include "thermal/analysis/pie.hpp"

namespace thermal{
namespace analysis{

class ThermalSweepOptimizer: private LMA_BASE
{
private:
//  void ThermalProp_Analysis( double *x, double *fvec,
//                             thermal::analysis::Kernal &popteaCore ) override;
//  void updateWorkSpace(const size_t Lend , const size_t N) override;

//  ThermalData paramter_estimation(int *info, int *nfev);
  //  double optiGfun( const double xCenter, const double xRange,
  //                   const enum physicalModel::labels::Name &mylabel ) ;
  //  void Optimization_Analysis( double *x, double *fvec,
  //                              thermal::analysis::Kernal &popteaCore ) ;
    std::vector<double> resizeExperimental( const double center,
                                            const double range,
                                            const size_t numPos ) ;
    std::shared_ptr< LMA > bestfitMethod;
    std::shared_ptr< PIE > intervalEstimates;


public:
  explicit ThermalSweepOptimizer(
      const math::estimation::settings &Settings_,
      const math::estimation::unknownList &unknownParameters,
      const size_t Lend_) ;
  ~ThermalSweepOptimizer(void);

  void start(
      std::shared_ptr<math::estimation::unknownList> &unknownParameters_in,
      std::shared_ptr<ThermalData> &thermalData_in,
      std::shared_ptr<Kernal> &coreSystem_in,
      std::shared_ptr< LMA > &bestfitMethod_in,
      std::shared_ptr< PIE > &intervalEstimates_in
      );
};


}}

#endif // THERMALSWEEPOPTIMIZER_HPP
