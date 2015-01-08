/*----------------------------------------------------------------------------*\
 ========               |
    || 	 T Thermal      | TAT: Thermal Analysis Toolbox
    ||   A Analysis     |
    || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	        	|
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

#include "num_method2014.h"
#include "thermal/analysis/poptea.hpp"
#include "thermal/analysis/poptea_initialize.h"
#include "thermal/emission/phase99.hpp"
#include "thermal/analysis/sweep/temp_cmplx.h"
#include "thermal/analysis/cmplx_combination/cmplx_combination.h"

#include "physics/classical_mechanics/kinematics.h"
#include "math/utility.hpp"

namespace investigations{
  namespace num_method{
    
using namespace thermal::analysis;

void run( const filesystem::directory &dir ) noexcept
{
  using std::string;
  using std::vector;
  using std::complex;
  using std::cout;
  using thermal::define::construct;
  using thermal::define::HeatX;
  using thermal::define::EmissionX;
  using thermal::emission::phase99;
  using thermal::analysis::sweep::temp_cplx_99;


  /// setup output
  Poptea poptea = initializePopTeawithNominalEmission( dir ) ;
  construct theoreticalModel = poptea.coreSystem->thermalsys.Construct ;
  
  /// prepare new thermal model
  theoreticalModel.update( HeatX::OneDimAnalytical, EmissionX::OneDimNonLin ) ;
  poptea.reloadThermalModel( theoreticalModel) ;
  
  /// output emission
  vector<double> emission1 = phase99( *( poptea.coreSystem ) , poptea.thermalData->omegas ) ;
  
  const size_t unit = poptea.thermalData->omegas.size() - 1;
  const double omega = poptea.thermalData->omegas[unit] ;
  std::cout << omega << "\n";

  const size_t temp_resolution = 100;
  vector<complex<double >> heat1_cplx =
  temp_cplx_99( *( poptea.coreSystem ) , omega , temp_resolution ) ;
  const size_t z_pos = 0;
  const complex<double> Tcplx = heat1_cplx[z_pos] ;
  cout << "the complex number is:\t" << Tcplx << "\n";


  using thermal::analysis::Tcplx_to_Ttransient;
  using thermal::analysis::Ttransient_to_Tcplx;
  const size_t res = 102;
  const vector<double> zval = math::range(0,1,res);


  using std::abs ;
  using std::arg ;
  cout << "mod:  " << abs( Tcplx ) << "\targ:\t" << arg( Tcplx ) <<"\n\n";

  vector<double> test = Tcplx_to_Ttransient( Tcplx , omega, res ) ;
  vector<double> time = t_cmplx_to_t_time( omega, res );
  
  using physics::classical_mechanics::angularFrequency_to_period;
  cout << "period is\t " << angularFrequency_to_period( omega )  << "\n" ;
  cout << "zpos is\t" << zval[z_pos ] << "\n";
  cout << "the complex number is:\t" << heat1_cplx[z_pos] << "\n" ;

  
  complex<double> time_transformed = Ttransient_to_Tcplx(test);
  cout << "the complex number is:\t" << time_transformed << "\n\n";

  theoreticalModel.update( HeatX::OneDimNumLin, EmissionX::OneDimNonLin ) ;
  poptea.reloadThermalModel( theoreticalModel ) ;
  const vector<double> emission2 =
  phase99( *( poptea.coreSystem ) , poptea.thermalData->omegas ) ;
  
  const vector<complex< double >> heat2_cplx =
  temp_cplx_99( *( poptea.coreSystem ) , poptea.thermalData->omegas[unit] ,
                temp_resolution ) ;
  
  
  cout << "\n\n";
  cout << "complex temperature fields" << "\n";
  
  
  /// Part test
  // poptea.bestFit() ;
  cout << poptea.ppUnknownParameters() << "\n" << temp_resolution;
  
  
  return;
}
    
}}
