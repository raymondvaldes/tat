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
#ifndef PIE_HPP
#define PIE_HPP

#include <memory>
#include "math/estimation/parameterestimation.hpp"
#include "thermal/analysis/thermalData.hpp"
#include "thermal/analysis/kernal.hpp"
#include "thermal/analysis/lmdiff_poptea.hpp"
#include "thermal/model/labels.h"
#include "sensible/layer.h"

namespace thermal{
namespace analysis{

  using thermal::model::labels;
  
class PIE: private baseData
{
public:
  class PIEAnalysisOutput
  { 
  public:
    /// struct SearchData dataTempStorage;
    class ThermalSweep
    {
      public:
      ThermalData lowerbound;
      ThermalData bestfit;
      ThermalData upperbound;
      void prettyPrint( const std::string folder ) noexcept;
    };

    class SearchData
    {
      public:
      labels::Name param ;
      std::vector< std::pair< double, ThermalData > > allThermalData ;
      ThermalSweep thermalSweep;

      std::string pprint( void ) noexcept;
      void ppThermalSweep ( const std::string folder) noexcept;
    };
    std::shared_ptr< ThermalData > bestFitThermal ;
    std::shared_ptr< sensible::layer > bestFitCoat ;
    std::shared_ptr< sensible::layer > trueCoat ;

    std::vector< SearchData > searchPath ;
    std::shared_ptr< math::estimation::unknownList > myUnknowns ;


    /// Post-PIE analysis methods
    std::string ppThermalSweep ( void ) noexcept;
    std::string ppSearchPath( const labels::Name input ) noexcept;
    std::string ppEmissionLimits( const labels::Name input ) noexcept;
    void pp2Folder(const std::string path ) noexcept;
    void clear( void ) noexcept;

  private:
    SearchData retrieveSearchData(const labels::Name input ) noexcept;
  } ouputResults;


  explicit PIE( void ) noexcept;
  ~PIE( ) noexcept;

  PIEAnalysisOutput
  solve( const std::shared_ptr< math::estimation::unknownList > &list_in,
         const std::shared_ptr< ThermalData > &thermalData_in,
         const std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in,
         const std::shared_ptr< LMA > bestfitMethod_in ) noexcept;

private:
  /// Heavy duty workers
  std::shared_ptr< LMA > bestfitMethod;
  double bestFit() noexcept;
  void parameterIntervalEstimates( void ) noexcept;

  /// worker methods
  double Gfunc( const double x , const labels::Name &mylabel ) noexcept;
  void updateExperimentalData( const std::vector<double> &input,
                               ThermalData &thermalData_in ) noexcept;
  void saveExperimental( const ThermalData& thermalData_in ) noexcept;
  void reloadExperimental( void ) noexcept;
  double solveFORx( const double target , const double min, const double max,
                    const labels::Name mylabel,
                    const std::string &bound ) noexcept;

  PIEAnalysisOutput::SearchData dataTempStorage;
  PIEAnalysisOutput::ThermalSweep ThermalSweepTEMP;
  /// TO BO REMOVED
  std::vector<double>SAVEExperimental;
  std::vector<double>SAVEpredictions;
  std::vector<double>SAVEomega;
};

}}
#endif // PIE_HPP
