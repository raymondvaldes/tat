//
//  apply_to_all.h
//  tat
//
//  Created by Raymond Valdes on 9/18/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef __tat__apply_to_all__
#define __tat__apply_to_all__

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

namespace math {
namespace numericalAnalysis{
namespace ublas{

template<class OP, class E>
BOOST_UBLAS_INLINE
typename boost::numeric::ublas::vector_unary_traits<E, OP>::result_type
apply_to_all ( const boost::numeric::ublas::vector_expression<E> &e,
               const OP& op = OP() ) noexcept
{
    typedef typename boost::numeric::ublas::vector_unary_traits<E, OP>::expression_type expression_type;
    return expression_type (e ());
}


namespace functor {

  template <class T>
  class log
  {
  public:
    typedef T value_type;
    typedef T result_type;
    log() { }
    
    static
    result_type apply(const value_type& x) noexcept
    {
      return std::log(x); // insert any function you want
    }

  };

  template <class T>
  class sqrt
  {
  public:
    typedef T value_type;
    typedef T result_type;
    sqrt() { }
    
    static
    result_type apply(const value_type& x) noexcept
    {
      return std::sqrt(x); // insert any function you want
    }

  };

}

}}}

#endif /* defined(__tat__apply_to_all__) */
