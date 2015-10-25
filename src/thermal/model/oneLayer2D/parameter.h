//
//  parameter.h
//  tat
//
//  Created by Raymond Valdes on 10/25/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef parameter_h_1025153vc34
#define parameter_h_1025153vc34

namespace thermal{
namespace model{
namespace oneLayer2D{

enum class Parameter{
  disk_thermal_diffusivity,
  disk_thermal_conductivity,
  disk_radius,

  laser_radius,
  laser_power,
  detector_offset,
  detector_radius,
  rc_filter
};

class Parameters {

public:
  std::vector< Parameter > parameters;
  
  
  Parameters( std::vector< Parameter > const & parameters )
  : parameters(parameters) {};

};

}}}

#endif /* parameter_h */
