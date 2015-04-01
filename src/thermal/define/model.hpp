/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#ifndef __TAT__MODEL_HPP
#define __TAT__MODEL_HPP

#include "thermal/define/construct.hpp"
#include "thermal/model/one_dim/numerical_2011/mesh.hpp"

namespace thermal{
namespace define{

class model
{
public:
  construct Construct;
  numericalModel::Mesh mesh;

  explicit model ( const construct &Construct_,
                   const numericalModel::Mesh &mesh_) noexcept;
  
  //reload members
  void reloadThermalConstruct( const construct &other_ ) noexcept;
  
  ~model(void) noexcept;
};

}}

#endif // __TAT__MODEL_HPP
