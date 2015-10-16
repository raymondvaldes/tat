//
//  is_valid.hpp
//  tat
//
//  Created by Raymond Valdes on 10/5/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef is_valid_hpp_100515
#define is_valid_hpp_100515

#include "Coefficient.h"

namespace thermal {
namespace pyrometry{
namespace twoColor{
namespace calibration{

auto coefficient_is_valid( Coefficient const g ) noexcept -> bool;

} // namespace calibration_coefficient
} // namespace twoColor
} // namespace pyrometry
} // namespace thermal

#endif /* is_valid_hpp */
