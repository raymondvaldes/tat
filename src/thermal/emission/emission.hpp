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
#ifndef EMISSION_HPP
#define EMISSION_HPP

#include <vector>
#include "thermal/simulations/Numerical_PhaseOfEmission.h"
#include "thermal/simulations/Numerical_Setup.h"
#include "thermal/define/temperature.h"

namespace thermal{
  
class Emission
{
public:
  explicit Emission( const double detector_lam_, const double T_ref_,
                     const numericalModel::Mesh mesh, const double beamR_,
                     const double E_sigma_ );
  ~Emission();
  double phase2D( std::vector< std::vector< std::vector< double > > >
                         &Temperature) const;
  double phase1D(const define::Temperature Tprofile) const;

private:
  mutable double *Ib;
  mutable double *EmissionTime;

  const double detector_lam, T_ref;
  const class numericalModel::Mesh mesh;
  const double beamR, E_sigma;

  double mean(const double x1, const double x2) const;
  double drArea(const double r0_, const double r1_) const;
  double Ib_plank(const double Temperature) const;
  double emissionAxial(std::vector<double> &Temperature) const;
  double emissionAxial(const define::Temperature Tprofile, const size_t nVal)
  const;

  double emissionAxialLinear(std::vector<double> &Temperature) const;
  double emissionVolumetric2D(std::vector<std::vector<double>>&Temperature)
  const;
};


}
#endif // EMISSION_HPP