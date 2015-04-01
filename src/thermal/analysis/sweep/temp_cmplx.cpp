/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#include <limits>
#include "thermal/analysis/sweep/temp_cmplx.h"
#include "thermal/model/one_dim/analytical_2005/analytical_2005.h"
#include "thermal/model/one_dim/numerical_2011/numerical_2011.h"
#include "math/algorithms/spline_cplx.h"
#include "math/utility.hpp"
#include "thermal/define/temperature.h"
#include "thermal/analysis/cmplx_combination/cmplx_combination.h"

namespace thermal{
namespace analysis{
namespace sweep{

std::vector< std::complex<double> >
temp_cplx_99( const thermal::analysis::Kernal &popteaCore,
              const double omega , const size_t M1) noexcept
{
  /*The result for each thermal penetration is calculated in parallel using the
  OpenMP framework.  This gives significant increases in the speed of the code
  for all ranges of L_end.  This also allows the code to be parallelized at
  a very high level. No further modifications of the code is necessary.*/
  using std::vector;
  using std::complex;

  
  /* A fine mesh will be used to report back the complex temperature.  This 
  will differ from the mesh used in the numerical solution for now.*/
  const size_t cntr_size = M1 + 1 ;
  vector< complex<double> > results( cntr_size ) ;
  constexpr double z_surf = 0;
  constexpr double z_interface = 1;
  const vector< double > z_val = math::range( z_surf, z_interface, cntr_size );
  

  switch( popteaCore.thermalsys.Construct.heat )
  {
    case define::HeatX::OneDimAnalytical:
    {
      using thermal::model::one_dim::analytical_2005;
      const analytical_2005 thermalEngine( popteaCore.TBCsystem.coating,
                                           popteaCore.TBCsystem.substrate,
                                           popteaCore.TBCsystem.optical,
                                           popteaCore.expSetup.laser,
                                           popteaCore.TBCsystem.Temp.rear,
                                           popteaCore.TBCsystem.gammaEval() ) ;
      using math::algorithms::spline_cplx;
      spline_cplx temp_cplx = thermalEngine.T_tt_R1eq1_cplx_sweep( omega ) ;

      for( size_t i = 0 ; i <= M1 ; ++i )
        results[i] = temp_cplx.eval( z_val[i] ) ;

      break;
    }

    case define::HeatX::OneDimNumLin:
    {
      using thermal::model::one_dim::numerical_2011;
      const numerical_2011 thermalEngine( popteaCore.TBCsystem.coating,
                                          popteaCore.TBCsystem.substrate,
                                          popteaCore.TBCsystem.optical,
                                          popteaCore.expSetup.laser,
                                          popteaCore.TBCsystem.Temp.rear,
                                          popteaCore.TBCsystem.gammaEval());
      constexpr size_t iter = 1000;
      constexpr double Ttol = .0001;

      using thermal::define::Temperature;
      const size_t Nend = popteaCore.thermalsys.mesh.Nend ;
      const size_t M2 =popteaCore.thermalsys.mesh.M2 ;
      Temperature Tprofile( Nend, M2 ) ;
      
      thermalEngine.temperature_1D( omega, iter, Ttol,
                                    popteaCore.thermalsys.mesh, Tprofile );
      
      
      for( size_t i = 0 ; i <= M1 ; ++i )
      {
//        const vector<double> Tsurface = Tprofile.eval_at_z( i );
//        const complex<double> Tsurface_cmplx = Ttransient_to_Tcplx( Tsurface ) ;
//        results[i] = Tsurface_cmplx ;
      }
      
      break;
    }

    case define::HeatX::TwoDimAnalytical:
    {
//      size_t n = 0;
//      #pragma omp parallel for schedule(dynamic) private(n)
//      for(n = 0 ; n < L_end ; n++ )
//        { results[n] = PhaseOfEmission2DAna( omegas[n], popteaCore ) ; }
      break;
    }

    case define::HeatX::OneDimNumNonLin:
      std::cout << "no model available"; exit(-2);
    case define::HeatX::TwoDimNumLin:
      std::cout << "no model available"; exit(-2);
    case define::HeatX::TwoDimNumNonLin:
      std::cout << "no model available"; exit(-2);
    default:
      std::cout << "no model available"; exit(-2);
  }

  return results;
}



}}}
