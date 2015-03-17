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
#include <boost/units/io.hpp>


namespace units{

template<class Unit,class Y = double>
  using quantity = boost::units::quantity<Unit, Y>;

  
template<class Dim,class System, class Enable = void>
  using unit = boost::units::unit< Dim, System, Enable >;
  
  
  using boost::units::binary_prefix;
  using boost::units::engineering_prefix;
  using boost::units::no_prefix;


//template<class Unit, class Y = double >
//class quantity_with_uncertainty: public quantity< Unit, Y>
//{
//private:
//  typedef quantity<Unit,Y>      this_type;
//  typedef Y                     value_type;
//  typedef Unit                  unit_type;
//  
//  this_type uncertainty_value;
//  
//public:
//  using quantity< Unit, Y>::quantity;
//};




}

#endif
