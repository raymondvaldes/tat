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
#include "sensible/layer.h"

namespace thermal{
namespace analysis{


class ThermalSweepOptimizer: private LMA_BASE
{  
public:
  ///output object
  class OptimizerOutput
  {
  public:
    struct ExperimentAnalysisState
    {
      std::shared_ptr< ThermalData > thermalData ;
      std::shared_ptr< sensible::layer > coating ;
      std::shared_ptr< math::estimation::unknownList > unknownParameters ;
      std::shared_ptr< math::estimation::unknownList > thermalSweepSearch ;

      double fitquality ;
      double meanParameterError;
      std::pair<double, double> lthermalLimits ;
      std::pair<double, double> lthermalCenterDecades ;
      std::pair<double, double> omegaLimits;

      std::string ppFinalResults( void ) ;
      std::string ppEmissionSweep( void ) ;
      void ppExportEmissionSweep( const std::string path ) ;
      void ppExportAll( const std::string path );

      void clear( void ) ;
    };

    struct SearchPath
    {
      std::shared_ptr< sensible::layer > coating_final ;
      std::vector< ExperimentAnalysisState > path ;
      void clear( void ) ;
      void push_back( const ExperimentAnalysisState &data_in ) ;
      std::string prettyPrint( void ) ;
    } searchPath ;

    struct Comparison
    {
      std::shared_ptr< ExperimentAnalysisState > before ;
      std::shared_ptr< ExperimentAnalysisState > after ;
      std::shared_ptr< ThermalData > preFitted ;
      std::shared_ptr< ThermalData > postFitted ;
      void prettyPrint( const std::string path );
    } results ;

    /// Post-PIE analysis methods
    void push_back( const ExperimentAnalysisState &data_in ) ;
    void pp2Folder( const std::string path , const std::string i) ;
    void clear( void ) ;
    void addBefore( const ExperimentAnalysisState &input,
                    const std::shared_ptr<ThermalData> &thermalData);
    void addAfter( const ExperimentAnalysisState &input,
                   const std::shared_ptr<Kernal> &coreSystem  );

  } ouputResults;

  // constructors and destructors
  explicit ThermalSweepOptimizer(
      const math::estimation::settings &Settings_in,
      const ThermalData &thermalData_in,
      const math::estimation::unknownList &unknownParameters_,
      const std::shared_ptr< LMA > &bestfitMethod_in,
      const std::shared_ptr< PIE > &intervalEstimates_in,
      const math::estimation::unknownList thermalSweepSearch_in,
      const std::vector< thermal::model::labels > sweepOptimizationGoal_in,
      const sensible::layer coating,
      const size_t iter_in,
      const double lmin_in, const double lmax_in ) ;
  ~ThermalSweepOptimizer( void ) ;

  // public solver (yes just give it all this shit and it'll do the work for u)
  OptimizerOutput solve(
     const std::shared_ptr<math::estimation::unknownList> &unknownParameters_in,
     const std::shared_ptr<ThermalData> &thermalData_in,
     const std::shared_ptr<Kernal> &coreSystem_in,
     const std::shared_ptr< LMA > &bestfitMethod_in,
     const std::shared_ptr< PIE > &intervalEstimates_in
     ) ;
  std::string contourMappingwithMC();

private:
  // overide methods inherited
  void updateWorkSpace( const size_t Lend , const size_t N ) override;
  void updateWorkSpace(
      const math::estimation::unknownList &thermalSweepSearch_in,
      const std::vector<thermal::model::labels> &sweepOptimizationGoal_in);

  void ThermalProp_Analysis( double *x, double *fvec ) override;
  void solve(
    const std::shared_ptr<math::estimation::unknownList>&unknownParameters_in,
    const std::shared_ptr<ThermalData> &thermalData_in,
    const std::shared_ptr<Kernal> &coreSystem_in ) override;

  // settings Objects
  std::shared_ptr< LMA > bestfitMethod;
  std::shared_ptr< PIE > intervalEstimates;
  math::estimation::unknownList thermalSweepSearch;
  std::vector<thermal::model::labels> sweepOptimizationGoal ;

  // worker Objects
  std::shared_ptr< sensible::layer > coatingTOinterpretFullRange;
  std::shared_ptr< ThermalData > fullRangeThermalData;
  std::pair<double, double> xSweep;
  std::pair<double, double> updatedLimits;
  std::shared_ptr< math::estimation::unknownList > unknownBestFit;
  
  struct SweepSettings {
    const double lmin;
    const double lmax;
    const size_t iter;
    SweepSettings( const double lmin_in, const double lmax_in,
                   const size_t iter_in )
      : lmin( lmin_in ), lmax( lmax_in ), iter( iter_in )  {};
  } sweepSettings;

  // worker methods
  ThermalData sliceThermalData( const double xCenter, const double xRange,
                                const sensible::layer updatedCoating ) ;
  std::pair< double, double > updateSweep( void ) ;
  void pieAnalysis(void);
  double penalty( const std::pair<double, double>  thermalCenterRange,
                  const double error ) ;
  ThermalData updatedFromXsearch( double *x );
  void resize_ThermalCenterRange( double *x ) ;
  void uncertainty_for_subset_pushback_ouputResults( double *x ) ;
  std::string contourMapping( const vector< vector< double > > group_x_CR ) ;

  // current state
  OptimizerOutput::ExperimentAnalysisState currentState;
  void captureState(const sensible::layer &coat );

  // solvers
  void optimizer( int *info, int *nfev );

  // thermal mapping
  const size_t iter;
};

}}

#endif // THERMALSWEEPOPTIMIZER_HPP
