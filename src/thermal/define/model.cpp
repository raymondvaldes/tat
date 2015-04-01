/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#include "thermal/define/model.hpp"

namespace thermal{
namespace define{

model::model ( const construct &Construct_,
               const numericalModel::Mesh &mesh_ ) noexcept
  : Construct(Construct_), mesh(mesh_)
{}
  
model::~model(void) noexcept {}

void model::reloadThermalConstruct( const construct &other_ ) noexcept
{
  Construct = other_ ;
}

  
}}
