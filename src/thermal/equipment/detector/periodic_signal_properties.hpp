//
//  periodic_signal_properties.hpp
//  tat
//
//  Created by Raymond Valdes on 10/2/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef periodic_signal_properties_h_therma_equipment_3243453245
#define periodic_signal_properties_h_therma_equipment_3243453245

#include "units.h"
#include "math/functions/PeriodicProperties.h"

namespace thermal{
namespace equipment{
namespace detector{

template < typename T >
using periodic_signal_properties_T = math::functions::PeriodicProperties< T  >;

typedef
periodic_signal_properties_T< units::si::electric_potential >
periodic_signal_properties;

} // namespace detector
} // namespace equipment
} // namespace thermal

#endif /* periodic_signal_properties_h */
