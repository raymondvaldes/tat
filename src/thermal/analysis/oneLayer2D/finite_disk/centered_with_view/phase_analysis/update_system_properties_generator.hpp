//
//  update_system_properties_generator.hpp
//  tat
//
//  Created by Raymond Valdes on 10/23/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef update_system_properties_generator_hpp_102315
#define update_system_properties_generator_hpp_102315


#include <functional>
#include <utility>
#include <vector>

#include "thermal/model/slab/slab.h"
#include "thermal/model/optics/optics.h"
#include "electronics/filter/low-pass/RC-first-order/time_constant.h"
#include "thermal/model/oneLayer2D/finite_disk/parameter_list.hpp"

namespace thermal {
namespace analysis { 
namespace oneLayer2D { 
namespace finite_disk { 
namespace centered_with_view {
namespace phase_analysis{

auto update_system_properties_generator(
  model::slab::Slab const & slab_initial,
  model::Optics const & optics_initial,
  model::oneLayer2D::finite_disk::Parameters const & unknown_parameters
)
 noexcept ->
  std::pair< std::vector<double> ,
    std::function<
    std::tuple<
      model::slab::Slab,
      model::Optics  >( const double * x )  >
      >;


} } } } } }

#endif /* update_system_properties_generator_hpp */
