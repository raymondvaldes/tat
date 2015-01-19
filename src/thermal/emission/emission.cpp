/*----------------------------------------------------------------------------*\
  ========                |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||   	  		        |
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
#include "thermal/emission/emission.hpp"
#include "thermal/model/one_dim/numerical_2011/Numerical_Setup.h"
#include "math/utility.hpp"
#include "math/estimation/cosfit.hpp"
#include "math/numIntegration/simpsons_3_8.hpp"



namespace thermal{

  
Emission::Emission( const double detector_lam_, const double T_ref_,
                    const numericalModel::Mesh mesh_, const double beamR_,
                    const double E_sigma_)  noexcept:
                    detector_lam(detector_lam_), T_ref(T_ref_), mesh(mesh_),
                    beamR(beamR_), E_sigma(E_sigma_)
{
    Ib = new double[mesh.M1+1];
    EmissionTime = new double[mesh.Nend];
}

Emission::~Emission() noexcept
{
  delete[] Ib;
  delete[] EmissionTime;
}

double Emission::mean(const double x1, const double x2) const noexcept
{
    return (x1+x2) / 2;
}

double Emission::drArea(const double r0_, const double r1_) const noexcept
{
    /*Differential area of a radial axi-symmetric element
    The area returned is the actual area calculated from the normalized
    radial dimension and the thickness of the coating.*/
    const double r0 = r0_ * beamR;
    const double r1 = r1_ * beamR;

    return M_PI * ( r1 * r1 - r0 * r0 );
}

double Emission::Ib_plank(const double Temperature) const noexcept
{
    //Planck's law is used to describe the Planck distribution
    /*
    D1 Const in Planck's spectral energy    [W m^2 / sr]
    D2 Const in Planck's spectral energy    [m K]
    sigma   STefan Boltzmann constant   [W/(m^2 K^4)]

    See: Linear radiation model for phase of thermal emission spectrosopy
    Bennett and Yu, 2005
    Equation (6)
    */
    using std::pow;
    using std::exp;
  
    constexpr double C1     = .59552197e-16;
    constexpr double C2     = .01438769;
    constexpr double sigma  = 5.67051e-8;

    const double
    T = Temperature + T_ref;
  
    double
    Ibp = C1;
//    Ibp *= 2;
    Ibp /= pow( detector_lam , 5 ) ;
    Ibp /= exp( C2 / ( detector_lam * T ) ) - 1 ;
    Ibp /= sigma * pow( T_ref, 4 ) ; /*normalize*/

    return Ibp;
}

double Emission::emissionAxial(std::vector<double> &Temperature) const noexcept
{
  /*
  Calculates the volumetric emission flux with respect to the axial
  direction. The Temperature variable is a pointer to the axial
  temperature.
  */
  using math::numIntegration::simpson_3_8;
  
  for(size_t j = 0 ; j <= mesh.M1 ; ++j)
  {
      Ib[j] = Ib_plank( Temperature[j] );
  }

  constexpr   size_t z0 = 0;
  const       size_t z1 = mesh.M1;

  return E_sigma * Ib[z1] + 4 * simpson_3_8( Ib, mesh.z_norm, z0, z1);
}

  double Emission::emissionAxial( const define::Temperature Tprofile,
                                  const size_t nVal) const noexcept
{
    /*
    Calculates the volumetric emission flux with respect to the axial
    direction. The Temperature variable is a pointer to the axial
    temperature.
    */
  
    for(size_t j = 0 ; j <= mesh.M1 ; ++j)
    {
        Ib[j] = Ib_plank( Tprofile.eval(nVal,j) );
    }

    constexpr   size_t z0 = 0;
    const       size_t z1 = mesh.M1;

    using math::numIntegration::simpson_3_8;
    return E_sigma * Ib[z1] + 4 * simpson_3_8( Ib, mesh.z_norm, z0, z1 );
}

double Emission::emissionAxialLinear(std::vector<double> &Temperature) const noexcept
{
    /*
    Calculates the volumetric emission flux with respect to the axial
    direction. The Temperature variable is a pointer to the axial
    temperature.
    */
    for(size_t j = 0 ; j <= mesh.M1 ; ++j)
    {
        Ib[j] = Temperature[j];
    }
    const size_t z0 = 0;
    const size_t z1 = mesh.M1;

    using math::numIntegration::simpson_3_8;
    return E_sigma * Ib[z1] + 4 * simpson_3_8( Ib, mesh.z_norm, z0, z1 );
}


double Emission::emissionVolumetric2D(std::vector<std::vector<double>>&
                                      Temperature) const noexcept
{
    /*
    Calculates the volumetric emission flux with respect to the axial
    direction. Assume Temperature is of the form Tempearture[r][z].
    */
    double emission = 0;

    {
        constexpr   size_t  r = 0;
        constexpr   double  r0 = 0;
        const       double  r1 = mean(mesh.rNorm[r], mesh.rNorm[r+1]);
        emission += emissionAxial(Temperature[r]) * drArea(r0,r1);
    }

    for(size_t r = 1 ; r < mesh.Rend - 1 ; r++)
    {
        const double r0 = mean(mesh.rNorm[r], mesh.rNorm[r-1]);
        const double r1 = mean(mesh.rNorm[r], mesh.rNorm[r+1]);
        emission += emissionAxial(Temperature[r]) * drArea(r0,r1);
    }

    {
        const size_t r = mesh.Rend - 1;
        const double r0 = mean(mesh.rNorm[r], mesh.rNorm[r-1]);
        const double r1 = mesh.rNorm[r];
        emission += emissionAxial(Temperature[r]) * drArea(r0,r1);
    }
    return emission;
}

double Emission::phase2D(std::vector< std::vector<std::vector<double>>>
                                 &Temperature) const noexcept
{
    /*
    The volumetric emission is determined for one unique period of heating
    and then a cosine function is fitted.  The resulting phase is reported.
    */
    double OAPemission[3] = {1, 1, -M_PI_2};

    for (size_t n = 0 ; n < mesh.Nend ; ++n )
    {
        EmissionTime[n] = emissionVolumetric2D( Temperature[n] );
    }

    math::estimation::cosfit( EmissionTime, mesh.tau, OAPemission,
                              mesh.Nend ) ;

    return OAPemission[2];
}

  double Emission::phase1D( const define::Temperature Tprofile ) const noexcept
{
    /*
    The volumetric emission is determined for one unique period of heating
    and then a cosine function is fitted.  The resulting phase is reported.
    */
    for (size_t n = 0 ; n < mesh.Nend ; ++n )
    {
        EmissionTime[n] = emissionAxial( Tprofile, n ) ;
    }

    const double
    offsetInitial = math::average( math::arrayMax(EmissionTime, mesh.Nend),
                                   math::arrayMin(EmissionTime, mesh.Nend));
    const double
    amplitudeInitial = ( math::arrayMax(EmissionTime, mesh.Nend)
                        -math::arrayMin(EmissionTime, mesh.Nend)) / 2;

    constexpr double
    phaseInitial = -M_PI_2;

    double OAPemission[3] = {offsetInitial, amplitudeInitial, phaseInitial};

    using math::estimation::cosfit;
    cosfit( EmissionTime, mesh.tau, OAPemission, mesh.Nend ) ;

    return OAPemission[2];
}



}
