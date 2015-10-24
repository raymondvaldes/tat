//
//  temperatures.cpp
//  tat
//
//  Created by Raymond Valdes on 10/15/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "thermal/model/complex/temperatures.h"
#include "phase.h"
#include "amplitude.h"
#include "algorithm/algorithm.h"

namespace thermal{
namespace model{
namespace complex{

using algorithm::transform;


Temperatures::Temperatures( std::vector< Temperature > const & values )
  : values( values )
{

}

auto Temperatures::size() const noexcept -> size_t
{
  return values.size();
}

auto Temperatures::empty() const noexcept -> bool
{
  return values.empty();
}

auto Temperatures::phases() const noexcept -> Phases
{
  auto out = complex::Phases( size() );
  
  transform( values, out.begin(), []( auto const a ) noexcept {
    return a.phase(); }
  );

  return out;
}

auto Temperatures::amplitudes() const noexcept -> Amplitudes
{
  auto out = complex::Amplitudes( size() );
  
  transform( values, out.begin(), []( auto const & a ) noexcept {
    return a.amplitude(); }
  );
  return out;
}


} // namespace complex
} // namespace model
} // naemsapce thermal
