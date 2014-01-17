/*----------------------------------------------------------------------------*\
  ========                      |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||   	  		|
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
#include <cassert>
#include <cmath>
#include "models/numericalmodel.hpp"
#include "algorithms/statistical_tools.hpp"
#include "numSimulations/Numerical_Setup.h"

namespace numericalModel
{
Mesh::Mesh(const size_t M2_, const size_t Rend_, const size_t Nend_,
           const double beta1_, const double split_, const double L_coat_,
           const double L_substrate_, const double CO2Radius_,
           const double Rdomain_)
           :M2(M2_), Rend(Rend_), Nend(Nend_), beta1(beta1_), split(split_)
{
  assert( (M2-1) %5 == 0);     // (M2-1 / 5) must be integer!! (assert)

  time.resize(Nend);
  tau.resize(Nend);

  eta.resize(M2);
  z_real.resize(M2);
  z_norm.resize(M2);
  zNorm2.resize(M2);
  d_eta_plus.resize(M2);
  deltaZ.resize(M2);
  d_eta_minus.resize(M2);

  rNorm2.resize(Rend);
  rNorm.resize(Rend);
  rZeta.resize(Rend);
  rReal.resize(Rend);

  z_jplus.resize(M2);
  z_jminus.resize(M2);
  z_j.resize(M2);

  for (size_t i = 0; i < Nend; ++i)
  {
    tau[i]  = double(i)/(Nend-1);
  }

  for (size_t i = 0; i < Rend; ++i)
  {
    rZeta[i] = double(i)/(Rend-1);
  }

  meshUpdate(L_coat_, L_substrate_, CO2Radius_, Rdomain_);
}

Mesh::~Mesh()
{
}

double Mesh::beta2_func(const double *variable, const double *constants)
{
  std::vector<double> eta_(int(constants[1]), 0);

  constexpr double L1 = 1; //coating nondimensional thickness
                           //z transformed to eta from 0-L_coat  to 0-1.
  constexpr double L2 = 1; //substrate ....Do not change these parameters.

  const size_t M1_ = constants[4] * ( constants[1] - 1 );

  for(size_t j = 0; j <= M1_ ; j++)
  {
      eta_[j] = L1 *  double (j) / double (M1_);
  }

  for(size_t j = 1 ; j < constants[1] - M1_ ; j ++)
  {
      eta_[M1_+j] = ( double ( j ) /
                      ( double( constants[1] - 1 ) - double( M1_ ) ) )
       * L2 + eta_[M1_];
  }


  const double
  a = ( z_eta(eta_[M1_+1], constants[0], variable[0]) - 1 ) * constants[2] +
  constants[3];

  const double
  b = z_eta(eta_[M1_], constants[0], variable[0]) * constants[3];

  const double
  c = z_eta(eta_[M1_-1], constants[0], variable[0]) * constants[3];

  const double
  d = std::abs( ( a - b ) - ( b - c ) );

  return  d  ;
}

void Mesh::minimizer(double *variable, double *constants,
                     double temp_variable_min, double temp_variable_max,
                     double min_goal, const size_t max_iterations)
{
  double fraction = 0;
  //    double *temp_to_minimize = new double [max_iterations];

  size_t while_j=0;
  int best_minimum_element = 0;
  variable[0] = temp_variable_min;
  //    temp_to_minimize[best_minimum_element] = min_goal*10;

  std::vector<double> temp_to_minimize;
  temp_to_minimize.resize(max_iterations+1);
  temp_to_minimize[best_minimum_element] = min_goal*10;


  while(temp_to_minimize[best_minimum_element]>=min_goal &&
        while_j<max_iterations)
  {
    fraction = pow(10,-1*double (while_j));
    variable[0] = temp_variable_min+fraction;
    temp_to_minimize[0] = beta2_func(variable,constants);

    for(size_t for_j=1 ; for_j <= max_iterations ; for_j++ )
    {
      variable[0]+=fraction;
      temp_to_minimize[for_j]= beta2_func(variable,constants);

      if(
         fabs(temp_to_minimize[for_j]) >=
         fabs(temp_to_minimize[for_j-1])
         ||
         variable[0] >   temp_variable_max)
      {
        variable[0]-=fraction;
        best_minimum_element=for_j-1;
        break;
      }
    }
      while_j+=1;

  }
  variable[0]+=fraction;
  temp_to_minimize[best_minimum_element+1]= beta2_func(variable,constants);
  variable[0]-=fraction;

  return;
}

double Mesh::find_beta2(const double L_coat, const double L_substrate)
{
  ////minimizer start (to find beta2)
  constexpr size_t beta_iter = {100};
  constexpr double beta_tol  = {1e-6};
  double variable;
  double constants[5] = {beta1, double(M2), L_substrate, L_coat, split};

  minimizer(&variable, constants, 1.001, 15., beta_tol, beta_iter);


  return variable;
}

size_t Mesh::discretizeSpace(const double L_coat, const double L_substrate)
{
  constexpr double L1 = 1; //coating nondimensional thickness
                           //z transformed to eta from 0-L_coat  to 0-1.
  constexpr double L2 = 1; //substrate ....Do not change these parameters.

  const size_t M1_ = split * (M2-1);

// define eta (computational grid)
  for(size_t j = 0; j <= M1_ ; j++)
  {
    eta[j] =  double (j) / M1_ * L1;
  }

  for(size_t j = 1 ; j <= (M2-1) - M1_ ; j ++)
  {
    eta[M1_+j] = ( double ( j ) / (M2-1 -M1_ ) ) * L2;
    eta[M1_+j] += eta[M1_];
  }

  for ( size_t j = 0 ; j < M2; j++ )
  {
    z_norm[j] = z_eta( eta[j], beta1,  beta2) ;

    if ( j <= M1_)
    {
      z_real[j] = z_norm[j] * L_coat;
    }
    else if ( j > M1_ && j < M2)
    {
      z_real[j] = (z_norm[j] - 1) * L_substrate + L_coat;
    }

    if(j <= M1_)
    {
      zNorm2[j] = z_norm[j];
    }
    else if(j > M1_)
    {
      zNorm2[j] = (L_substrate/L_coat) * ( z_norm[j] - 1 ) + 1;
    }
  }


  return M1_;
}

double Mesh::z_eta(const double eta_)
{
  return z_eta(eta_, beta1, beta2);
}

double Mesh::z_eta(const double eta_, const double beta1_, const double beta2_)
{
  /* z_norm accounts for z_real after it has been normalized by L_coat
      and L_substrat double B;*/
  if (equalto(eta_,0))
  {
    return eta_;
  }

  else if (equalto(eta_,1))
  {
    return eta_;
  }

  else if (eta_ < 1)
  {
    const double B = ( beta1_ + 1) / (beta1_ - 1) ;
    return 1 + beta1_ - ( 2 * B * beta1_ ) / ( B + pow( B , eta_ ) ) ;
  }

  else if (eta_ > 1)
  {
    const double B = ( beta2_ + 1) / ( beta2_ - 1) ;
    return 2 + beta2_ - (2 * B * B * beta2_) / (B * B + pow( B , eta_));
  }

  return -1;
}

