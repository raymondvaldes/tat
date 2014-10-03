//
//  unit.h
//  tat
//
//  Created by Raymond Valdes on 9/30/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#ifndef tat_unit_h
#define tat_unit_h

#include <boost/units/unit.hpp>

namespace units {
  


 
 template< class Dim, class System, class Enable >
  using unit = boost::units::unit< Dim, System, Enable> ;

  
}

#endif
