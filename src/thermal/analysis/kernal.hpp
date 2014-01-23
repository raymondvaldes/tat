/*----------------------------------------------------------------------------*\
  ========                      |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||   	  		|
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
#ifndef popteaCore_HPP
#define popteaCore_HPP

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include "models/expEquipment.hpp"
#include "models/physicalmodel.hpp"
#include "math/estimation/parameterestimation.hpp"
#include "tools/filesystem.hpp"
#include "thermal/model.hpp"

namespace thermal {
namespace analysis{

class Kernal
{
public:
  class equipment::setup expSetup;
  class physicalModel::TBCsystem TBCsystem;
  class thermal::model thermalsys;
  class math::estimation::LMA LMA;
  class filesystem::directory DataDirectory;

  Kernal( class equipment::setup expSetup_,
          class physicalModel::TBCsystem TBCsystem_,
          class thermal::model thermalsys_,
          class math::estimation::settings Settings_,
          class math::estimation::unknownList unknownParameters_,
          class filesystem::directory DataDirectory_ ) ;

  static Kernal loadConfig( const std::string &filename,
                const class filesystem::directory DataDirectory_);

  ~Kernal( void );





  double l_min, l_max; ///MUST REMOVE
  size_t L_end;     ///MUST REMOVE
  std::vector<double> omegas; ///MUST REMOVE
  std::vector<double> l_thermal;  ///MUST REMOVE
  double thermalSetupTEMP(const double lmin_, const double lmax_,
                          const double L_coat, const double kc, const double psic,
                          const size_t L_end_);
  void updateNMeasurements();
  void thermalSetup( const double lmin_, const double lmax_, //MUST BE REMOVED
                   const size_t LendMin);                  //MUST BE REMOVED
  double bEval(void) const;                                 //MUST BE REMOVED




};


}}

#endif // popteaCore_HPP
