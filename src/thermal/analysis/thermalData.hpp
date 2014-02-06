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

#include "math/estimation/parameterestimation.hpp"

namespace thermal {
namespace analysis{

class ThermalData
{
private:
  size_t numMeasurements(const double lmin_, const double lmax_);
  void clearVectors(void);
  void resizeVectors( const size_t Lend);
  const std::pair<double, double> lthermalLimits;

public:
  std::vector<double> omegas;
  std::vector<double> experimentalEmission;
  std::vector<double> predictedEmission;
  std::pair<double, double> lthermalPredicted;
  const size_t measurementsPerDecade;
  double MSE;

  //Constructors, destructors and assignment operators
  explicit ThermalData( const double l_min,
                        const double l_max,
                        const size_t lminPerDecarde,
                        const physicalModel::layer &coating );  
  ThermalData& operator = (const ThermalData& that);
  ~ThermalData();

  static class ThermalData
  loadConfigfromXML( const boost::property_tree::ptree pt,
                     const physicalModel::layer &coating );

  //get information
  size_t size(void) const;
  std::vector<double>
  get_lthermalSweep( const physicalModel::layer &coating ) const;
  std::pair<double, double>
  get_lthermalLimits( const physicalModel::layer &coating) const;
  std::pair<double, double>
  get_omegaLimits( const physicalModel::layer &coating) const;

  //modify data
  void updateExperimental( const std::vector<double> &input );
  size_t thermalSetup( const double lmin, const double lmax,
                       const physicalModel::layer &coating );
  void updatefromBestFit( std::vector< math::estimation::unknown > list,
                          const physicalModel::layer &coating,
                          const ThermalData fullData);

};


}}

#endif // THERMALDATA_HPP
