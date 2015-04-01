/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#include <cstddef>
#include <utility>
#include <iomanip>

#include "thermal/analysis/thermalData.hpp"
#include "math/utility.hpp"
#include "math/estimation/parameterestimation.hpp"
#include "thermal/define/omega.h"
#include "thermal/define/lthermal.h"

namespace thermal {
namespace analysis{

ThermalData::ThermalData(void) noexcept
{}

ThermalData::ThermalData( const double l_min, const double l_max,
                          const size_t lminPerDecarde,
                          const sensible::layer &coating ) noexcept
  : lthermalLimits(l_min, l_max), measurementsPerDecade(lminPerDecarde)
{
  thermalSetup( l_min, l_max, coating );
}

ThermalData::~ThermalData() noexcept{}

size_t ThermalData::thermalSetup( const double lmin, const double lmax,
                                  const sensible::layer &coating  ) noexcept

{
  size_t L_end = numMeasurements( lmin, lmax );

  clearVectors();
  resizeVectors( L_end );

  std::vector<double> lthermalTEMP = math::range1og10(lmin, lmax, L_end ) ;

  using thermal::define::omega;
  for (size_t i=0; i < L_end; ++i )
  {
    omegas[i] = omega( coating.getDepth(), lthermalTEMP[i],
                                coating.kthermal.offset,
                                coating.psithermal.offset ) ;
  }
  
  return L_end;
}

size_t ThermalData::size(void) const noexcept
{
  return omegas.size();
}

std::string
ThermalData::prettyPrint( const sensible::layer &coating ) noexcept
{
  std::ostringstream output;

  output << "#|-------------------------------------------------------------\n";
  output << "#| Phase of Emission                                           \n";
  output << "#|                                                             \n";
  output << "#| columns...                                                  \n";
  output << "#| omega      : heating wavelength                             \n";
  output << "#| Lambda     : thermal penetration                            \n";
  output << "#| expEmission: experimental phase of emit                     \n";
  output << "#| modEmission: model output phase of emit                     \n";
  output << "#|                                                             \n";
  output << "#|-------------------------------------------------------------\n";
  const std::vector<double> lthermals = get_lthermalSweep( coating ) ;

  assert( omegas.size() == lthermals.size() );
  assert( omegas.size() == experimentalEmission.size() );
  assert( omegas.size() == predictedEmission.size() );


  for( size_t i = 0 ; i < omegas.size() ; ++i )
  {
    output << omegas[i]
           << "\t" << lthermals[i]
           << "\t" << experimentalEmission[i]
           << "\t" << predictedEmission[i]
           << "\n";
  }

  return output.str() ;
}

std::string ThermalData::prettyPrint( void ) noexcept
{
  std::ostringstream output;

  output << "#|-------------------------------------------------------------\n";
  output << "#| Phase of Emission                                           \n";
  output << "#|                                                             \n";
  output << "#| columns...                                                  \n";
  output << "#| omega      : heating wavelength                             \n";
  output << "#| expEmission: experimental phase of emit                     \n";
  output << "#| modEmission: model output phase of emit                     \n";
  output << "#|                                                             \n";
  output << "#|-------------------------------------------------------------\n";
  for( size_t i = 0 ; i < omegas.size() ; ++i )
  {
    output << omegas[i]
           << "\t" << experimentalEmission[i]
           << "\t" << predictedEmission[i]
           << "\n";
  }

  return output.str() ;
}



std::string ThermalData::prettyPrint( const sensible::layer &coating,
                                    const std::vector<double> &nominalEmission ) noexcept
{
  std::ostringstream output;

  output << "#|-------------------------------------------------------------\n";
  output << "#| Phase of Emission                                           \n";
  output << "#|                                                             \n";
  output << "#| columns...                                                  \n";
  output << "#| omega      : heating wavelength                             \n";
  output << "#| Lambda     : thermal penetration                            \n";
  output << "#| expEmission: experimental phase of emit                     \n";
  output << "#| modEmission: model output phase of emit  (nominal)          \n";
  output << "#|                                                             \n";
  output << "#|-------------------------------------------------------------\n";
  const std::vector<double> lthermals = get_lthermalSweep( coating ) ;

  assert( omegas.size() == lthermals.size() );
  assert( omegas.size() == experimentalEmission.size() );
  assert( omegas.size() == nominalEmission.size() );


  for( size_t i = 0 ; i < omegas.size() ; ++i )
  {
    output << omegas[i]
           << "\t" << lthermals[i]
           << "\t" << experimentalEmission[i]
           << "\t" << nominalEmission[i]
           << "\n";
  }

  return output.str() ;
}


void ThermalData::clearVectors(void) noexcept
{
  omegas.clear();
  experimentalEmission.clear();
  predictedEmission.clear();
}

void ThermalData::resizeVectors( const size_t Lend) noexcept
{
  omegas.resize( Lend );
  experimentalEmission.resize( Lend );
  predictedEmission.resize( Lend );
}

std::pair<double, double>
ThermalData::get_omegaLimits( void ) const noexcept
{
  std::pair<double, double> output( omegas.front(), omegas.back() );
  return output;
}

std::pair<double, double>
ThermalData::get_lthermalLimits( const sensible::layer &coating) const noexcept
{
  using thermal::define::lthermal;
  const double first = lthermal( coating.getDepth(),
                                          coating.kthermal.offset,
                                          coating.psithermal.offset,
                                          omegas.front() ) ;

  const double second = lthermal( coating.getDepth(),
                                           coating.kthermal.offset,
                                           coating.psithermal.offset,
                                           omegas.back() ) ;

  const std::pair< double, double > output(first, second);
  return output;
}

std::vector<double>
ThermalData::get_lthermalSweep( const sensible::layer &coating ) const noexcept
{
  const size_t LEND = omegas.size();
  using thermal::define::lthermal;
  
  std::vector<double> output(LEND);
  for (size_t i=0; i < LEND ; ++i )
  {
    output[i] = lthermal( coating.getDepth(), coating.kthermal.offset,
                                   coating.psithermal.offset, omegas[i] ) ;
  }

  return output;
}


void ThermalData::updateExperimental( const std::vector<double> &input) noexcept
{
  BOOST_ASSERT( input.size() == experimentalEmission.size() );
  experimentalEmission = input;
}



ThermalData& ThermalData::operator=( const ThermalData& that ) noexcept
{
  if(this != &that)
  {
    omegas = that.omegas;
    experimentalEmission = that.experimentalEmission;
    predictedEmission = that.predictedEmission;
    lthermalPredicted = that.lthermalPredicted;
    measurementsPerDecade = that.measurementsPerDecade;
    MSE = that.MSE;
    lthermalLimits = that.lthermalLimits;
  }
  return *this;
}


void ThermalData::
updatefromBestFit( std::vector< math::estimation::unknown > list,
                   const sensible::layer &coating  ) noexcept
{

  double xCenter = 0;
  double xRange = 0;
  for( auto const& unknown :  list )
  {
    if( unknown.label() == thermal::model::labels::Name::thermalCenter )
      { xCenter = unknown.bestfit(); }
    else if( unknown.label() == thermal::model::labels::Name::thermalRange )
      { xRange = unknown.bestfit(); }
  }

  std::cout << "inside updatefromBestFit\n";
  std::cout << "\n" << xCenter << "\t" << xRange << "\n";
  std::pair<double, double> newThermalSweep =
  math::newThermalSweepLimits( xCenter, xRange, lthermalLimits);
  thermalSetup( newThermalSweep.first, newThermalSweep.second, coating);


  ///Experimental Data must be saved and used to be interpolated accross the
  /// restricted domain.  The experimental Data and sweep cannot be erased.

}

size_t ThermalData::numMeasurements( const double l_min, const double l_max ) noexcept
{
  const size_t L_end = measurementsPerDecade;
  BOOST_ASSERT_MSG( ( l_min < l_max ) , "check min-max logic\n\n" );


  constexpr size_t box = 7;
  constexpr double rangeLim[box] = {1e-3, 1e-2, 1e-1, 1e0, 1e1, 1e2, 1e3};

  BOOST_ASSERT_MSG( ( l_min >= rangeLim[0] ) &&
                    ( l_max <= rangeLim[box-1] )  , "check min-max range\n\n" );

  /* I need to create a function that determines the number of measurements
  necessary to satisfy L_end_ which is the minimum  number of measurements per
  decade. Once I determine the number of measurements I need then I can use
  the ::rangelog10 function to populate the range.*/

  double rangeFills[box-1] = {0};
  for(size_t i = 0; i < box-1 ; ++i)
  {
    if( l_min >= rangeLim[i+1]  || l_max <= rangeLim[i])
    {
      rangeFills[i] = 0;
    }
    else if( l_min <= rangeLim[i] && l_max >= rangeLim[i+1])
    {
      rangeFills[i] = 1;
    }
    else
    {
      double start = 0;
      if(l_min <= rangeLim[i])
      {
        start = 0;
      }
      else if( l_min < rangeLim[i+1] )
      {
        start = math::percentilelog10(rangeLim[i], rangeLim[i+1], l_min);
      }

      double end1 = 1;
      if(l_max >= rangeLim[i+1])
      {
        end1 = 1;
      }
      else if( l_max < rangeLim[i+1] )
      {
        end1 = math::percentilelog10(rangeLim[i], rangeLim[i+1], l_max);
      }

      rangeFills[i] = end1 - start;
    }
  }

  double sum = 0;
  for(size_t i = 0; i < box-1 ; ++i)
  {
    sum += rangeFills[i];
  }

  size_t Lnew = L_end;

  if( sum > 1)
  {
    Lnew = L_end;
    Lnew *=sum;
  }
  else if(sum <= 1)  //TODO REMOVE?
  {
    Lnew = L_end;
  }

  return Lnew;
}


class ThermalData ThermalData::
        loadConfigfromXML( const boost::property_tree::ptree pt,
                           const sensible::layer &coating ) noexcept
{
  using boost::property_tree::ptree;

  // Iterate over 'unknown' branches
  const double start  = pt.get<double>( "thermal_penetration.start" );
  const double end    = pt.get<double>( "thermal_penetration.end" );
  const size_t minperDecade = pt.get<size_t> ("minperDecade");

  ThermalData thermalData( start, end, minperDecade, coating );

  return thermalData;
}


}}
