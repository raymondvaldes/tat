//
//  settings.cpp
//  tat
//
//  Created by Raymond Valdes on 1/20/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#include "math/estimation/settings.h"
#include <cassert>
#include "statistics/signal_processing/abs.h"

namespace math{
namespace estimation{

using statistics::signal_processing::abs;

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
                       const size_t nprint_,
                     std::vector<double> const diag_
      ) noexcept
    :ftol(ftol_), xtol(xtol_), gtol(gtol_), maxfev(maxfev_), epsfcn(epsfcn_),
      factor(factor_), mode(mode_), nprint(nprint_), diag( diag_ )
  
    {}

auto settings::enable_scale_parameters( std::vector<double> const diag_ )
noexcept -> void
{
  auto const diag_abs = abs( diag_ );

  diag = diag_abs;

  assert( !diag.empty() );
  for( auto const s : diag ) {
    assert( s > 0 );
  }

  mode = 2 ;
}

auto settings::set_relative_sum_square_error( double const ftol_ )
noexcept -> void
{
  ftol = ftol_;
}

auto settings::set_relative_parameter_error( double const xtol_ )
noexcept -> void
{
  xtol = xtol_;
}

auto settings::set_orthogonality_between_fvec_jacobian( double const gtol_ )
noexcept -> void
{
  gtol = gtol_;
}

auto settings::set_maximum_iterations( size_t const maxfev_ )
noexcept -> void
{
  maxfev = maxfev_;
}

auto settings::set_error_of_fcn( double const epsfcn_ )
noexcept -> void
{
  epsfcn = epsfcn_;
}

auto settings::set_initial_set_bound_factor( double const factor_ )
noexcept -> void
{
  assert( factor_ >= 0.0999 ) ;
  assert( factor_ <= 100.001 );
  factor = factor_;
}

} //namespace estimation
} //namespace math
