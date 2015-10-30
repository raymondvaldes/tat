//
//  modulation_cutoff_frequencies.h
//  tat
//
//  Created by Raymond Valdes on 10/14/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef modulation_cutoff_frequencies_h_101415
#define modulation_cutoff_frequencies_h_101415

#include "optional/optional.h"
#include "modulation_frequency.h"
#include "units.h"

namespace thermal{
namespace equipment{
namespace laser{
  
struct Modulation_cutoff_frequencies{
  Modulation_Frequency lower_bound = 0 * units::si::hertz;
  optional< Modulation_Frequency > upper_bound;
  
  auto check_if_in_bounds( Modulation_Frequency const & f )
  const noexcept -> bool
  {
    auto const satisfies_lower_bound = f > lower_bound;
    
    auto satisfies_upper_bound = true;
    
    if( upper_bound )
    {
      satisfies_upper_bound = f <  upper_bound;
    }
    
    auto const is_valid =
      satisfies_lower_bound && satisfies_upper_bound;
    
    return is_valid;
  };
  
  auto check_if_out_of_bounds( Modulation_Frequency const & f )
  const noexcept -> bool
  {
    return !check_if_in_bounds( f );
  
  }
};
  
  
} // namespacelaser
} // namespace equipment
} // namespace thermal


#endif /* modulation_cutoff_frequencies_h */
