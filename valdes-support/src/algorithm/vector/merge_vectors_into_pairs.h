//
//  merge_vectors_into_pairs.h
//  tat
//
//  Created by Raymond Valdes on 10/28/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef merge_vectors_into_pairs_h
#define merge_vectors_into_pairs_h

#include <vector>
#include <gsl.h>
#include <utility>
#include "algorithm/algorithm.h"

namespace algorithm{
namespace vector{

template<typename T, typename F>
auto merge_vectors_into_pairs
(
  std::vector<T> const & Ts,
  std::vector<F> const & Fs
)
noexcept -> std::vector< std::pair< T, F > >
{
  Expects( !Ts.empty() && !Fs.empty() );
  Expects( Ts.size() == Fs.size() );
  using std::begin;
  
  auto const size = Ts.size();
  auto TFs = std::vector< std::pair<T, F> >( size );

  algorithm::transform( Ts, Fs, begin( TFs ),
  [] ( auto const t, auto const f )
  {
    using std::make_pair;
    
    auto tf = make_pair( t, f );
    return tf;
  });
  
  Ensures( TFs.size() == size );
  return TFs;
};



}
}

#endif /* merge_vectors_into_pairs_h */
