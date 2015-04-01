/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#ifndef EMISSION_HPP
#define EMISSION_HPP

#include <vector>
#include "thermal/simulations/Numerical_PhaseOfEmission.h"
#include "thermal/model/one_dim/numerical_2011/Numerical_Setup.h"
#include "thermal/define/temperature.h"

namespace thermal{
  
class Emission
{
public:
  explicit Emission( const double detector_lam_, const double T_ref_,
                     const numericalModel::Mesh mesh, const double beamR_,
                     const double E_sigma_ ) noexcept;
  ~Emission() noexcept;
  double phase2D( std::vector< std::vector< std::vector< double > > >
                         &Temperature) const noexcept;
  double phase1D(const define::Temperature Tprofile) const noexcept;

private:
  mutable double *Ib;
  mutable double *EmissionTime;

  const double detector_lam, T_ref;
  const class numericalModel::Mesh mesh;
  const double beamR, E_sigma;

  double mean(const double x1, const double x2) const noexcept;
  double drArea(const double r0_, const double r1_) const noexcept;
  double Ib_plank(const double Temperature) const noexcept;
  double emissionAxial(std::vector<double> &Temperature) const noexcept;
  double emissionAxial(const define::Temperature Tprofile, const size_t nVal)
  const noexcept;

  double emissionAxialLinear(std::vector<double> &Temperature) const noexcept;
  double emissionVolumetric2D(std::vector<std::vector<double>>&Temperature)
  const noexcept;
};


}
#endif // EMISSION_HPP
