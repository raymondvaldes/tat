//
//  filter_using_cutoff_frequencies.h
//  tat
//
//  Created by Raymond Valdes on 10/28/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef filter_using_cutoff_frequencies_h
#define filter_using_cutoff_frequencies_h

#include <gsl.h>
#include "modulation_frequencies.h"
#include "modulation_cutoff_frequencies.h"
#include "algorithm/algorithm.h"
#include "algorithm/vector/merge_vectors_into_pairs.h"
#include "algorithm/vector/split_vector_of_pairs.h"
namespace thermal{
namespace equipment{
namespace laser {

template< typename T >
auto
filter_using_cutoff_frequencies
(
  Modulation_frequencies const & frequencies,
  Modulation_cutoff_frequencies const & cutoff,
  std::vector<T> measurements
) -> std::vector<T>
{
  using algorithm::vector::merge_vectors_into_pairs;
  using algorithm::vector::split_vector_of_pairs;
  Expects( frequencies.size() == measurements.size() ) ;
  Expects( !frequencies.empty() && !measurements.empty() );
  
  auto filtered_pairs = merge_vectors_into_pairs( frequencies, measurements );
  auto const size = filtered_pairs.size();
  
  auto const new_end =
  algorithm::remove_if( filtered_pairs , [&cutoff]( auto const & e ) noexcept
  {
    auto const frequency_out_of_bound =
    cutoff.check_if_out_of_bounds( e.first );
    
    return frequency_out_of_bound;
  } );
  
  filtered_pairs.erase(new_end, filtered_pairs.end());

  auto const f = split_vector_of_pairs( filtered_pairs );
  
  auto const filtered_measurements = f.second;

  Expects( filtered_measurements.size() <= size )  ;
  return filtered_measurements;
}


} // namespace laser
} // namespace experiment
} // namespace thermal


#endif /* filter_using_cutoff_frequencies_h */
