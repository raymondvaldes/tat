//
//  map_parameter_values.cpp
//  tat
//
//  Created by Raymond Valdes on 10/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "map_parameter_values.hpp"
#include "map_parameter_value.h"
#include "algorithm/algorithm.h"
#include <utility>

namespace thermal{
namespace model{
namespace oneLayer2D{

using thermal::model::Optics;
using algorithm::for_each;
using std::make_pair;




auto map_parameter_values
(
  Parameters const & parameters,
  Disk const & disk,
  Optics const & optics
)
noexcept -> Map_parameter_values
{
  auto m = Map_parameter_values();

  for_each( parameters, [&m, &disk, &optics]( auto const p ) noexcept {
    
    auto const v = map_parameter_value(p, disk, optics);
    m.emplace( make_pair( p, v)  );
  } );

  return m;
}

}}}


