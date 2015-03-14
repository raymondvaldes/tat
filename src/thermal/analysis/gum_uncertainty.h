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
  baseData SavedState;
  
  const double dh = 1e-8;
  const double fullVal = 1;
  size_t N_unknowns;
  size_t N_knowns;
  size_t N_parameters;
  size_t N_dataPoints;

  double sDerivative( const enum model::labels::Name derive,
                      const size_t ith ) noexcept;
  boost::numeric::ublas::vector<double> sDerivativeVector( void ) noexcept;
  boost::numeric::ublas::vector<double>
    first_D_model( const enum model::labels::Name derive ,
                   const size_t ith) noexcept;
  boost::numeric::ublas::vector<double> second_D_model(
                    const enum model::labels::Name d_first,
                    const enum model::labels::Name d_second,
                    const size_t ith) noexcept;
  boost::numeric::ublas::matrix<double> jacobianY( void ) noexcept;
  boost::numeric::ublas::matrix<double> jacobianX( void ) noexcept;
  double derivative_M( const enum model::labels::Name d_first ,
                       const enum model::labels::Name d_second,
                       const size_t ith ) noexcept;
  boost::numeric::ublas::vector<double> evalModel(
  const vector< std::pair < enum thermal::model::labels::Name, double > > list,
  const size_t ith ) noexcept;
  boost::numeric::ublas::unit_vector<double>
  derivativeCi( const size_t maxSize, const size_t ith) noexcept;
  vector< enum thermal::model::labels::Name > get_list_knowns( void ) noexcept;
  boost::numeric::ublas::matrix<double> jacobian( void ) noexcept;
  boost::numeric::ublas::matrix<double> Djacobian(
    const enum thermal::model::labels::Name derive, const size_t ith ) noexcept;

  void modifyModel( const enum thermal::model::labels::Name derive,
                    const double val,
                    const size_t ith ) noexcept;
  void saveModel() noexcept;
  void resetModel() noexcept;
  boost::numeric::ublas::vector<double> uncertaintyResults( void ) noexcept;


  public:
  explicit Taylor_uncertainty( void ) noexcept;
  ~Taylor_uncertainty() noexcept;

  void solve(
         const std::shared_ptr< math::estimation::unknownList > &list_in,
         const std::shared_ptr< ThermalData > &thermalData_in,
         const std::shared_ptr< thermal::analysis::Kernal > &coreSystem_in ) noexcept;
};


  
}}

#endif /* defined(__tat__gum_uncertainty__) */
