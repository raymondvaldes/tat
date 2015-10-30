//
//  lambda_generator.hpp
//  tat
//
//  Created by Raymond Valdes on 10/18/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef lambda_generator_hpp_101815
#define lambda_generator_hpp_101815

#include <cstdint>
#include <vector>
#include "thermal/model/oneLayer2D/finite_disk/disk/biot.h"
#include "thermal/model/oneLayer2D/finite_disk/disk/dimensionless/radius.hpp"
#include "thermal/model/oneLayer2D/finite_disk/seperation_of_variables/lambda.h"
#include "thermal/model/oneLayer2D/finite_disk/seperation_of_variables/complex_lambda.h"

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace finite_disk{
namespace seperation_of_variables{

struct Search_bound{
  double lower;
  double upper;
  Search_bound( double lower, double upper ): lower(lower), upper(upper){};
};

class Lambda_generator{

private:
  disk::dimensionless::Radius_s s;
  disk::Biot biot_radial;
  dimensionless::Thermal_penetration l;
  
  mutable std::vector< Lambda > lambdas;
  mutable std::vector< Complex_lambda > complex_lambdas;
  
  auto search_bounds() const noexcept-> Search_bound;
  auto push_back_lambda( ) const noexcept -> void;
  auto generate_lambdas_upto( size_t nth ) const noexcept -> void;
  
public:

  explicit Lambda_generator
  (
    disk::dimensionless::Radius_s const s,
    disk::Biot const biot_2_radial,
    dimensionless::Thermal_penetration const l
  );
  
  auto objective_function( Lambda const lambda ) const noexcept -> double;

  auto real_lambda_at( size_t const nth ) const -> Lambda;
  auto complex_lambda_at( size_t const nth ) const noexcept -> Complex_lambda;
  auto size() const noexcept -> size_t;
  auto empty() const noexcept -> bool;
  
  auto check_s_infinite_assumption() const -> bool;
  
  
};

} // seperation_of_variables
} // finite_disk
} // oneLayer2d
} // model
} // thermal

#endif /* lambda_generator_hpp */
