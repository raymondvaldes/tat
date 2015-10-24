//
//  temperatures_factory_dummy_amplitudes.hpp
//  tat
//
//  Created by Raymond Valdes on 10/24/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef temperatures_factory_dummy_amplitudes_hpp_102415
#define temperatures_factory_dummy_amplitudes_hpp_102415

#include "temperatures.h"
#include "phase.h"

namespace thermal{
namespace model{
namespace complex{

auto
temperature_factory_dummy_amplitudes( Phases const & phases )
noexcept -> Temperatures;

} // namespace complex
} // namespace model
} // namespace thermal

#endif /* temperatures_factory_dummy_amplitudes_hpp */
