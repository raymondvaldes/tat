//
//  get_model_parameters.hpp
//  tat
//
//  Created by Raymond Valdes on 10/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef get_model_parameters_hpp_123f4u23uh4f
#define get_model_parameters_hpp_123f4u23uh4f


#include "thermal/model/oneLayer2D/model_selection.h"
#include "thermal/model/oneLayer2D/parameter_list.hpp"
#include <utility>

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace emission{

auto
get_model_parameters( Detector_model const detector_model )
-> Valid_parameters;

} // namespace thermal_emission
}
} // namespace oneLayer2D
} // namespace model
} // namespace thermal

#endif /* get_model_parameters_hpp */
