//
//  update_system_properties_generator.hpp
//  tat
//
//  Created by Raymond Valdes on 10/24/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef update_system_properties_generator_hpp_102415
#define update_system_properties_generator_hpp_102415


#include <functional>
#include <utility>
#include <vector>

#include "thermal/model/slab/slab.h"
#include "thermal/model/optics/optics.h"
#include "thermal/model/oneLayer2D/finite_disk/parameter_list.hpp"


namespace thermal{
namespace analysis{
namespace oneLayer2D {

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

}
}
}

#endif /* update_system_properties_generator_hpp */
