//
//  print_quantities.cpp
//  tat
//
//  Created by Raymond Valdes on 10/26/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "print_quantities.hpp"
#include "algorithm/algorithm.h"

namespace thermal{
namespace model{
namespace oneLayer2D{

auto print_quantities
(
  Parameters const parameters,
  slab::Slab const & slab,
  Optics const & optics
)
noexcept -> std::string
{
  auto v = std::string();

  algorithm::for_each( parameters, [&]( auto const p )
  {
    v += print_quantity( p, slab, optics ) + "\n";
  } );


  return v;
}

} // namespace
} // namespace
} // namespace

