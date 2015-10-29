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
#include "thermal/equipment/laser/filter_using_cutoff_frequencies.h"

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

auto Temperatures::filter_using_cutoff_frequencies
(
  thermal::equipment::laser::Modulation_frequencies const & frequencies,
  thermal::equipment::laser::Modulation_cutoff_frequencies const & cutoff
)
const noexcept -> Temperatures
{
  Expects( !frequencies.empty() ) ;
  Expects( frequencies.size() == values.size() );
  using thermal::equipment::laser::filter_using_cutoff_frequencies;
  
  auto const t = filter_using_cutoff_frequencies(frequencies, cutoff, values);
  auto const T = Temperatures(t);

  return T;
}


} // namespace complex
} // namespace model
} // naemsapce thermal
