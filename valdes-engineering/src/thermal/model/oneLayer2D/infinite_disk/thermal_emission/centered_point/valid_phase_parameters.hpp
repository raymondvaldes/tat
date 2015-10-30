//
//  valid_phase_parameters.hpp
//  tat
//
//  Created by Raymond Valdes on 10/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef valid_phase_parameters_hpp_rf23rc4r3c
#define valid_phase_parameters_hpp_rf23rc4r3c

#include "thermal/model/oneLayer2D/parameter_list.hpp"

namespace thermal {
namespace model {
namespace oneLayer2D {
namespace infinite_disk{
namespace thermal_emission {
namespace centered_point{

auto valid_phase_parameters() noexcept -> Parameters;

}}}}}}

#endif /* valid_phase_parameters_hpp */
