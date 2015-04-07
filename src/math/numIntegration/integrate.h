//
//  integrate.h
//  tat
//
//  Created by Raymond Valdes on 3/27/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat_math_numIntegration_integrate__
#define __tat_math_numIntegration_integrate__

#include "algorithm/algorithm.h"

#include <vector>
#include <cassert>
#include <boost/numeric/odeint.hpp>

#include "statistics/signal_processing/average.h"


namespace math{
namespace numIntegration{

using statistics::signal_processing::average;
using algorithm::for_each;

//[ integrate_observer
template< typename type >
struct push_back_state_and_time
{
    std::vector< std::vector< type > > & m_states;
    std::vector< type > & m_xPoints;

    push_back_state_and_time
    (
      std::vector< std::vector< type > > & states ,
      std::vector< type > & xPoints
    )
    : m_states( states ) , m_xPoints( xPoints ) { }

    void operator()
    (
      std::vector< type > const & y ,
      type x
    )
    {
        m_states.push_back( y ) ;
        m_xPoints.push_back( x ) ;
    }
};
//]

template< typename func_type, typename type >
auto integrate
(
  func_type const & func  ,
  std::vector< type > &f_x0,
  type const x0,
  type const x1,
  type const dx_intial_step
)
noexcept -> decltype( f_x0.front() * dx_intial_step )
{
  using boost::numeric::odeint::runge_kutta_dopri5;
  using boost::numeric::odeint::controlled_runge_kutta;
  using boost::numeric::odeint::dense_output_runge_kutta;
  using boost::numeric::odeint::integrate_adaptive;

  using std::vector;
  assert( !f_x0.empty() );

  /* The type of container used to hold the state vector */
  using state_type = vector< type  > ;
  
  auto const tol_absolute = 1E-10;
  auto const tol_relative = 1E-10;
  
  typedef runge_kutta_dopri5< state_type > dopri5_type;
  typedef controlled_runge_kutta< dopri5_type > controlled_dopri5_type;
  typedef dense_output_runge_kutta< controlled_dopri5_type > dense_output_dopri5_type;
  
  auto stepper = make_controlled( tol_absolute , tol_relative , dopri5_type() );

  auto y_vec = vector< state_type >() ;
  auto x_points = vector< type >() ;

  //This function integrates dy/dx from x0 to x1
  integrate_adaptive(
    stepper, func , f_x0 , x0 , x1 , dx_intial_step,
    push_back_state_and_time< type >( y_vec, x_points) );

  return y_vec.back().front() - y_vec.front().front();
}

} // namespace numIntegration
} // namespace math





#endif /* defined(__tat__integrate__) */
