#include "../Header.h"

void temperature_1D(const double lambda,
                    const double R1, const double q_surface,
                    const size_t iter, const double omega1,
                    const double epsilon,
                    class Mesh *mesh, class Temperature Tprofile,
                    class expEquipment::Laser laser,
                    struct physicalModel::TBCsystem TBCsystem)
{
  const double Is           = laser.Is;
  const double It           = laser.It;
  const double R0           = TBCsystem.optical.R0;
  const double L_coat       = TBCsystem.coating.depth;
  const double L_substrate  = TBCsystem.substrate.depth;
  const double Ttol         = TBCsystem.Temp.tolerance;
  const double T_rear       = TBCsystem.Temp.rear;
  const class property *k1_thermal      = &TBCsystem.coating.kthermal;
  const class property *k2_thermal      = &TBCsystem.substrate.kthermal;
  const class property *psi1_thermal    = &TBCsystem.coating.psithermal;
  const class property *psi2_thermal    = &TBCsystem.substrate.psithermal;

  class matrixArrays *MatrixArrays = NULL;
  MatrixArrays = new class matrixArrays(mesh->M2);

  std::vector< std::vector<double> >
  b_steady(mesh->Nend-1, std::vector<double>(mesh->M2));

/// Setup initial conditions for the transient temperature field:
  const double l_thermal = lthermal(L_coat, k1_thermal->offset,
                                    psi1_thermal->offset, omega1);
  const std::complex<double>
  Tinfo = Tac1D_ana(mesh->z_real[0] / L_coat, R0, R1, epsilon,
                    lambda, l_thermal);

  double
  amplitude_T_analytical = fabs ( Tinfo );
  amplitude_T_analytical *= L_coat * It * (1 - R0) ;
  amplitude_T_analytical /= k1_thermal->offset ;

  const double Iplus0 = Iplus0Func(R0, R1, lambda);
  const double Iplus1 = Iplus1Func(R0, R1, lambda);

  for(size_t j=0 ; j <= mesh->M1; ++j)
  {
    Tprofile.assgn(0,j, Tss1D_ana(mesh->z_real[j] / L_coat, R1, lambda, Is,
                                  L_coat, (L_coat+L_substrate)/L_coat,
                                  k2_thermal->offset, Iplus0, Iplus1,
                                  q_surface, k1_thermal->offset));
  }

