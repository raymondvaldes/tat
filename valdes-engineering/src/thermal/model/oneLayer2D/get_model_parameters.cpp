//
//  get_model_parameters.cpp
//  tat
//
//  Created by Raymond Valdes on 10/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "get_model_parameters.hpp"
#include "finite_disk/emission/get_model_parameters.hpp"
#include "infinite_disk/thermal_emission/get_model_parameters.hpp"

namespace thermal{
namespace model{
namespace oneLayer2D{


auto
get_model_parameters(
  Conduction_model const conduction_model ,
  Detector_model const detector_model
)
-> Valid_parameters
{
  auto v = Valid_parameters();

  switch( conduction_model )
  {
    case Conduction_model::finite_disk:
    {
      using finite_disk::emission::get_model_parameters;
      v = get_model_parameters( detector_model );
      break;
    }
    case Conduction_model::infinite_disk:
    {
      using infinite_disk::thermal_emission::get_model_parameters;
      v = get_model_parameters( detector_model );
      break;
    }
  }

  return v;
}

} // namespace oneLayer2D
} // namespace model
} // namespace thermal

