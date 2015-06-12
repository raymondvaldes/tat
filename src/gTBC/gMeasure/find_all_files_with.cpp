//
//  find_all_files_with.cpp
//  tat
//
//  Created by Raymond Valdes_New on 3/12/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//
#include <iostream>
#include "gTBC/gMeasure/find_all_files_with.h"
#include "algorithm/algorithm.h"
#include "algorithm/vector/find_all.h"

using algorithm::sort;
using algorithm::for_each;
using algorithm::find_first_of;
using algorithm::find_end;
using algorithm::vector::find_all;

namespace gTBC {

namespace gMeasure{

auto find_all_files_with_label
(
  std::vector< ScopeFile > const & scope_files, std::string const & label
)
noexcept ->  std::vector< ScopeFile >
{
  auto const search_for_label =
  [&label]( auto const & scope_file, auto const &  ){
    auto const sameLabel = scope_file.label == label;
    return sameLabel;
  };
  
  sort( scope_files, sort_label_predicate ) ;
  auto const files_with_label = find_all( scope_files, label, search_for_label ) ;

  return files_with_label;
}


auto find_all_files_with_lambda
(
  std::vector< ScopeFile > const & scope_files,
  units::quantity< units::si::wavelength >const & lambda
)
noexcept ->  std::vector< ScopeFile >
{
  auto const search_for_label =
  [&lambda]( auto const & scope_file, auto const &  ){
    return scope_file.monochorometer_lambda == lambda;
  };
  
  sort( scope_files, sort_lambda_predicate ) ;
  auto const files_found = find_all( scope_files, lambda, search_for_label ) ;
  
  return files_found;
}


auto find_all_files_with_frequency
(
  std::vector< ScopeFile > const & files,
  units::quantity< units::si::frequency >const & frequency
)
noexcept -> std::vector< ScopeFile >
{
  auto const search_for_label =
  [&frequency]( auto const & scope_file, auto const &  )
  {
    using std::abs;
    auto const lhs = scope_file.laser_modulation_frequency.value() ;
    auto const rhs = frequency.value() ;
    auto const tolerance = 1e-8;
    auto const not_unique = abs( lhs - rhs ) < tolerance ;
  
    return not_unique;
  };
  
  sort( files, sort_frequency_predicate ) ;
  auto const files_found = find_all( files, frequency, search_for_label ) ;
  
  return files_found;
}

} // namespace gMeasure

} // namespace gTBC
