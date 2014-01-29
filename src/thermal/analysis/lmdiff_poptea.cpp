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
#include <functional>
#include <cstddef>
#include <vector>
#include <boost/foreach.hpp>
#include <iostream>

#include "math/statistical_tools.hpp"
#include "math/estimation/constrained.hpp"
#include "math/estimation/utils.hpp"
#include "math/utility.hpp"
#include "thermal/analysis/lmdiff_poptea.hpp"
#include "thermal/emission/phase99.hpp"

namespace thermal {
namespace analysis{


LMA::LMA(const math::estimation::settings &Settings_,
          const math::estimation::unknownList &unknownParameters_,
          const size_t Lend_, const ThermalData &thermalData_)
  : thermalData(thermalData_), Settings(Settings_),
    unknownParameters(unknownParameters_),
    LMA_workspace( Lend_, unknownParameters_.size() )
{
  myReducedUpdate();
}

LMA::~LMA(void){}

void LMA::updateUnknownParameters(
    const std::vector< class math::estimation::unknown > &unknownList_ )
{
  std::vector<class math::estimation::unknown> updated(unknownList_);
  unknownParameters( updated );


//  const size_t Default = LMA_workspace.emissionExperimental.size();
  const size_t Default = LMA_workspace.fvec.size();
  updateWorkSpace( Default, updated.size() ) ;
}

void LMA::myReducedUpdate( void )
{
  myReduced =
  std::bind( &LMA::ThermalProp_Analysis, this , std::placeholders::_1,
             std::placeholders::_2, std::placeholders::_3) ;
}


void LMA::updateWorkSpace( const size_t Lend, const size_t N )
{
  LMA_workspace.updateArraySize( Lend , N );
}

void LMA::updateThermalData( class ThermalData thermalData_ )
{
  thermalData = thermalData_;
}

class ThermalData
LMA::paramter_estimation( int *info, int *nfev,  Kernal &coreSystem,
                          ThermalData input )
{
  updateThermalData( input );

  using namespace math::estimation;
  const size_t m = thermalData.omegas.size();
  const size_t n = unknownParameters.size();

  ///Create workspaces
  double *x = new double[n];
  double *fvec = new double[m];
  double *qtf = new double[n];
  double *wa1 = new double[n];
  double *wa2 = new double[n];
  double *wa3 = new double[n];
  double *wa4 = new double[m];
  double *fjac = new double[m*n];
  double *wa5 = new double[m*n];
  int *ipvt = new int[n];
  double *diag = new double[n];

  ///populate initial values
  std::vector<double>xInitial;
  for( const auto &unknown : unknownParameters() )
    { xInitial.push_back( unknown.initialVal() ); }
  for( size_t i=0 ; i< n ; i++ )
    { x[i] = xInitial[i]; }

  scaleDiag( diag, unknownParameters , coreSystem.TBCsystem,
             Settings.mode ) ;

  ///Transform inputs
  int j = 0;
  for( const auto& unknown : unknownParameters() )
  {
    x[j] = kx_limiter2( x[j], unknown.lowerBound(), unknown.upperBound() );
    j++;
  }

  ///levenberg-marquardt algorithm
  myReducedUpdate();
  lmdif( myReduced , m, n, x, fvec, Settings.ftol,
         Settings.xtol, Settings.gtol, Settings.maxfev,
         Settings.epsfcn, diag, Settings.mode,
         Settings.factor, Settings.nprint, info, nfev, fjac, m,
         ipvt, qtf, wa1, wa2, wa3, wa4, wa5, coreSystem ) ;

  //Transform outputs
  j=0;
  for( auto& unknown : unknownParameters() )
  {
    x[j] = x_limiter2(x[j], unknown.lowerBound(), unknown.upperBound());
    unknown.bestfitset(x[j]);
    j++;
  }

   ///Final fit
  coreSystem.updatefromBestFit( unknownParameters() );
  thermalData.predictedEmission = thermal::emission::phase99( coreSystem ,
                                                        thermalData.omegas );

  /// Quality-of-fit
  thermalData.MSE =
      math::estimation::SobjectiveLS( thermalData.experimentalEmission,
                                      thermalData.predictedEmission );

  delete [] qtf;
  delete [] wa1;
  delete [] wa2;
  delete [] wa3;
  delete [] wa4;
  delete [] wa5;
  delete [] ipvt;
  delete [] fvec;
  delete [] fjac;
  delete [] diag;
  delete [] x;

  return thermalData;
}


void LMA::ThermalProp_Analysis( double *x, double *fvec,
                                class thermal::analysis::Kernal &popteaCore)
{
  //Update parameters
  math::estimation::unknownList updatedInput;
  int i = 0;
  for( auto& unknown :  unknownParameters() )
  {
    const double val = math::estimation::
        x_limiter2( x[i++] , unknown.lowerBound(), unknown.upperBound() );
    unknown.bestfitset( val );
    updatedInput.addUnknown(unknown);
  }
  unknownParameters( updatedInput() );
  popteaCore.updatefromBestFit( unknownParameters()  );

  // Estimates the phase of emission at each heating frequency
  thermalData.predictedEmission =
      thermal::emission::phase99( popteaCore, thermalData.omegas );

  /// Evaluate Objective function
  for( size_t n = 0 ; n < thermalData.omegas.size() ; ++n )
  {
     fvec[n] =  thermalData.experimentalEmission[n] -
                    thermalData.predictedEmission[n] ;
  }

  thermalData.MSE =
      math::estimation::SobjectiveLS( thermalData.experimentalEmission,
                                      thermalData.predictedEmission );
  printPEstimates( popteaCore.TBCsystem, unknownParameters ) ;

  return;
}

}}

void printPEstimates( const class physicalModel::TBCsystem TBCSystem,
                      math::estimation::unknownList list )
{
  for( const auto& unknown : list() )
  {
    std::cout << TBCSystem.returnVal( unknown.label() ) << "  ";
  }

  std::cout << "\n";
  return;
}
