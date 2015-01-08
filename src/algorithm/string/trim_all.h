//
//  trim_all.h
//  tat
//
//  Created by Raymond Valdes on 1/7/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_trim_all_h
#define tat_trim_all_h

#include <boost/algorithm/string/trim_all.hpp>

namespace algorithm{
namespace string{

  using boost::algorithm::trim_all;
  using boost::algorithm::trim_all_if;
  using boost::algorithm::trim_all_copy;
  using boost::algorithm::trim_all_copy_if;


  using boost::algorithm::trim_fill;
  using boost::algorithm::trim_fill_if;
  using boost::algorithm::trim_fill_copy;
  using boost::algorithm::trim_fill_copy_if;

}}

#endif
