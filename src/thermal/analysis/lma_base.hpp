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

#ifndef LMA_BASE_HPP
#define LMA_BASE_HPP

#include <functional>
#include <cstddef>
#include <memory>

#include "math/estimation/parameterestimation.hpp"
#include "thermal/analysis/thermalData.hpp"
#include "thermal/analysis/kernal.hpp"
#include "thermal/analysis/poptea.hpp"
#include "thermal/analysis/lmdiff_poptea_help.hpp"

namespace thermal {
namespace analysis{

//class LMA_BASE
//{
//protected:
//  /// working objects
//  std::shared_ptr< math::estimation::unknownList > unknownParameters_p;
//  std::shared_ptr< ThermalData > thermalData;
//  std::shared_ptr< thermal::analysis::Kernal > coreSystem_p;

//  // ThermalData thermalData;
//  math::estimation::settings Settings;
//  LMA_workingArrays LMA_workspace;

//  int nfev;
//  int info;
//  std::function< void( double*, double*, thermal::analysis::Kernal &) >
//  myReduced;

//  virtual void ThermalProp_Analysis( double *x, double *fvec,
//                             thermal::analysis::Kernal &popteaCore ) ;
//  virtual void updateBindFunc( void );
//  virtual void updateWorkSpace(const size_t Lend , const size_t N);

//public:
//  virtual void solve(
//      std::shared_ptr<math::estimation::unknownList> &unknownParameters_in,
//      std::shared_ptr<ThermalData> &thermalData_in,
//      std::shared_ptr<Kernal> &coreSystem_in );
//};

}}

#endif // LMA_BASE_HPP
