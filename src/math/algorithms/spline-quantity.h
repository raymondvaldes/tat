//
//  spline-quantity.h
//  tat
//
//  Created by Raymond Valdes_New on 2/6/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_spline_quantity_h
#define tat_spline_quantity_h

#include <vector>
#include "units.h"
#include "units/algorithm/vector/quantity_to_value.h"

namespace math{

namespace algorithms{

template< typename Tx, typename Ty >
class spline_quantity{

private:
  std::vector< units::quantity< Tx > > x_quantities;
  std::vector< units::quantity< Ty > > y_quantities;

  void buildSpline()
  {
      //GET THESE SPLINES INTO DOUBLES TO FEED INTO THE SPLINE GENERATOR
  
  };

public:
  explicit spline_quantity(
  const std::vector< units::quantity< Tx > > &x_quantitiesIn,
  const std::vector< units::quantity< Tx > > &y_quantitiesIn  ) noexcept
  : x_quantities( x_quantitiesIn ), y_quantities( y_quantitiesIn )
  {
    buildSpline();
  };


};



} // namespace algorithms

} // namespace math


#endif
