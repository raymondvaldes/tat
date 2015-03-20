//
//  algorithm.h
//  tat
//
//  Created by Raymond Valdes on 1/26/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_algorithm_h
#define tat_algorithm_h

#include <boost/range/algorithm.hpp>
#include <boost/range/numeric.hpp>
#include <boost/algorithm/cxx11/any_of.hpp>
#include <boost/algorithm/cxx11/is_sorted.hpp>
#include <boost/algorithm/cxx11/find_if_not.hpp>
#include <boost/algorithm/cxx11/none_of.hpp>
#include <boost/range/algorithm_ext/iota.hpp>


/*The ones commented out are the ones that I am need to review. */

namespace algorithm {

  using boost::range::iota;

///////////////////////////////////// Mutating algorithms
  using boost::copy;
  using boost::copy_backward;
  using boost::fill;
  using boost::fill_n;
  using boost::generate;
  //using inplace_merge;
  using boost::merge;
  //using nth_element;
  //using partial_sort;
  //using partition;
  using boost::random_shuffle;
  using boost::remove;
  using boost::remove_copy;
  using boost::remove_copy_if;
  using boost::remove_if;
  using boost::replace;
  //using replace_copy;
  //using replace_copy_if;
  //using replace_if;
  using boost::reverse;
  using boost::reverse_copy;
  //using rotate;
  //using rotate_copy;
  //using stable_partition;
  //using stable_sort;
  //using boost::swap_ranges;

  template < class T >
  auto sort ( T const & list ) noexcept -> T
  {
    using std::sort;
    using std::begin;
    using std::end;
    
    auto list_to_sort = list;
    sort( begin(list_to_sort), end(list_to_sort) ) ;
    
    return list_to_sort;
  }
  
  template < class T, class BinaryPredicate >
  auto sort ( T const & list, BinaryPredicate const & p ) noexcept -> T
  {
    using std::sort;
    using std::begin;
    using std::end;
    
    auto list_to_sort = list;
    sort( begin( list_to_sort ), end( list_to_sort ), p ) ;
    
    return list_to_sort;
  }
  
  using boost::transform;
  
  template < class T, class BinaryPredicate >
  auto unique( T const & sorted_list,  BinaryPredicate const & p ) -> T
  {
    using std::unique;
    using std::begin;
    using std::end;

    auto uniqueList = sorted_list;
    
    auto last = unique( begin( uniqueList ) , end( uniqueList ) , p );
    
    uniqueList.erase( last , end( uniqueList ) ) ;
    
    return uniqueList;
  }
  
  using boost::unique_copy;
  
///////////////////////////////////// Non-mutating algorithms
  using boost::algorithm::any_of;
  using boost::algorithm::none_of;
  using boost::algorithm::is_sorted;
  using boost::algorithm::find_if_not;

//adjacent_find
//binary_search
  using boost::count;
  using boost::count_if;
//equal
//equal_range
  using boost::for_each;
  using boost::find;
  using boost::find_end;
  using boost::find_first_of;
  using boost::find_if;
//lexicographical_compare
  using boost::lower_bound;
  using boost::max_element;
  using boost::min_element;
//mismatch
//search
//search_n
  using boost::upper_bound;
  
  
///////////////////////////////////// Numerics

  using boost::accumulate;
  using boost::adjacent_difference;
  using boost::inner_product;
  using boost::partial_sum;

  
} // namespace range


#endif
