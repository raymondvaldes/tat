//
//  settings.cpp
//  tat
//
//  Created by Raymond Valdes on 1/20/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "math/estimation/settings.h"

namespace math{

namespace estimation{

settings
settings::loadConfigfromXML(const boost::property_tree::ptree pt) noexcept
  {
      //initialize parameter estimation settings
      const double ftol     = pt.get<double>( "ftol" );
      const double xtol     = pt.get<double>( "xtol" );
      const double gtol     = pt.get<double>( "gtol" );
      const size_t maxfev   = pt.get<size_t>( "maxfev" );
      const double epsfcn   = pt.get<double>( "epsfcn" );
      const double factor   = pt.get<double>( "factor" );
      const size_t mode        = pt.get<size_t>( "mode" );
      const size_t nprint      = pt.get<size_t>( "nprint" );
    
      return settings{ ftol, xtol, gtol, maxfev, epsfcn, factor, mode, nprint };
  }

  settings::settings( const double ftol_,
                       const double xtol_,
                       const double gtol_,
                       const size_t maxfev_ ,
                       const double epsfcn_,
                       const double factor_,
                       const size_t mode_ ,
                       const size_t nprint_) noexcept
    :ftol(ftol_), xtol(xtol_), gtol(gtol_), maxfev(maxfev_), epsfcn(epsfcn_),
      factor(factor_), mode(mode_), nprint(nprint_){}


} //namespace estimation

} //namespace math
