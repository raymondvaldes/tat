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
#ifndef SOLUTION_HPP
#define SOLUTION_HPP

#include "models/physicalmodel.hpp"


namespace thermal {
namespace analysis{


class ThermalData
{
private:
  const size_t LendMinDecade = 50;
  void  updateNMeasurements( const double L_end );
  double thermalSetupTEMP(const double lmin_, const double lmax_,
                           const double L_coat, const double kc,
                           const double psic);
  /// Heat Transfer and Emission models
  const double l_min = .04;
  const double l_max = 4;

public:
  std::vector<double> omegas;
  std::vector<double> l_thermal;

  explicit ThermalData( const physicalModel::layer coating );
  ThermalData& operator=(const ThermalData& that);
  ~ThermalData();

  size_t thermalSetup( const double lmin_, const double lmax_,
                       const physicalModel::layer coating );
};


}}

#endif // SOLUTION_HPP
