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

#include "models/physicalmodel.hpp"


namespace thermal {
namespace analysis{

class ThermalData
{
private:
  void  updateNMeasurements( const double L_end );
  double thermalSetupTEMP( const double lmin_, const double lmax_,
                           const size_t lminPerDecarde,
                           const double L_coat, const double kc,
                           const double psic);
public:
  std::vector<double> omegas;
  std::vector<double> l_thermal;

  //Constructors, destructors and assignment operators
  explicit ThermalData( const double l_min, const double l_max,
                        const size_t lminPerDecarde,
                        const physicalModel::layer &coating );
  ThermalData& operator = (const ThermalData& that);
  ~ThermalData();

  static class ThermalData
  loadConfigfromXML( const boost::property_tree::ptree pt,
                     const physicalModel::layer &coating );

  //modify data
  void updateLthermal( const std::vector<double> &input,
                       const physicalModel::layer &coating );
  void updateOmegas(const std::vector<double> input ,
                    const physicalModel::layer &coating);
  size_t thermalSetup( const double lmin, const double lmax,
                       const size_t lminPerDecarde ,
                       const physicalModel::layer &coating  );

};


}}

#endif // THERMALDATA_HPP
