/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
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

#include "numerical_2011.h"
#include "thermal/model/utilities/heat generation/Iheat.h"
#include "thermal/model/utilities/nondimensional/tau_0.h"
#include "thermal/model/one_dim/Tss_ana.h"
#include "thermal/define/lthermal.h"
#include "math/solvers/tma.h"

namespace thermal { namespace model{ namespace one_dim{

using std::vector;
using std::complex;

numerical_2011::numerical_2011(
  const sensible::layer &coating_in,
  const sensible::layer &substrate_in,
  const sensible::radiativeSysProp &radiative_prop_in,
  const thermal::equipment::Laser &laser_in,
  const double temp_in,
  const double gamma_in )
  :
  one_dim( coating_in, substrate_in, radiative_prop_in, laser_in, temp_in,
           gamma_in )
  {}
  
numerical_2011::~numerical_2011( void ) {}


double numerical_2011::gspatial( double z, double opt, double lambda, double R1,
                                 double Iplus0, double Iplus1 ) const
{
// z must be normalized by the coating thickness
  double gs ;
  gs =  Iplus0 * exp( -z / lambda );
  gs += R1 * Iplus1 * exp( ( z - 1 ) / lambda );
  gs *= ( 1. / opt ) ;

  if( z <= 1 )
    return gs;
  else if ( z > 1 )
    return 0;

  return 0;
}


double numerical_2011::gs_int( const double eta, const double opt,
                               const double lambda, const double R1,
                               const double Iplus0, const double Iplus1 ) const
{
  using std::exp;
  
    // z must be normalized by the coating thickness
    if ( eta > 1 )
    {
      return 0;
    }
    else if( eta <= 1 )
    {
      double gs = eta;
      gs -= 1;
      gs /= lambda;
      gs = exp(gs);
      gs *= Iplus1;
      gs *= R1 ;
      gs -= Iplus0 *  exp( -eta / lambda );
      gs *= lambda;
      gs /= opt;
      return gs;
    }

    return -1;
}


double numerical_2011::t_tau( const double tau, const double tau_ref ) const
{
    return tau * tau_ref;
}

double numerical_2011::Iaverage( const double Is, const double It,
                                 const double omega, const double tau_ref,
                                 const vector<double>&tau,
                                 const size_t n ) const
{
    double I_avg;
  
    using thermal::model::Iheat_int;
  
    I_avg  = Iheat_int( Is, It, omega, t_tau( tau[n+1], tau_ref ) ) ;
    I_avg -= Iheat_int( Is, It, omega, t_tau( tau[n]  , tau_ref ) ) ;
    I_avg /= t_tau( tau[n+1], tau_ref ) - t_tau( tau[n], tau_ref )  ;

    return I_avg;
}

double numerical_2011::Gaverage( const double opt, const double lambda,
                                 const double R1, const double Iplus0,
                                 const double Iplus1, const double z1,
                                 const double z2) const
{
    double generation = gs_int( z2, opt, lambda, R1, Iplus0, Iplus1) ;
    generation -= gs_int( z1, opt, lambda, R1, Iplus0, Iplus1) ;
    generation /= z2 - z1 ;
    return generation;
}

complex<double> numerical_2011::Tac1D_ana( const double z,const double R0,
                                           const double R1,
                                           const double epsilon,
                                           const double Lam,
                                           const double Lthrm ) const
{
  using std::sinh;
  using std::cosh;
  using std::sqrt;
  using std::exp;

  constexpr   complex<double> _i_ (0.0, 1.0);
  const       complex<double> sqrtIdivL =  sqrt(_i_) / Lthrm;

  complex<double>
  F  = epsilon;
  F *= sinh( sqrtIdivL ) ;
  F += cosh( sqrtIdivL );
  F /= epsilon * cosh( sqrtIdivL ) + sinh( sqrtIdivL ) ;

  complex<double>
  H  = R0 * exp((-z-1)/Lam) + exp((z-1)/Lam);
  H *= R1;
  H *= Lam;
  H *= sqrtIdivL;
  H += (1-R0) * R1 * exp(-1/Lam) * ( F * cosh( sqrtIdivL * z)-
                                        sinh(sqrtIdivL * z ) );
  H += ( cosh( sqrtIdivL * z )
           / ( epsilon * cosh( sqrtIdivL ) + sinh( sqrtIdivL ) ) )
           * ( 2. - (1.+R1)*(1.+epsilon*sqrtIdivL*Lam)
           - (1.-R1) * ( 1.-_i_*((Lam*Lam)/(Lthrm*Lthrm) ) ) ) ;

  complex<double>
  zeta  = F;
  zeta *= cosh( sqrtIdivL * z ) ;
  zeta -= sinh( sqrtIdivL * z ) ;
  zeta /= sqrt(_i_);
  zeta -= ( Lam / Lthrm ) * exp(-z/Lam) ;
  zeta -= (H * exp( -1. / Lam )) / ( sqrt(_i_) * (1. - R0*R1* exp(-2./Lam) ) );

  complex<double>
  theta =  zeta / ( 1. - _i_ * ( (Lam * Lam) / ( Lthrm * Lthrm ) ) ) ;
  theta *=  Lthrm ;

  return theta;
}



double numerical_2011::Iplus0Func( const double R0, const double R1,
                                   const double lambda ) const
{
  using std::exp;

  double Ip0 = R0;
  Ip0 *= R1;
  Ip0 *= exp( -2 / lambda ) ;
  Ip0 /=  1 - R0 * R1 * exp( -2 / lambda )   ;
  Ip0 += 1;
  Ip0 *=  1 - R0;

  return Ip0;
}

double numerical_2011::Iplus1Func( const double R0, const double R1,
                                   const double lambda ) const
{
  using std::exp;

  double Ip1 = 1;
  Ip1 -= R0 ;
  Ip1 *= exp( -1 / lambda ) ;
  Ip1 /= 1 - R0 * R1 * exp( -2 / lambda ) ;

  return Ip1;
}

void numerical_2011::temperature_1D( const double omega1, const size_t iter,
                                     const double Ttol,
                                     numericalModel::Mesh mesh,
                                     thermal::define::Temperature Tprofile ) const
{
  using std::vector;
  using std::abs;
  using std::complex;
  
  const double lambda     = coat.Lambda;
  const double epsilon    = gamma;

  const double Is           = I_intensity_ss ;
  const double It           = I_intensity_tt ;
  
  const double q_surface = 0;
  const double R0           = 0 ;
  const double L_coat       = coat.L ;
  const double L_substrate  = sub_full.depth ;
  const double T_rear       = Temperature_interface ;
  

  const sensible::property *k1_thermal      = &coat_full.kthermal ;
  const sensible::property *k2_thermal      = &sub_full.kthermal ;
  const sensible::property *psi1_thermal    = &coat_full.psithermal ;
  const sensible::property *psi2_thermal    = &sub_full.psithermal ;

  matrixArrays *MatrixArrays = NULL;
  MatrixArrays = new class matrixArrays( mesh.M2 );

  vector< vector<double> >
  b_steady(mesh.Nend-1, vector<double>(mesh.M2));
 
  /// Setup initial conditions for the transient temperature field:
  using thermal::define::lthermal;
  const double l_thermal = lthermal(L_coat, k1_thermal->offset,
                                    psi1_thermal->offset, omega1);
  const complex<double>
  Tinfo = Tac1D_ana( mesh.z_real[0] / L_coat, R0, R1, epsilon, lambda,
                     l_thermal ) ;

  double
  amplitude_T_analytical = abs( Tinfo );
  amplitude_T_analytical *= L_coat * It * (1 - R0) ;
  amplitude_T_analytical /= k1_thermal->offset ;

  const double Iplus0 = Iplus0Func(R0, R1, lambda);
  const double Iplus1 = Iplus1Func(R0, R1, lambda);

  using thermal::model::one_dim::Tss1D_ana;
  for(size_t j=0 ; j <= mesh.M1; ++j)
  {
    Tprofile.assgn(0,j, Tss1D_ana( mesh.z_real[j] / L_coat, R1, lambda, Is,
                                   L_coat, (L_coat+L_substrate)/L_coat,
                                   k2_thermal->offset, Iplus0, Iplus1,
                                   q_surface, k1_thermal->offset) );
  }

  for (size_t j = mesh.M1+1; j < mesh.M2; j++)
  {
      Tprofile.assgn(0,j, Tss1D_ana( mesh.z_real[j] / L_coat, R1, lambda,
                                     Is,  L_coat, (L_coat+L_substrate)/L_coat,
                                     k2_thermal->offset, Iplus0, Iplus1,
                                     q_surface, k1_thermal->offset) );
  }
///Transient Solution
  /*
   Transient Solution
   Convergence criteria should be dependent on the amplitude variation of the
   transient field.  Ex. At low thermal penetrations the amplitudes will be
   very small and need a much tighter amplitude control.
  */
  {
    const double tau_ref = thermal::model::tau_0( omega1 ) ;
    MatrixArrays->B4 = abMatrixPrepopulate(MatrixArrays->B1,
                                           MatrixArrays->B2,
                                           MatrixArrays->B3, mesh.M1,
                                           MatrixArrays->M2, mesh.tau,
                                           L_coat, L_substrate, tau_ref,
                                           mesh.eta, q_surface,
                                           mesh.z_jplus,
                                           mesh.z_jminus, mesh.z_j,
                                           mesh.d_eta_plus, mesh.deltaZ,
                                           mesh.d_eta_minus);


    double *genProfile = new double[mesh.M1+1];
    const double opt = L_coat * lambda ;
    heatingProfile(opt, lambda, R1, Iplus0, Iplus1, mesh.z_jplus,
                   mesh.z_jminus, mesh.z_j, genProfile, mesh.M1);

    for (size_t n = 0 ; n < mesh.Nend-1 ; ++n )
    {
      bMatrixPrepopulate1(n, MatrixArrays->B2, b_steady[n], mesh.M1,
                          MatrixArrays->M2, mesh.tau, Is, It, L_coat,
                          tau_ref, R1, Iplus1, omega1, mesh.z_jminus,
                          mesh.z_j, mesh.deltaZ, genProfile, T_rear);
    }
    delete []genProfile;
  }
/*
  Rewrite abtransient so that it accepts two temperature arrays.  This will
  allow a quicker temperature lookup in the Ab_transient function.  Also,
  wrap these functions in
*/

  for ( size_t p = 1 ; p <= iter ; ++p )
  {
    for ( size_t n = 0 ; n < mesh.Nend-1 ; ++n )
    {
      for (size_t j = 0 ; j < mesh.M2 ; ++j )
      {
          MatrixArrays->b[j]  = b_steady[n][j];
      }

      Ab_transient( n, MatrixArrays->A1, MatrixArrays->A2,
                    MatrixArrays->A3, MatrixArrays->b, Tprofile,
                    mesh.M1, MatrixArrays->M2, MatrixArrays->B1,
                    MatrixArrays->B2, MatrixArrays->B3, MatrixArrays->B4,
                    k1_thermal, k2_thermal, psi1_thermal, psi2_thermal );

      using math::solvers::solveMatrix;
      solveMatrix( MatrixArrays->M2 , MatrixArrays->A1 , MatrixArrays->A2 ,
                   MatrixArrays->A3 , MatrixArrays->b ,
                   MatrixArrays->Temperature ) ;


      for (size_t j = 0 ; j < mesh.M2 ; ++j )
      {
        Tprofile.assgn(n+1,j, MatrixArrays->Temperature[j]);
      }
    }



      /// error will be greatest at the surface
    {
       /*Setup Convergence Criteria
       Convergence criteria should be dependent on the amplitude variation
       of the transient field.  Ex. At low thermal penetrations the
       amplitudes will be very small and need a much tighter amplitude
       control.*/
      double ss_error1 = 0;

      if (p == 0) ss_error1 = 1;

      double
      ss_error = abs( Tprofile.eval( mesh.Nend-1, 0 ) - Tprofile.eval( 0, 0 ) ) ;
      double ss_errorD = 1;

      if( p >1 )
      {
        ss_errorD = abs(ss_error - ss_error1);
        ss_errorD /= amplitude_T_analytical ;
      }

//      ss_error1 = ss_error;

      static const size_t iter_min = 3  ;
      const double TtolPercentage = Ttol * abs(amplitude_T_analytical);

      if( p >= iter_min )
      {
        if (ss_errorD < TtolPercentage)
        {
            break;
        }
        else if (ss_error < TtolPercentage)
        {
          break;
        }
        else if (p >= iter)
        {
          break;
        }
      }
    }


    for(size_t j = 0 ; j < mesh.M2; ++j)
    {
       Tprofile.assgn( 0,j, Tprofile.eval( mesh.Nend-1 , j ) );
    }
  }

  delete MatrixArrays;
}



double numerical_2011::abMatrixPrepopulate( vector<double>& B1,
                                            vector<double>& B2,
                                            vector<double>& B3,
                           const size_t M1, const size_t M2,
                           const vector<double>&tau,
                           const double L_coat, const double L_substrate,
                           const double tau_ref,
                           const vector<double>& eta,
                           const double q_surface,
                           const vector<double>& z_jplus,
                           const vector<double>& z_jminus,
                           const vector<double>& z_j,
                           const vector<double>&d_eta_plus,
                           const vector<double>&deltaZ,
                           const vector<double>&d_eta_minus) const
{
//Front Surface
    const double delEta =  eta[1] - eta[0] ;
    const double delEtaS =  eta[M1+1] - eta[M1] ;
    const double delTau =  tau[1] - tau[0] ;

    for ( size_t j = 0; j == 0; ++j )
    {
        const double delZ = z_jplus[j] - z_j[j];

        B1[j]  = 1;
        B1[j] /= 2*delTau;

        B2[j] = q_surface;
        B2[j] *= tau_ref;
        B2[j] /= L_coat * delZ;

        B3[j] = tau_ref;
        B3[j] *= d_eta_plus[j];
        B3[j] /=  2 * L_coat * L_coat * delEta * delZ  ;
     }

//Coating (interior nodes)
     for (size_t j = 1; j < M1 ; j++)
     {
        B1[j]  = L_coat * deltaZ[j]  ;
        B1[j] /= delTau * tau_ref;

        B2[j] = -d_eta_minus[j];
        B2[j] /= 2 * L_coat * delEta;

        B3[j] = d_eta_plus[j];
        B3[j] /= 2 * L_coat * delEta;
     }

// Interface at coating end
    double B4;
    {
        const size_t j = M1;
        B1[j]  = z_j[j] - z_jminus[j];
        B1[j] *= L_coat;
        B1[j] /= tau_ref * delTau;

        B2[j]  = z_jplus[j] - z_j[j];
        B2[j] *= L_substrate;
        B2[j] /= tau_ref * delTau;

        B3[j] = - d_eta_minus[j];
        B3[j] /= L_coat * 2 * (eta[j] - eta[j-1]);

        B4 = - d_eta_plus[j];
        B4 /= L_substrate * 2 * (eta[j+1] - eta[j]);
     }

//Substrate (interior nodes)
     const size_t jstart = M1+1;
     const size_t jend = M2-1;
     for ( size_t j = jstart ; j < jend ; j++ )
     {
        B1[j]  = L_substrate * deltaZ[j]  ;
        B1[j] /= delTau * tau_ref;

        B2[j] = -d_eta_minus[j];
        B2[j] /= 2 * L_substrate * delEtaS;

        B3[j] = d_eta_plus[j];
        B3[j] /= 2 * L_substrate * delEtaS;
     }

////rear boundary condition - fixed temperature
     for ( size_t j = jend ; j == jend ; j++ )
     {
        B1[j]  = 0;
        B2[j] = 0;
        B3[j] = 0;
     }
     return B4;
}

void numerical_2011::heatingProfile(const double opt, const double lambda,
                    const double R1, const double Iplus0, const double Iplus1,
                    const vector<double>& z_jplus,
                    const vector<double>& z_jminus,
                    const vector<double>& z_j, double*genProfile,
                    const size_t M1 ) const
{
    for(size_t j=0; j ==0; ++j)
        genProfile[j] = Gaverage(opt, lambda, R1, Iplus0, Iplus1, z_j[j],
                                  z_jplus[j]);
    for (size_t j = 1; j < M1 ; ++j)
    {
        genProfile[j] = Gaverage(opt, lambda, R1, Iplus0, Iplus1,
                                  z_jminus[j], z_jplus[j]);
    }
    for(size_t j=M1; j ==M1; ++j)
        genProfile[j] = Gaverage(opt, lambda, R1, Iplus0, Iplus1,
                                  z_jminus[j], z_j[j]);

    return;
}

void numerical_2011::bMatrixPrepopulate1(const size_t n, vector<double>& B2,
                         vector<double>& b, const size_t M1,
                         const size_t M2,
                         const vector<double>& tau,
                         const double Is, const double It, const double L_coat,
                         const double tau_ref, const double R1,
                         const double Iplus1, const double omega,
                         const vector<double>& z_jminus,
                         const vector<double>& z_j,
                         const vector<double>&deltaZ,
                         const double* genProfile, const double T_rear) const
{
//Update A matrix based on temperature an time
    const double I_avg  = Iaverage(Is, It, omega, tau_ref, tau, n);
    double *QgenAverage = new double[M2];

    for(size_t j=0 ; j <= M1 ; ++j)
        QgenAverage[j] = I_avg * genProfile[j] ;

//Front Surface
    for ( size_t j = 0; j == 0; ++j )
    {
        b[j] = QgenAverage[j];
        b[j] *= tau_ref;
        b[j] += B2[j];

    }

//Coating (interior nodes)
    for (size_t j = 1; j < M1 ; j++)
    {
        b[j] = QgenAverage[j];
        b[j] *= deltaZ[j];
        b[j] *= L_coat;
    }

// Interface at coating end
    const double q_abs = I_avg * (1 - R1) * Iplus1;
    for (size_t j = M1; j == M1; j ++) //Interface
    {
        b[j] =  z_j[j];
        b[j] -= z_jminus[j];
        b[j] *= QgenAverage[j];
        b[j] *=L_coat;
        b[j] +=q_abs;

    }

//Substrate (interior nodes)
    const size_t jstart = M1+1;
    const size_t jend = M2-1;
    for ( size_t j = jstart ; j <= jend ; j++ )
    {
        b[j] = T_rear;
    }

    delete []QgenAverage;

    return;
}

void numerical_2011::Ab_transient( const size_t n,
                                   vector<double>& A1,
                                   vector<double>& A2,
                                   vector<double>& A3,
                                   vector<double>& b,
                                   const define::Temperature Tprofile,
                                   const size_t M1,
                                   const size_t M2,
                                   const vector<double>& B1,
                                   const vector<double>& B2,
                                   const vector<double>& B3,
                                   const double B4,
                                   const sensible::property *kLayer1,
                                   const sensible::property *kLayer2,
                                   const sensible::property *psiLayer1,
                                   const sensible::property *psiLayer2
                                  ) const
{
///Update A matrix based on temperature and time
///Front Surface
    {
        const size_t j = 0;
        A1[j] = 0;

        A2[j]  = psiLayer1->Projected(Tprofile,n,j) ;
        A2[j] += psiLayer1->Current(Tprofile,n,j)  ;
        A2[j] *= B1[j] ;
        A2[j] += B3[j] * kLayer1->Projected(Tprofile,n,j,j+1)  ;

        A3[j]  = -B3[j];
        A3[j] *= kLayer1->Projected(Tprofile,n,j,j+1);

        b[j] += kLayer1->Current(Tprofile,n,j,j+1) * (Tprofile.eval(n,j+1) -
                                               Tprofile.eval(n,j)) * B3[j];
        b[j] += B1[j] * (psiLayer1->Projected(Tprofile,n,j) +
                         psiLayer1->Current(Tprofile,n,j) ) * Tprofile.eval(n,j);
    }

///Coating (interior nodes)
     for (size_t j = 1; j < M1 ; ++j)
     {
        const double B1j = B1[j];
        const double psi1projTnnjp  = psiLayer1->Projectedt(Tprofile,n,n+1,j);

        const double B2j = B2[j];
        const double k1projTnjjm    = kLayer1->Projected(Tprofile,n,j,j-1);


        const double B3j = B3[j];
        const double k1projTnjjp    = kLayer1->Projected(Tprofile,n,j,j+1);

        double
        A3j  = B3j;
        A3j *= k1projTnjjp ;
        A3j *= -1;

        double
        A2j  = B1j;
        A2j*= psi1projTnnjp ;
        A2j -= B2j * k1projTnjjm ;
        A2j += B3j * k1projTnjjp ;

        double
        A1j = B2j;
        A1j *= k1projTnjjm ;

        A1[j] = A1j;
        A2[j] = A2j;
        A3[j] = A3j;
     }

     for (size_t j = 1; j < M1 ; ++j)
     {
        const double B1j = B1[j];
        const double psi1projTnnjp  = psiLayer1->Projectedt(Tprofile,n,n+1,j);

        const double B2j = B2[j];
        const double k1currjTnjjm   = kLayer1->Current(Tprofile,n,j,j-1);

        const double B3j = B3[j];
        const double k1currjTnjjp   = kLayer1->Current(Tprofile,n,j,j+1);

        double
        bj = -1;
        bj *=  B2j;
        bj *= k1currjTnjjm;
        bj *= Tprofile.eval(n,j-1);
        bj += (
                   B1j * psi1projTnnjp
                 + B2j * k1currjTnjjm
                 - B3j * k1currjTnjjp
              ) * Tprofile.eval(n,j) ;
        bj += B3j * k1currjTnjjp * Tprofile.eval(n,j+1) ;

        b[j] += bj;
     }


/// Interface at coating end
     for (size_t j = M1; j == M1; j++) //Interface
     {
         A1[j] =  B3[j]  * kLayer1->Projected(Tprofile,n,j,j-1);

         A2[j] =  B1[j] * psiLayer1->Projectedt(Tprofile,n,n+1,j);
         A2[j] += B2[j] * psiLayer2->Projectedt(Tprofile,n,n+1,j);
         A2[j] -= B3[j] * kLayer1->Projected(Tprofile,n,j,j-1);
         A2[j] -= B4 * kLayer2->Projected(Tprofile,n,j,j+1);

         A3[j]  = B4 * kLayer2->Projected(Tprofile,n,j,j+1);

         b[j] += ( B1[j] * psiLayer1->Projectedt(Tprofile,n,n+1,j)
               +  B2[j] * psiLayer2->Projectedt(Tprofile,n,n+1,j)) * Tprofile.eval(n,j);
         b[j] += B3[j] * kLayer1->Current(Tprofile,n,j,j-1) * (Tprofile.eval(n,j) -
                                                        Tprofile.eval(n,j-1));
         b[j] -= B4 * kLayer2->Current(Tprofile,n,j,j+1) * (Tprofile.eval(n,j+1) -
                                                     Tprofile.eval(n,j));
     }

///Substrate (interior nodes)
     const size_t jstart = M1+1;
     const size_t jend = M2-1;
     for ( size_t j = jstart ; j < jend ; ++j )
     {
        const double B1j = B1[j];
        const double psi2projTnnjp  = psiLayer2->Projectedt(Tprofile,n,n+1,j);

        const double B2j = B2[j];
        const double k2projTnjjm    = kLayer2->Projected(Tprofile,n,j,j-1);

        const double B3j = B3[j];
        const double k2projTnjjp    = kLayer2->Projected(Tprofile,n,j,j+1);

        double
        A1j  = B2j ;
        A1j *= k2projTnjjm ;

        double
        A2j  = B1j ;
        A2j  *= psi2projTnnjp ;
        A2j -= B2j * k2projTnjjm ;
        A2j += B3j * k2projTnjjp ;

        double
        A3j = B3j ;
        A3j *= -1;
        A3j *= k2projTnjjp ;

        A1[j] = A1j;
        A2[j] = A2j;
        A3[j] = A3j;

     }

     for ( size_t j = jstart ; j < jend ; ++j )
     {
        const double B1j = B1[j];
        const double psi2projTnnjp  = psiLayer2->Projectedt(Tprofile,n,n+1,j);

        const double B2j = B2[j];
        const double k2currjTnjjm   = kLayer2->Current(Tprofile,n,j,j-1);

        const double B3j = B3[j];
        const double k2currjTnjjp   = kLayer2->Current(Tprofile,n,j,j+1);

        double
        temp = B1j;
        temp *= psi2projTnnjp;
        temp += B2j * k2currjTnjjm;
        temp -= B3j * k2currjTnjjp;
        temp *= Tprofile.eval(n,j);

        double
        bj =  -1;
        bj *= B2j;
        bj *= k2currjTnjjm;
        bj *= Tprofile.eval(n,j-1);
        bj += temp ;
        bj += B3j * k2currjTnjjp * Tprofile.eval(n,j+1) ;


        b[j] += bj;

     }

///rear boundary condition - fixed temperature
///Change so that Kappa(ref), Psi_non(ref) = 1;
     {
        const size_t j = jend;
        A1[j] = 0 ;
        A2[j] = 1 ;
        A3[j] = 0;
     }

     return;
}


}}}