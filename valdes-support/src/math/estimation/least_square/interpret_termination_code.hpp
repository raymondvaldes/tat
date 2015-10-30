//
//  interpret_termination_code.hpp
//  tat
//
//  Created by Raymond Valdes on 10/28/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef interpret_termination_code_hpp_10281523423r
#define interpret_termination_code_hpp_10281523423r

#include "termination_code.h"

namespace math{
namespace estimation{
namespace least_square{

auto interpret_termination_code( int const code ) noexcept -> Termination_code;


}}}
#endif /* interpret_termination_code_hpp */
