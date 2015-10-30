//
//  Best_fit.h
//  tat
//
//  Created by Raymond Valdes on 5/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_thermal_analysis_oneL2D_estte_paramrs_weighted_average_Bes9629__
#define __tat_thermal_analysis_oneL2D_estte_paramrs_weighted_average_Bes9629__

#include <vector>
#include "units.h"
#include "thermal/model/slab/slab.h"
#include "thermal/model/optics/optics.h"
#include "thermal/model/oneLayer2D/model_selection.h"
#include "thermal/model/oneLayer2D/generator/disk.hpp"
#include "thermal/equipment/laser/modulation_frequencies.h"

namespace thermal{
namespace analysis {
namespace oneLayer2D {
namespace estimate_parameters{
namespace phase_analysis{

struct Best_fit{

  private:
  thermal::model::oneLayer2D::generator::Disk engine;
  
  public:
  thermal::model::slab::Slab slab;
  thermal::model::Optics optics;
  
  double phase_goodness_of_fit;


  explicit Best_fit
  (
    thermal::model::oneLayer2D::Conduction_model const conduction_model,
    thermal::model::oneLayer2D::Detector_model const detector_model,
    thermal::model::slab::Slab const slab,
    thermal::model::Optics const optics,
    double const phase_goodness_of_fit
  ) noexcept ;
  
  auto evaluate
  (
    equipment::laser::Modulation_frequencies const & modulation_frequencies
  )
  const -> thermal::model::complex::Temperatures;
  
  auto phase_goodness_of_fit_function() const -> double;
  
  auto caliberate_experimental_temperatures(
    equipment::laser::Modulation_frequencies const & frequencies,
    model::complex::Temperatures const & temperatures
  ) noexcept -> model::complex::Temperatures ;
  
};

} // namespace phase_analysis
} // namespace estimate_parameters
} // namespace oneLayer2D
} // namespace analysis
} // namespace thermal


#endif /* defined(__tat__Best_fit__) */
