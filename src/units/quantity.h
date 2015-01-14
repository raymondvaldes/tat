//
//  quantity.h
//  tat
//
//  Created by Raymond Valdes on 9/30/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef tat_quantity_h
#define tat_quantity_h

#include <boost/units/quantity.hpp>

namespace units{

template<class Unit,class Y = double>
  using quantity = boost::units::quantity<Unit, Y>;

}

#endif
