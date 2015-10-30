//
//  meta_measurement_descriptions.hpp
//  tat
//
//  Created by Raymond Valdes on 10/13/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef meta_measurement_descriptions_hpp_101315
#define meta_measurement_descriptions_hpp_101315

#include "meta_measurement_description.hpp"
#include "thermal/equipment/laser/modulation_cutoff_frequencies.h"
#include "thermal/model/complex/temperatures.h"
#include <vector>
#include <utility>

#include "units.h"
#include "frequency_detector_ground.hpp"

namespace gTBC {
namespace gMeasure {

struct meta_measurement_descriptions{

private:
  std::vector< meta_measurement_description > meta_datas                                                                     ;
  
public:              
  meta_measurement_descriptions
  (
    std::vector< meta_measurement_description > const & meta_datas_
  ): meta_datas( meta_datas_ ){};
  
  
  auto laser_phases(void) const
  noexcept -> std::vector<
  std::pair<  units::quantity< units::si::frequency   > ,
              units::quantity< units::si::plane_angle > > >;
  
  auto laser_frequencies( void ) const
  noexcept -> std::vector< units::quantity< units::si::frequency > >;
  
  auto detector_wavelength( void ) const
  noexcept -> units::quantity< units::si::wavelength >;
  
  auto detector_grounds(void) const
  noexcept -> std::vector < Frequency_detector_ground > ;

  auto measurement_periodic_signal_properties
  (
    units::quantity< units::si::electric_potential > signal_steady_offset
  ) const
  noexcept -> std::vector< thermal::equipment::detector::periodic_signal_properties >;

  auto measurement_amplitudes( void ) const
  noexcept-> std::vector< units::quantity< units::si::electric_potential > >;
  
  auto measurement_amplitudes_2( void )
  noexcept-> std::vector< units::quantity< units::si::electric_potential > >;
  
  auto measurement_amplitudes_average( void )
  noexcept-> std::vector< units::quantity< units::si::electric_potential > >;

  auto measurement_phases( void ) const
  noexcept-> std::vector< units::quantity< units::si::plane_angle > > ;
  
  auto measurement_phases_2( void )
  noexcept-> std::vector< units::quantity< units::si::electric_potential > >;
  
  auto measurement_phases_average( void )
  noexcept-> std::vector< units::quantity< units::si::electric_potential > >;


  auto detector_wavelengths( void )
  noexcept -> std::pair<  units::quantity< units::si::wavelength >,
                          units::quantity< units::si::wavelength > >;
  
  auto is_twoColor_measurement( void ) noexcept -> bool;
  
  auto modulator_settings( void ) noexcept -> std::pair<
    units::quantity< units::si::dimensionless>,
    units::quantity< units::si::dimensionless> >;
  
  
  auto filter_using_cutoff_frequencies(
    thermal::equipment::laser::Modulation_cutoff_frequencies const &
    cutoff_frequencies
  ) const noexcept -> meta_measurement_descriptions ;
  
  auto sort_by_ascending_frequency()
  const noexcept -> meta_measurement_descriptions;
  
  auto size(void) const noexcept -> size_t;
  auto empty() const noexcept -> bool;
  
  auto temperatures_dummy_amplitudes()
  const noexcept -> thermal::model::complex::Temperatures;

};

} // namespace gMeasure
} // namespace gTBC


#endif /* meta_measurement_descriptions_hpp */
