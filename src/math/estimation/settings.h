//
//  settings.h
//  tat
//
//  Created by Raymond Valdes on 1/20/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_settings_h
#define tat_settings_h

#include <cstddef>
#include <boost/property_tree/ptree.hpp>

namespace math{

namespace estimation{

struct settings
{

  double ftol;
  double xtol;
  double gtol;
  size_t maxfev;
  double epsfcn;
  double factor;
  size_t mode;
  size_t nprint;

  static
  settings
  loadConfigfromXML( const boost::property_tree::ptree pt )
  noexcept;
  
  explicit settings( const double ftol_ = 1.e-10,
                     const double xtol_ = 1.e-10,
                     const double gtol_ = 1.e-10,
                     const size_t maxfev_ = 1e8,
                     const double epsfcn_ = 1.e-12,
                     const double factor_ = 10,
                     const size_t mode_ = 1,
                     const size_t nprint_ = 0 ) noexcept;
};


} //namespace estimation

} //namespace math


#endif
