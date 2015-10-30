//
//  settings.h
//  tat
//
//  Created by Raymond Valdes on 1/20/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_settings_h
#define tat_settings_h

#include <vector>
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
  std::vector< double > diag;
  
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
                     const size_t nprint_ = 0,
                     std::vector<double> const diag_ = std::vector<double>()  ) noexcept;


/*
*	diag is an array of length n. if mode = 1 (see
*	  below), diag is internally set. if mode = 2, diag
*	  must contain positive entries that serve as
*	  multiplicative scale factors for the variables.
*/
    auto enable_scale_parameters( std::vector<double> const diag_ )
    noexcept -> void;
  
//*	ftol is a nonnegative input variable. termination
//*	  occurs when both the actual and predicted relative
//*	  reductions in the sum of squares are at most ftol.
//*	  therefore, ftol measures the relative error desired
//*	  in the sum of squares.
    auto set_relative_sum_square_error( double const ftol_ ) noexcept -> void;

//*	xtol is a nonnegative input variable. termination
//*	  occurs when the relative error between two consecutive
//*	  iterates is at most xtol. therefore, xtol measures the
//*	  relative error desired in the approximate solution.
    auto set_relative_parameter_error( double const xtol_ ) noexcept -> void;

//*	gtol is a nonnegative input variable. termination
//*	  occurs when the cosine of the angle between fvec and
//*	  any column of the jacobian is at most gtol in absolute
//*	  value. therefore, gtol measures the orthogonality
//*	  desired between the function vector and the columns
//*	  of the jacobian.
    auto set_orthogonality_between_fvec_jacobian( double const gtol_ ) noexcept -> void;

//*	maxfev is a positive integer input variable. termination
//*	  occurs when the number of calls to fcn is at least
//*	  maxfev by the end of an iteration.
    auto set_maximum_iterations( size_t const maxfev_ ) noexcept -> void;

//*	epsfcn is an input variable used in determining a suitable
//*	  step length for the forward-difference approximation. this
//*	  approximation assumes that the relative errors in the
//*	  functions are of the order of epsfcn. if epsfcn is less
//*	  than the machine precision, it is assumed that the relative
//*	  errors in the functions are of the order of the machine
//*	  precision.
    auto set_error_of_fcn( double const epsfcn_ ) noexcept -> void;

//*	factor is a positive input variable used in determining the
//*	  initial step bound. this bound is set to the product of
//*	  factor and the euclidean norm of diag*x if nonzero, or else
//*	  to factor itself. in most cases factor should lie in the
//*	  interval (.1,100.). 100. is a generally recommended value.
    auto set_initial_set_bound_factor( double const factor_ ) noexcept -> void;
  
  
};

} //namespace estimation
} //namespace math

#endif
