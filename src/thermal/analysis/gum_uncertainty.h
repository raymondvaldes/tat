//
//  gum_uncertainty.h
//  tat
//
//  Created by Raymond Valdes on 9/10/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef __tat__gum_uncertainty__
#define __tat__gum_uncertainty__

#include <vector>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

#include "math/estimation/parameterestimation.hpp"
#include "thermal/analysis/thermalData.hpp"
#include "thermal/analysis/basedata.hpp"
#include "thermal/analysis/kernal.hpp"


namespace thermal {
namespace analysis {

class Taylor_uncertainty: private baseData
{
  private:
  const double tolDif = 0.01;
  void experimentalData( void ) ;
  void modelData( void ) ;
  void modelDataDerivative( void ) ;
  double sDerivative( enum model::labels::Name derive ) ;
  boost::numeric::ublas::vector<double> sDerivativeVector( void ) ;
  boost::numeric::ublas::vector<double>
    first_D_model( enum model::labels::Name derive , const double dh) ;
  boost::numeric::ublas::vector<double> second_D_model(
                    enum model::labels::Name d_first,
                    enum model::labels::Name d_second, const double dh) ;
  boost::numeric::ublas::matrix<double> jacobianY( void ) ;
  double derivative_M( enum model::labels::Name d_first ,
                       enum model::labels::Name d_second, const double dh ) ;

  
  public:
  explicit Taylor_uncertainty( void ) ;
  ~Taylor_uncertainty( ) ;

  void solve(
         const std::shared_ptr< math::estimation::unknownList > &list_in,
         const std::shared_ptr< ThermalData > &thermalData_in,
         const std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in ) ;
};


  
}}

#endif /* defined(__tat__gum_uncertainty__) */
