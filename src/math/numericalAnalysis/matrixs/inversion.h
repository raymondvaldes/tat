//
//  inversion.h
//  tat
//
//  Created by Raymond Valdes on 9/16/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef __tat__inversion__
#define __tat__inversion__


#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>

namespace math {
namespace numericalAnalysis {
namespace matrix {

template<typename M>
M InvertMatrix(const M& input)
{
  using namespace boost::numeric::ublas;
  typedef permutation_matrix<std::size_t> pmatrix;
  
  // create a working copy of the input
  M A(input);
  M inverse(input);
  
  // create a permutation matrix for the LU-factorization
  pmatrix pm( A.size1() );
    
  // perform LU-factorization
  lu_factorize(A,pm);
  
  // create identity matrix of "inverse"
  inverse.assign(identity_matrix<typename M::value_type>(A.size1()));
    
  // backsubstitute to get the inverse
  lu_substitute(A, pm, inverse);
    
  return inverse;
}

}}}

#endif /* defined(__tat__inversion__) */