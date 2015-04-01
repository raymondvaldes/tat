/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
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
  size_t numMeasurements(const double lmin_, const double lmax_) noexcept;
  void clearVectors(void) noexcept;
  void resizeVectors( const size_t Lend) noexcept;
  std::pair<double, double> lthermalLimits ;

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
                        const sensible::layer &coating ) noexcept;
  explicit ThermalData( void ) noexcept;
  ThermalData& operator = ( const ThermalData& that ) noexcept;
  ~ThermalData() noexcept;

  static class ThermalData
  loadConfigfromXML( const boost::property_tree::ptree pt,
                     const sensible::layer &coating ) noexcept;

  //get information
  size_t size( void ) const noexcept;
  vector<double> get_lthermalSweep( const sensible::layer &coating ) const noexcept;
  std::pair<double, double>
  get_lthermalLimits( const sensible::layer &coating ) const noexcept;
  std::pair<double, double> get_omegaLimits( void ) const noexcept;

  //modify data
  void updateExperimental( const std::vector<double> &input ) noexcept;
  
  size_t thermalSetup( const double lmin, const double lmax,
                       const sensible::layer &coating ) noexcept;
  
  void updatefromBestFit( std::vector< math::estimation::unknown > list,
                          const sensible::layer &coating) noexcept;

//  printer
  std::string prettyPrint( const sensible::layer &coating,
                           const std::vector<double> & nominalEmission ) noexcept ;
  std::string prettyPrint( const sensible::layer &coating ) noexcept;
  std::string prettyPrint( void ) noexcept;

};


}}

#endif // THERMALDATA_HPP
