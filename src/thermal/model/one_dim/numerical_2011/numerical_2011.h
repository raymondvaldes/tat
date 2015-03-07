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

#ifndef __tat__numerical_2011__
#define __tat__numerical_2011__

#include <complex>
#include <iostream>
#include "thermal/model/one_dim/one_dim.h"
#include "thermal/define/temperature.h"
#include "sensible/layer.h"
#include "sensible/property.h"
#include "thermal/model/one_dim/numerical_2011/mesh.hpp"

namespace thermal{ namespace model { namespace one_dim{
  
  using std::complex;
  using std::vector;
  
class numerical_2011: protected one_dim
{
private:
  class matrixArrays
  {
    public:
    vector<double> A1, A2, A3;
    vector<double> b;
    vector<double> Temperature;
    vector<double> B1, B2, B3;

    const size_t M2;
    double B4;

    explicit matrixArrays( const size_t length ) noexcept
      : A1(length), A2(length), A3(length), b(length), Temperature(length),
      B1(length), B2(length), B3(length), B4(0), M2(length){}
  };


  double gspatial( double eta, double opt, double lambda, double R1,
                   double Iplus0, double Iplus1 ) const noexcept;
  double gs_int( const double eta, const double opt, const double lambda,
                 const double R1, const double Iplus0, const double Iplus1 ) const noexcept;
  double t_tau( const double tau, const double tau_ref ) const noexcept;
  double Iaverage( const double Is, const double It, const double omega,
                   const double tau_ref,
                   const vector<double>&tau,
                   const size_t n ) const noexcept;
  double Gaverage( const double opt, const double lambda, const double R1,
                   const double Iplus0, const double Iplus1, const double z1,
                   const double z2 ) const noexcept;
  double Iplus0Func( const double R0, const double R1, const double lambda ) const noexcept;
  double Iplus1Func( const double R0, const double R1, const double lambda ) const noexcept;
  double abMatrixPrepopulate( vector<double>& B1,
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
                              const vector<double>&d_eta_minus ) const noexcept;

  void heatingProfile( const double opt, const double lambda,
                       const double R1, const double Iplus0, const double Iplus1,
                       const vector<double>& z_jplus,
                       const vector<double>& z_jminus,
                       const vector<double>& z_j, double*genProfile,
                       const size_t M1 ) const noexcept;

  void bMatrixPrepopulate1( const size_t n, std::vector<double>& B2,
                            vector<double>& b, const size_t M1,
                            const size_t M2,
                            const vector<double>& tau,
                            const double Is, const double It, const double L_coat,
                            const double tau_ref, const double R1,
                            const double Iplus1, const double omega,
                            const vector<double>& z_jminus,
                            const vector<double>& z_j,
                            const vector<double>&deltaZ,
                            const double* genProfile,
                            const double T_rear ) const noexcept;
  
  complex<double> Tac1D_ana( const double z, const double R0, const double R1,
                             const double epsilon, const double Lam,
                             const double Lthrm ) const noexcept;
  
  void Ab_transient( const size_t n,
                     vector<double>& A1,
                     vector<double>& A2,
                     vector<double>& A3,
                     vector<double>& b, const define::Temperature Tprofile,
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
                   ) const noexcept;
  

public:
  explicit numerical_2011( const sensible::layer &coating_in,
                           const sensible::layer &substrate_in, 
                           const sensible::radiativeSysProp &radiative_prop_in,
                           const thermal::equipment::Laser &laser_in,
                           const double temp_in,
                           const double gamma_in ) noexcept;
  ~numerical_2011( void ) noexcept;
  
  void temperature_1D( const double omega1, const size_t iter,
                       const double Ttol, numericalModel::Mesh mesh,
                       thermal::define::Temperature Tprofile ) const noexcept;
  
};

  
}}}

#endif /* defined(__tat__numerical_2011__) */
