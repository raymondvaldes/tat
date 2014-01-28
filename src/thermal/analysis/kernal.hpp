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
  /// core members
  class equipment::setup expSetup;
  class physicalModel::TBCsystem TBCsystem;
  class thermal::model thermalsys;
  class filesystem::directory DataDirectory;

  /// constructors and object creators
  Kernal( const class equipment::setup &expSetup_,
          const class physicalModel::TBCsystem &TBCsystem_,
          const class thermal::model &thermalsys_,
          const class filesystem::directory &DataDirectory_ ) ;
  static Kernal loadConfig( const boost::property_tree::ptree &pt,
                            const class filesystem::directory &DataDirectory_);
  ~Kernal( void );

  /// Operations that give results
  double bEval(void) const;
  void updatefromBestFit( std::vector< math::estimation::unknown > list );



};

class Kernal loadWorkingDirectoryKernal(const class filesystem::directory dir);


}}

#endif // popteaCore_HPP
