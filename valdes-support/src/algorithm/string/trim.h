//
//  trim.h
//  tat
//
//  Created by Raymond Valdes on 1/7/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__trim__
#define __tat__trim__

#include <string>
#include <boost/algorithm/string/trim_all.hpp>

namespace algorithm{
namespace string{

  using boost::algorithm::trim_left;
  using boost::algorithm::trim_left_copy;
  
  using boost::algorithm::trim_right;
  using boost::algorithm::trim_right_copy;

  using boost::algorithm::trim;
  using boost::algorithm::trim_copy;

}}

#endif /* defined(__tat__trim__) */
