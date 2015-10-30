//
//  is_valid_signal.h
//  tat
//
//  Created by Raymond Valdes on 10/4/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef is_valid_signal_h_10415
#define is_valid_signal_h_10415

#include "thermal/equipment/detector/signal.h"

namespace thermal{
namespace equipment{
namespace detector{
namespace judsonTeledyneInSB{

auto is_valid_signal( Signal const signal ) noexcept -> bool;
auto is_invalid_signal( Signal const signal ) noexcept -> bool;

} // namespace judsonTeledyneInSb
} // namespace detector
} // namespace equipment
} // namespace thermal


#endif /* is_valid_signal_h */
