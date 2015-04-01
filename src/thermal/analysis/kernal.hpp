/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#ifndef popteaCore_HPP
#define popteaCore_HPP

#include <boost/property_tree/ptree.hpp>
#include <utility>
#include <vector>

#include "thermal/analysis/kernal.hpp"
#include "thermal/equipment/setup.h"
#include "math/estimation/parameterestimation.hpp"
#include "tools/interface/filesystem.hpp"
#include "thermal/define/model.hpp"
#include "thermal/model/labels.h"

#include "sensible/TBCsystem.h"

namespace thermal {
namespace analysis{

class Kernal
{
public:
  /// core members
  equipment::setup expSetup;
  sensible::TBCsystem TBCsystem;
  define::model thermalsys;
  filesystem::directory DataDirectory;

  /// constructors and object creators
  Kernal( const equipment::setup &expSetup_,
          const sensible::TBCsystem &TBCsystem_,
          const define::model &thermalsys_,
          const filesystem::directory &DataDirectory_ ) noexcept;
  static Kernal loadConfig( const boost::property_tree::ptree &pt,
                            const filesystem::directory &DataDirectory_) noexcept;
  ~Kernal( void ) noexcept;

  /// Operations that give results
  double bEval(void) const noexcept;
  void updatefromBestFit( std::vector< math::estimation::unknown > list ) noexcept;
  void updatefromInitial( std::vector< math::estimation::unknown > list ) noexcept;
  void updateFromList( const enum model::labels::Name mylabel ,
                       const double val ) noexcept;
  
  std::pair< std::shared_ptr< Kernal >, std::vector<double> >
  updateCoreOmegaFromList(
    const std::vector<double> &omegas,
    const std::vector< std::pair < enum model::labels::Name, double > > list,
    const size_t ith ) const noexcept;
  
  // reload members
  void reloadthermalsys( const define::construct &other ) noexcept;

};

Kernal loadWorkingDirectoryKernal(const filesystem::directory &dir) noexcept;
}}

template<typename OBJ>
void reassign( std::shared_ptr< OBJ > &var, const OBJ &input ) noexcept
{ var.reset( new OBJ( input )  ); }


#endif // popteaCore_HPP
