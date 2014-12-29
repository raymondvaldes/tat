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
#include <boost/math/special_functions/fpclassify.hpp>

#include "math/estimation/lmdiff.hpp"
#include "math/statistical_tools.hpp"
#include "math/estimation/constrained.hpp"
#include "math/estimation/utils.hpp"
#include "math/utility.hpp"
#include "thermal/analysis/lmdiff_poptea.hpp"
#include "thermal/emission/phase99.hpp"

namespace thermal {
namespace analysis{

LMA_BASE::LMA_BASE( const math::estimation::settings &Settings_,
                    const math::estimation::unknownList &unknownParameters_,
                    const size_t Lend_ ) noexcept
  : Settings(Settings_), LMA_workspace( Lend_, unknownParameters_.size() )
{}

LMA_BASE::~LMA_BASE() noexcept {}


void LMA_BASE::updateBindFunc( void ) noexcept
{
  using std::bind;
  using std::placeholders::_1;
  using std::placeholders::_2;
  
  myReduced = bind( &LMA_BASE::ThermalProp_Analysis, this , _1, _2 ) ;
}

void LMA::updateWorkSpace( const size_t Lend, const size_t N ) noexcept
{
  LMA_workspace.updateArraySize( Lend , N );
}


LMA::LMA( const math::estimation::settings &Settings_,
          const math::estimation::unknownList &unknownParameters_,
          const size_t Lend_ ) noexcept
  : LMA_BASE( Settings_, unknownParameters_, Lend_ )
{}

LMA::~LMA(void) noexcept {}



void LMA::solve(
    const std::shared_ptr<math::estimation::unknownList> &unknownParameters_in,
    const std::shared_ptr<ThermalData> &thermalData_in,
    const std::shared_ptr<Kernal> &coreSystem_in ) noexcept
{
  unknownParameters = unknownParameters_in ;
  thermalData = thermalData_in ;
  coreSystem = coreSystem_in ;

  ///update workspaces
  updateWorkSpace( thermalData->size() , unknownParameters->size() ) ;

  ///Solve
  paramter_estimation( &info, &nfev ) ;

  ///update core
  coreSystem->updatefromBestFit( (*unknownParameters)() ) ;
}


class ThermalData
LMA::paramter_estimation( int *info, int *nfev ) noexcept
{
  using std::vector;
  using thermal::emission::phase99;
  using math::estimation::SobjectiveLS ;
  using math::estimation::unknown;

  using namespace math::estimation;
  const int m = static_cast<int>(thermalData->omegas.size());
  const int n = static_cast<int>(unknownParameters->size());

  ///Create workspaces
  vector<double> fvec(m);
  vector<double> qtf(n);
  vector<double> wa1(n);
  vector<double> wa2(n);
  vector<double> wa3(n);
  vector<double> wa4(m);
  vector<double> fjac(m*n);

  vector<int> ipvt(n);
  vector<double> diag(n);

  ///populate initial values
  vector<double> x(n);
  vector<double> xInitial;

  for( const auto &unknown : (*unknownParameters)() ) {
    xInitial.push_back( unknown.initialVal() );
  }
  
  x = xInitial;
  
  
  for( size_t i=0 ; i< static_cast<size_t>(n) ; i++ ) {
    ipvt[i] = 9;
  }

  scaleDiag( diag.data(), *unknownParameters , coreSystem->TBCsystem,
             static_cast<int>(Settings.mode ) ) ;



  ///Transform inputs
  int j = 0;
  for( const auto& unknown : (*unknownParameters)() )
  {
    x[j] = kx_limiter2( xInitial[j], unknown.lowerBound(), unknown.upperBound() );
    j++;
  }

  ///levenberg-marquardt algorithm
  updateBindFunc();
  lmdif( myReduced , m, n, x.data(), fvec.data(), Settings.ftol, Settings.xtol,
         Settings.gtol,
         static_cast<int>(Settings.maxfev), Settings.epsfcn, diag.data(),
         static_cast<int>(Settings.mode), Settings.factor,
         static_cast<int>(Settings.nprint), info, nfev, fjac.data(), m,
         ipvt.data(), qtf.data(), wa1.data(), wa2.data(), wa3.data(),
         wa4.data() ) ;

  //Transform outputs
  j=0;
  for( unknown& unknown : unknownParameters->vectorUnknowns )
  {
    x[j] = x_limiter2( x[j], unknown.lowerBound(), unknown.upperBound() );
    unknown.bestfitset(x[j]);
    j++;
  }

   ///Final fit
  coreSystem->updatefromBestFit( (*unknownParameters)() );
  thermalData->predictedEmission = phase99( *coreSystem , thermalData->omegas );

  /// Quality-of-fit
  thermalData->MSE = SobjectiveLS(
        thermalData->experimentalEmission, thermalData->predictedEmission ) ;

//  std::cerr << "from inside bestfit " << thermalData->MSE << "\n";

//  std::cout << *nfev <<"\n";
//  printPEstimates( coreSystem->TBCsystem, *unknownParameters ) ;

  return *thermalData;
}


void LMA::ThermalProp_Analysis(double *x, double *fvec) noexcept
{
  BOOST_ASSERT( x != nullptr ) ;
  BOOST_ASSERT( fvec != nullptr ) ;
  
  for( size_t i = 0 ; i < unknownParameters->size() ; ++i ) {
    BOOST_ASSERT( !isnan( x[i] ) ) ;
  }
  
  
  using math::estimation::unknownList;
  using math::estimation::x_limiter2;
  using thermal::emission::phase99;
  using std::pow;
  using std::sqrt;
  
  //Update parameters
  //The reason I create a new list of unknownParameter is because the operator()
  unknownList updatedInput;
  
  int i = 0;
  for( auto& unknown :  (*unknownParameters)() )
  {
    const double val = x_limiter2( x[i++] , unknown.lowerBound(),
                                   unknown.upperBound() ) ;
    unknown.bestfitset( val );
    updatedInput.addUnknown( unknown ) ;
  }
  (*unknownParameters)( updatedInput() );
  coreSystem->updatefromBestFit( (*unknownParameters)()  );

  // Estimates the phase of emission at each heating frequency
  thermalData->predictedEmission = phase99( *coreSystem, thermalData->omegas ) ;

  /// Evaluate Objective function
  for( size_t n = 0 ; n < thermalData->omegas.size() ; ++n )
  {
     fvec[n] =  thermalData->experimentalEmission[n] ;
     fvec[n] -= thermalData->predictedEmission[n] ;
  }

  thermalData->lthermalPredicted =
      thermalData->get_lthermalLimits( coreSystem->TBCsystem.coating ) ;



  for( size_t j = 0 ; j < thermalData->omegas.size() ; ++j ) {
    BOOST_ASSERT( !isnan( fvec[j] ) ) ;
  }




  return;
}

}}

void printPEstimates( const sensible::TBCsystem  TBCSystem,
                      math::estimation::unknownList list ) noexcept
{
  using std::cout;
  
  for( const auto& unknown : list() )
  {
    cout << TBCSystem.returnVal( unknown.label() ) << "  ";
  }

  return;
}