  for (size_t j = mesh->M1+1; j < mesh->M2; j++)
  {
      Tprofile.assgn(0,j, Tss1D_ana( mesh->z_real[j] / L_coat, R1, lambda,
                                    Is,  L_coat, (L_coat+L_substrate)/L_coat,
                                    k2_thermal->offset, Iplus0, Iplus1,
                                    q_surface, k1_thermal->offset));
  }

///Transient Solution
  /*
   Transient Solution
   Convergence criteria should be dependent on the amplitude variation of the
   transient field.  Ex. At low thermal penetrations the amplitudes will be
   very small and need a much tighter amplitude control.
  */
  {
    const double tau_ref = tau_0(omega1);
    MatrixArrays->B4 = abMatrixPrepopulate(MatrixArrays->B1,
                                           MatrixArrays->B2,
                                           MatrixArrays->B3, mesh->M1,
                                           MatrixArrays->M2, mesh->tau,
                                           L_coat, L_substrate, tau_ref,
                                           mesh->eta, q_surface,
                                           mesh->z_jplus,
                                           mesh->z_jminus, mesh->z_j,
                                           mesh->d_eta_plus, mesh->deltaZ,
                                           mesh->d_eta_minus);


    double *genProfile = new double[mesh->M1+1];
    const double opt = L_coat * lambda ;
    heatingProfile(opt, lambda, R1, Iplus0, Iplus1, mesh->z_jplus,
                   mesh->z_jminus, mesh->z_j, genProfile, mesh->M1);

    for (size_t n = 0 ; n < mesh->Nend-1 ; ++n )
    {
      bMatrixPrepopulate1(n, MatrixArrays->B2, b_steady[n], mesh->M1,
                          MatrixArrays->M2, mesh->tau, Is, It, L_coat,
                          tau_ref, R1, Iplus1, omega1, mesh->z_jminus,
                          mesh->z_j, mesh->deltaZ, genProfile, T_rear);
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
    for ( size_t n = 0 ; n < mesh->Nend-1 ; ++n )
    {
      for (size_t j = 0 ; j < mesh->M2 ; ++j )
      {
          MatrixArrays->b[j]  = b_steady[n][j];
      }

      Ab_transient(n, MatrixArrays->A1, MatrixArrays->A2,
                   MatrixArrays->A3, MatrixArrays->b, Tprofile,
                   mesh->M1, MatrixArrays->M2, MatrixArrays->B1,
                   MatrixArrays->B2, MatrixArrays->B3, MatrixArrays->B4,
                   k1_thermal, k2_thermal, psi1_thermal, psi2_thermal);

      solveMatrix(MatrixArrays->M2 , MatrixArrays->A1 , MatrixArrays->A2 ,
                  MatrixArrays->A3 , MatrixArrays->b ,
                  MatrixArrays->Temperature);


      for (size_t j = 0 ; j < mesh->M2 ; ++j )
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
      ss_error = fabs(Tprofile.eval(mesh->Nend-1, 0) -
                      Tprofile.eval(0, 0));
      double ss_errorD = 1;

      if( p >1 )
      {
        ss_errorD = fabs(ss_error - ss_error1);
        ss_errorD /= amplitude_T_analytical ;
      }

      ss_error1 = ss_error;

      static const size_t iter_min = 3  ;
      const double TtolPercentage = Ttol *fabs(amplitude_T_analytical);

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


    for(size_t j = 0 ; j < mesh->M2; ++j)
    {
       Tprofile.assgn(0,j, Tprofile.eval(mesh->Nend-1,j) );
    }
  }
  delete MatrixArrays;

  return;
}



double abMatrixPrepopulate(std::vector<double>& B1,
                           std::vector<double>& B2,
                           std::vector<double>& B3,
                           const size_t M1, const size_t M2,
                           const double * __restrict__ tau,
                           const double L_coat, const double L_substrate,
                           const double tau_ref,
                           const double * __restrict__ eta,
                           const double q_surface,
                           const std::vector<double>& z_jplus,
                           const std::vector<double>& z_jminus,
                           const std::vector<double>& z_j,
                           const double*d_eta_plus,
                           const double*deltaZ,
                           const double*d_eta_minus)
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

void heatingProfile(const double opt, const double lambda,
                    const double R1, const double Iplus0, const double Iplus1,
                    const std::vector<double>& z_jplus,
                    const std::vector<double>& z_jminus,
                    const std::vector<double>& z_j, double*genProfile,
                    const size_t M1 )
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

void bMatrixPrepopulate1(const size_t n, std::vector<double>& B2,
                         std::vector<double>& b, const size_t M1,
                         const size_t M2, const double * __restrict__ tau,
                         const double Is, const double It, const double L_coat,
                         const double tau_ref, const double R1,
                         const double Iplus1, const double omega,
                         const std::vector<double>& z_jminus,
                         const std::vector<double>& z_j, const double*deltaZ,
                         const double* genProfile, const double T_rear)
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

void Ab_transient(const size_t n,
                  std::vector<double>& A1,
                  std::vector<double>& A2,
                  std::vector<double>& A3,
                  std::vector<double>& b, const class Temperature Tprofile,
//                  const std::vector<std::vector<double>>& T,
                  const size_t M1,
                  const size_t M2,
                  const std::vector<double>& B1,
                  const std::vector<double>& B2,
                  const std::vector<double>& B3,
                  const double B4,
                  const class property *kLayer1,
                  const class property *kLayer2,
                  const class property *psiLayer1,
                  const class property *psiLayer2
                  )
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

std::complex<double> Tac1D_ana(const double z,const double R0,const double R1,
                               const double epsilon, const double Lam,
                               const double Lthrm)
{
    constexpr   std::complex<double> _i_ (0.0, 1.0);
    const       std::complex<double> sqrtIdivL =  sqrt(_i_) / Lthrm;

    std::complex<double>
    F  = epsilon;
    F *= sinh( sqrtIdivL ) ;
    F += cosh( sqrtIdivL );
    F /= epsilon * cosh( sqrtIdivL ) + sinh( sqrtIdivL ) ;

    std::complex<double>
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

    std::complex<double>
    zeta  = F;
    zeta *= cosh( sqrtIdivL * z ) ;
    zeta -= sinh( sqrtIdivL * z ) ;
    zeta /= sqrt(_i_);
    zeta -= ( Lam / Lthrm ) * exp(-z/Lam) ;
    zeta -= (H * exp( -1. / Lam )) / ( sqrt(_i_) * (1. - R0*R1* exp(-2./Lam) ) );

    std::complex<double>
    theta =  zeta / ( 1. - _i_ * ( (Lam * Lam) / ( Lthrm * Lthrm ) ) ) ;
    theta *=  Lthrm ;

    return theta;
}

double Tss1D_ana(const double z, const double R1, const double lambda,
                 const double Is, const double L, const double d,
                 const double k_ref, const double Iplus0, const double Iplus1,
                 const double q_surface, const double k_c)
{
    /* This is the steady state 1d analytical solution to volumetric heat
    absorption in a two-layer system.  The front surface is maintained with
    an adiabatic boundary and the rear surface is held at a constant reference
    temperature of zero.*/
    double Tss = 0;

    const double
    C0 = Is * L  / ( lambda * k_c ) ;

    const double
    Clam = exp( -1 / lambda );

    double
    C1  = C0 ;
    C1 *= -Iplus0 * lambda + R1 * Iplus1 * lambda * Clam;
    C1 -= q_surface / (k_c / k_ref);

    double
    C3  = k_c / k_ref;
    C3 *= -C0 * ( - Iplus0 * lambda * Clam + R1 * Iplus1 * lambda ) + C1 ;
    C3 += ( ( -1 + R1 ) * Is * Iplus1 * L ) /   k_ref  ;

    double
    C4 = - C3 * d;

    double
    C2 =  C0 ;
    C2 *= lambda * lambda * Iplus0 * Clam + R1 * Iplus1 * lambda * lambda ;
    C2 += C4 + C3 - C1;

    if ( z<=1 )
    {
        Tss = -C0;
        Tss *= Iplus0 * lambda * lambda * exp( -z / lambda ) + R1 * Iplus1 *
               lambda * lambda * exp( ( z - 1 ) / lambda ) ;
        Tss += C1 * z;
        Tss += C2;
    }
    else if (z > 1)
    {
        Tss = C3 * z + C4 ;
    }
    return Tss;
}

double t_tau(const double tau, const double tau_ref)
{
    return tau * tau_ref;
}

double Iaverage(const double Is, const double It, const double omega,
                        const double tau_ref, const double *tau, const size_t n)
{
    double I_avg;
    I_avg  = Iheat_int( Is,It,omega, t_tau(tau[n+1], tau_ref) ) ;
    I_avg -= Iheat_int( Is,It,omega, t_tau(tau[n]  , tau_ref) ) ;
    I_avg /= t_tau(tau[n+1], tau_ref) - t_tau(tau[n], tau_ref)  ;

    return I_avg;
}

double Gaverage(const double opt, const double lambda, const double R1,
                const double Iplus0, const double Iplus1, const double z1,
                const double z2)
{
    double generation = gs_int( z2, opt, lambda, R1, Iplus0, Iplus1) ;
    generation -= gs_int( z1, opt, lambda, R1, Iplus0, Iplus1) ;
    generation /= z2 - z1 ;
    return generation;
}


double qGenAverage(const double I_avg, const double opt, const double lambda, const double R1, const double Iplus0,
                   const double Iplus1, const double z1, const double z2)
{
    double q_gen;
    q_gen  = gs_int( z2, opt, lambda, R1, Iplus0, Iplus1) ;
    q_gen -= gs_int( z1, opt, lambda, R1, Iplus0, Iplus1) ;
    q_gen /= z2 - z1 ;
    q_gen *= I_avg;

    return q_gen;
}

double z_eta(const double eta, const double beta1, const double beta2)
{
/*
!flag!!!!  Is there an error in beta?
    z_norm accounts for z_real after it has been normalized by L_coat and
    L_substrat double B;
 */
//    SETUP TO RETURN ETA IF BETA1 and BETA2 ABOVE CRITICAL VALUE;

    if (equalto(eta, 0))
    {
        return eta;
    }

    else if (equalto(eta, 1))
    {
        return eta;
    }

    else if (eta < 1)
    {
        const double B = ( beta1 + 1) / (beta1 - 1) ;
        return 1 + beta1 - ( 2 * B * beta1 ) / ( B + pow( B , eta ) ) ;
    }

    else if (eta > 1)
    {
        const double B = ( beta2 + 1) / ( beta2 - 1) ;
        return 2 + beta2 - ( 2 * B * B * beta2 ) / ( B * B + pow( B , eta ) ) ;
    }

    return -1;
}

double D_eta(const double z_norm, const double beta1)
{
    //z_norm accounts for z_real after it has been normalized by L_coat
    //and L_substrate
    //disable with beta greater than 7;
//    if(beta1 > 7)
//        return 0;

    if (z_norm <= 1)
    {
        const double B = ( beta1 + 1) / ( beta1 - 1) ;
        return ( -2 * beta1 ) /
        ( ( ( (-1 + z_norm)*(-1 + z_norm)) -(beta1*beta1) ) * ( log( B ) ) ) ;
    }
    else if (z_norm > 1)
    {
        return -1;
    }

    return -1;
}

double D_xi(const double z_norm, const double beta1)
{
    return D_eta(z_norm, beta1);
}

double D_eta(const double z_norm, const double beta1, const double beta2)
{
    //z_norm accounts for z_real after it has been normalized by
    //L_coat and L_substrate

    if (z_norm <= 1)
    {
//      if(beta1 > 5) return 0;
        const double B = ( beta1 + 1) / ( beta1 - 1) ;
        return ( -2 * beta1 ) /
        ( ( ( (-1 + z_norm)*(-1 + z_norm)) -(beta1*beta1) ) * ( log( B ) ) ) ;
    }
    else if (z_norm > 1)
    {
//      if(beta2 > 5) return 0;
        const double B = ( beta2 + 1) / ( beta2 - 1) ;
        return ( -2 * beta2 ) /
        ( ( ((-2 + z_norm)*(-2 + z_norm)) - (beta2*beta2) ) * ( log( B ) ) ) ;
    }

    return -1;
}

//Functions  for stretching
double eta_z(const double z,const double beta1,const double beta2)
{
    double A,B,beta;
    double eta1 = 0;
    //z_norm accounts for z_real after it has been normalized by L_coat and
    //L_substrate

    if (z <= 1)
    {
        beta = beta1;
        A = ( beta + ( 1. - z  ) )
          / ( beta - ( 1. - z  ) ) ;
        B = ( beta + 1.) / ( beta - 1.) ;
        eta1 = 1. - log(A)/log(B);
    }
    else if (z > 1)
    {
        beta = beta2;
        A  = ( beta + ( 2. - z ) ) ;
        A /= ( beta - ( 2. - z ) ) ;

        B = ( beta + 1.) / ( beta - 1.) ;
        eta1 = 2. - log(A)/log(B) ;
    }
    return eta1;
}

double r_xi(const double xi, const double beta)
{
    //z_norm accounts for z_real after it has been normalized by
    //L_coat and L_substrat
//    double B;
    if (equalto(xi,0))
    {
        return xi;
    }
    else if (equalto(xi,1))
    {
        return xi;
    }
    else if (xi < 1)
    {
        const double B = ( beta + 1) / (beta - 1) ;
        return 1 + beta - ( 2 * B * beta ) / ( B + pow( B , xi ) ) ;
    }



    return -1;
}

double Iplus0Func(const double R0, const double R1, const double lambda)
{
    double Ip0 = R0;
    Ip0 *= R1;
    Ip0 *= exp( -2 / lambda ) ;
    Ip0 /=  1 - R0 * R1 * exp( -2 / lambda )   ;
    Ip0 += 1;
    Ip0 *=  1 - R0;

    return Ip0;
}

double Iplus1Func(const double R0, const double R1, const double lambda)
{
    double Ip1 = 1;
    Ip1 -= R0 ;
    Ip1 *= exp( -1 / lambda ) ;
    Ip1 /= 1 - R0 * R1 * exp( -2 / lambda ) ;

    return Ip1;
}
