//
//  best_fit.hpp
//  tat
//
//  Created by Raymond Valdes on 10/24/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef best_fit_hpp_102415
#define best_fit_hpp_102415

#include <string>
#include "units.h"
#include "thermal/model/slab/slab.h"
#include "thermal/model/optics/optics.h"
#include "thermal/model/oneLayer2D/generator/disk.hpp"
#include "theoretical_results.hpp"
#include "thermal/model/oneLayer2D/parameter_list.hpp"

namespace thermal{
namespace analysis{
namespace oneLayer2D {

class Best_fit{

private:
  model::oneLayer2D::generator::Disk engine;
  
public:
  model::slab::Slab slab;
  model::Optics optics;
  Theoretical_results final_fit;

  explicit Best_fit
  (
    model::oneLayer2D::generator::Disk const & disk,
    Theoretical_results const & final_fit
  ) noexcept ;
  
  auto evaluate
  (
    equipment::laser::Modulation_frequencies const & modulation_frequencies
  )
  const -> model::complex::Temperatures;
  
  auto phase_goodness_of_fit_function() const -> double;
  auto parameters_to_string(
    model::oneLayer2D::Parameters const & parameters ) const -> std::string;
};


}}}


#endif /* best_fit_hpp */