double Mesh::D_eta(const double z_norm_)
{
  //z_norm accounts for z_real after it has been normalized by
  //L_coat and L_substrate

  if (z_norm_ < 1 || equalto(z_norm_, 1))
  {
    const double B = ( beta1 + 1) / ( beta1 - 1) ;
    return ( -2 * beta1 ) /
    ( ( ( (-1 + z_norm_)*(-1 +z_norm_)) -(beta1*beta1) ) * ( log( B) ) ) ;
  }

  else if (z_norm_ > 1)
  {
    const double B = ( beta2 + 1) / ( beta2 - 1) ;
    return ( -2 * beta2 ) /
    ( ( ((-2 + z_norm_)*(-2 + z_norm_)) - (beta2*beta2) ) * ( log( B ) ) ) ;
  }

  return -1;
}

void Mesh::zUpdate()
{
  /*
  Attempted to autovectorize the for loop but was unable due to the
  conditional statements in the z_eta function. Splitting the loop into
  three loops did not help.
  */
  z_jplus[0] = z_eta( ::average(eta[1], eta[0]));
      z_j[0] = z_eta( eta[0]);

  const size_t endM2 = M2-1;
  for (size_t j = 1; j < endM2; j++)
  {
    z_jplus[j] = z_eta( ::average(eta[j+1], eta[j]) );
    z_jminus[j] = z_eta( ::average(eta[j-1], eta[j]) );
    z_j[j] =  z_eta( eta[j]);
  }

  z_jminus[M2-1] = z_eta( ::average(eta[M2-2], eta[M2-1]) );
       z_j[M2-1] = z_eta( eta[M2-1]);


  for(size_t j = 0; j==0; j++)
    d_eta_plus[j]  = D_eta( z_jplus[j] );
  for (size_t j = 1; j < M2-1 ; ++j)
  {
    d_eta_minus[j] = D_eta( z_jminus[j]);
    d_eta_plus[j]  = D_eta( z_jplus[j]);
    deltaZ[j] = z_jplus[j] - z_jminus[j];
  }

  {
    const size_t j = M2-1;
    d_eta_minus[j] = D_eta( z_jminus[j]);
    d_eta_plus[j]  = D_eta( z_j[j] ) ;
  }

  return;
}

void Mesh::meshUpdate(const double L_coat, const double L_substrate,
                      const double CO2Radius, const double Rdomain)
{
  beta2 = find_beta2(L_substrate, L_coat);
  M1 = discretizeSpace(L_coat, L_substrate);

  for (size_t i = 0; i < Rend; ++i)
  {
    rNorm[i] = rZeta[i] * ( Rdomain / CO2Radius ) ;
    rReal[i] = rNorm[i] * CO2Radius;
  }

  zUpdate();
}


simulations::simulations(void){}


}

