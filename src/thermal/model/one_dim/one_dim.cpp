/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#include "thermal/model/one_dim/one_dim.h"

namespace thermal{ namespace model {namespace one_dim{

one_dim::one_dim(
  const sensible::layer &coating_in,
  const sensible::layer &substrate_in,
  const sensible::radiativeSysProp &radiative_prop_in,
  const thermal::equipment::Laser &laser_in,
  const double temp_in,
  const double gamma_in ) noexcept
  :
  coat( coating_in.kthermal.offset, coating_in.psithermal.offset,
        coating_in.getDepth(), coating_in.getLambda() ),
  coat_full( coating_in ),
  sub_full( substrate_in ), 
  I_intensity_ss(             laser_in.Is ),
  I_intensity_tt(             laser_in.It ),
  Temperature_interface(      temp_in ),
  gamma(                      gamma_in ),
  R1(                         radiative_prop_in.R1 ),
  Emit1(                      radiative_prop_in.Emit1 )
{}
  
one_dim::~one_dim( void ) noexcept {}

}}}
