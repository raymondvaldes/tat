//
//  find_unique_measurements.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/12/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include <algorithm>
#include <iostream>

#include "gTBC/gMeasure/find_unique_measurements.h"
#include "gTBC/gMeasure/find_unique_frequencies_in_files.h"
#include "gTBC/gMeasure/find_unique_labels_in_files.h"
#include "gTBC/gMeasure/find_unique_lambdas_in_files.h"
#include "gTBC/gMeasure/find_all_files_with.h"
#include "algorithm/algorithm.h"


namespace gTBC {

namespace gMeasure {

using algorithm::for_each;
using std::vector;

auto find_unique_measurements
(
  std::vector< ScopeFile > const & scope_files
)
noexcept ->  std::vector< Unique_scope_measurement >
{
  auto out = vector< Unique_scope_measurement >();

  //Break into groups of labels
  auto const list_labels = find_unique_labels_in_files( scope_files ).second ;
  assert( list_labels.size() == 1 );
  
  for_each( list_labels, [&scope_files, &out]( auto const & label ) noexcept
  {
    auto const files_with_label =
    find_all_files_with_label( scope_files,label);
    
    auto const list_lambdas =
    find_unique_lambdas_in_files( files_with_label ).second ;


    for_each( list_lambdas, [&files_with_label, &out]( auto const & lambda ) noexcept
    {
      auto const files_with_lambda =
      find_all_files_with_lambda( files_with_label, lambda );
      
      auto const list_freq =
      find_unique_frequencies_in_files( files_with_lambda ).second ;
    
      for_each( list_freq , [&files_with_lambda, &out]( auto const & freq ) noexcept
      {
        auto const files_with_freq =
        find_all_files_with_frequency( files_with_lambda, freq );
        
        out.push_back( Unique_scope_measurement{files_with_freq} );
      });
    });
  });
  
  return out;
}

} // namespace gMeasure
  
} // namespace gTBC
