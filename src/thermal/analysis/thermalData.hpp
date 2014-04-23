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
#ifndef THERMALDATA_HPP
#define THERMALDATA_HPP

#include <sstream>
#include "math/estimation/parameterestimation.hpp"
#include "sensible/layer.h"

namespace thermal {
namespace analysis{

  using std::vector;
  
class ThermalData
{
private:
  size_t numMeasurements(const double lmin_, const double lmax_);
  void clearVectors(void);
  void resizeVectors( const size_t Lend);
  std::pair<double, double> lthermalLimits;

public:
  vector<double> omegas;
  vector<double> experimentalEmission;
  vector<double> predictedEmission;
  std::pair<double, double> lthermalPredicted;
  size_t measurementsPerDecade;
  double MSE;

  //Constructors, destructors and assignment operators
  explicit ThermalData( const double l_min, const double l_max,
                        const size_t lminPerDecarde,
                        const sensible::layer &coating ) ;
  explicit ThermalData( void ) ;
  ThermalData& operator = ( const ThermalData& that ) ;
  ~ThermalData();

  static class ThermalData
  loadConfigfromXML( const boost::property_tree::ptree pt,
                     const sensible::layer &coating ) ;

  //get information
  size_t size( void ) const;
  vector<double> get_lthermalSweep( const sensible::layer &coating ) const ;
  std::pair<double, double>
  get_lthermalLimits( const sensible::layer &coating ) const ;
  std::pair<double, double> get_omegaLimits( void ) const ;

  //modify data
  void updateExperimental( const std::vector<double> &input ) ;
  
  size_t thermalSetup( const double lmin, const double lmax,
                       const sensible::layer &coating ) ;
  
  void updatefromBestFit( std::vector< math::estimation::unknown > list,
                          const sensible::layer &coating,
                          const ThermalData fullData ) ;

  //printer
  std::string prettyPrint( const sensible::layer &coating ) ;
  std::string prettyPrint( void ) ;

};


}}

#endif // THERMALDATA_HPP
