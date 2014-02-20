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

namespace thermal{
namespace analysis{

using namespace physicalModel;

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
      void prettyPrint( const std::string folder );
    };

    class SearchData
    {
      public:
      labels::Name param ;
      std::vector< std::pair< double, ThermalData > > allThermalData ;
      ThermalSweep thermalSweep;

      std::string pprint( void ) ;
      void ppThermalSweep ( const std::string folder) ;
    };
    std::shared_ptr< ThermalData > bestFitThermal ;
    std::shared_ptr< physicalModel::layer > bestFitCoat ;

    std::vector< SearchData > searchPath ;
    std::shared_ptr< math::estimation::unknownList > myUnknowns ;


    /// Post-PIE analysis methods
    std::string ppThermalSweep ( void );
    std::string ppSearchPath( const labels::Name input ) ;
    std::string ppEmissionLimits( const labels::Name input ) ;
    void pp2Folder(const std::string path );
    void clear( void ) ;

  private:
    SearchData retrieveSearchData(const labels::Name input ) ;
  } ouputResults;


  explicit PIE( void ) ;
  ~PIE( ) ;

  PIEAnalysisOutput
  solve( const std::shared_ptr< math::estimation::unknownList > &list_in,
         const std::shared_ptr< ThermalData > &thermalData_in,
         const std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in,
         const std::shared_ptr< LMA > bestfitMethod_in ) ;

private:
  /// Heavy duty workers
  std::shared_ptr< LMA > bestfitMethod;
  double bestFit();
  void parameterIntervalEstimates( void ) ;

  /// worker methods
  double Gfunc( const double x , const labels::Name &mylabel ) ;
  void updateExperimentalData( const std::vector<double> &input,
                               ThermalData &thermalData_in ) ;
  void saveExperimental( const ThermalData& thermalData_in ) ;
  void reloadExperimental( void );
  double solveFORx( const double target , const double min, const double max,
                    const labels::Name mylabel,
                    const std::string &bound ) ;

  PIEAnalysisOutput::SearchData dataTempStorage;
  PIEAnalysisOutput::ThermalSweep ThermalSweepTEMP;
  /// TO BO REMOVED
  std::vector<double>SAVEExperimental;
  std::vector<double>SAVEpredictions;
  std::vector<double>SAVEomega;
};

}}
#endif // PIE_HPP
