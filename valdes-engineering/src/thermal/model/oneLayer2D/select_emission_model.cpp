//
//  select_emission_model.cpp
//  tat
//
//  Created by Raymond Valdes on 10/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "select_emission_model.hpp"
#include "finite_disk/emission/select_detector_model.h"
#include "infinite_disk/thermal_emission/select_detector_model.hpp"


namespace thermal{
namespace model{
namespace oneLayer2D{

using equipment::laser::Modulation_frequencies;
using slab::Slab;
using complex::Temperatures;

auto select_emission_model
(
  Conduction_model const conduction_model,
  Detector_model const detector_model
)
  -> std::function<
    complex::Temperatures(
        slab::Slab const &,
        Optics const &,
        equipment::laser::Modulation_frequencies const & )
  >
{
  auto func = std::function <
      Temperatures( Slab const &, Optics const &, Modulation_frequencies const&)
    >();


  switch( conduction_model )
  {
    case Conduction_model::infinite_disk:
    {
      using infinite_disk::thermal_emission::select_detector_model;
      func = select_detector_model(detector_model);
      break;
    }
    case Conduction_model::finite_disk:
    {
      using finite_disk::emission::select_detector_model;
      func = select_detector_model(detector_model);
      break;
    }
  }

  return func;
}

}}}
