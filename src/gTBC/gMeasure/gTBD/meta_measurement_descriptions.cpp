//
//  meta_measurement_descriptions.cpp
//  tat
//
//  Created by Raymond Valdes on 10/13/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "meta_measurement_descriptions.hpp"

#include <utility>

#include "algorithm/algorithm.h"
#include "math/utilities/even.h"


namespace gTBC {
namespace gMeasure {

using std::vector;
using std::pair;
using std::make_pair;
using algorithm::for_each;
using algorithm::sort;
using algorithm::remove_if;
using namespace units;

auto meta_measurement_descriptions::laser_frequencies( void ) const
noexcept -> std::vector< units::quantity< units::si::frequency > >
{
  auto results = vector< units::quantity< units::si::frequency > >();

  for_each( meta_datas, [&results]( auto const & meta_data )
  {
    auto const laser_frequency = meta_data.laser_modulation_frequency ;
    results.push_back( laser_frequency ) ;
  } ) ;

  return results;
}

auto meta_measurement_descriptions::laser_phases(void) const
noexcept -> std::vector <
  std::pair<  units::quantity< units::si::frequency   > ,
              units::quantity< units::si::plane_angle > > >
{
  auto results = vector< pair< quantity< frequency > , quantity< plane_angle >>>();

  for_each( meta_datas, [&results]( auto const & meta_data )
  {
    auto const laser_info = make_pair(  meta_data.laser_modulation_frequency,
                                        meta_data.reference_argument ) ;
    results.push_back( laser_info ) ;
  } ) ;

  return results;
}

auto meta_measurement_descriptions::detector_wavelength( void ) const
noexcept -> units::quantity< units::si::wavelength >
{
  return meta_datas[0].monochrometer_wavelength;
}

auto meta_measurement_descriptions::measurement_amplitudes( void ) const
noexcept-> std::vector< units::quantity< units::si::electric_potential > >
{
  auto results = vector< quantity< electric_potential > >();

  for_each( meta_datas, [&results]( auto const & meta_data )
  {
    results.push_back( meta_data.signal_amplitude ) ;
  } ) ;

  return results;
}

auto meta_measurement_descriptions::measurement_phases( void ) const
noexcept-> std::vector< units::quantity< units::si::plane_angle > >
{
  auto results = vector< quantity< plane_angle > >();

  for_each( meta_datas, [&results]( auto const & meta_data )
  {
    results.push_back( meta_data.signal_phase ) ;
  } ) ;

  return results;
}

auto
meta_measurement_descriptions::measurement_periodic_signal_properties
(
  units::quantity< units::si::electric_potential > signal_steady_offset
)
const noexcept
-> std::vector< thermal::equipment::detector::periodic_signal_properties >
{
  using thermal::equipment::detector::periodic_signal_properties;
  auto results = vector< periodic_signal_properties >();

  for_each( meta_datas, [ &results, signal_steady_offset ]
  ( auto const & meta_data ) noexcept
  {
    results.push_back( meta_data.get_periodic_signal_properties( signal_steady_offset ) ) ;
  } ) ;

  return results;
}


auto meta_measurement_descriptions::size(void) const noexcept -> size_t
{
  auto const measurements = meta_datas.size();
  return measurements;
}


auto meta_measurement_descriptions::detector_grounds(void) const
noexcept -> std::vector < Frequency_detector_ground >
{
  using math::utilities::is_even;
  
  auto const n_measurements = meta_datas.size();
  assert( is_even( n_measurements ) );
  
  auto results = vector< Frequency_detector_ground >();
  results.reserve( meta_datas.size() / 2 ) ;
  
  for( size_t i = 0 ; i < meta_datas.size() ; ++i )
  {
    if( is_even(i+1) && i > 0 )
    {
      auto const f1 = meta_datas[i-1].laser_modulation_frequency;
      auto const f2 = meta_datas[i].laser_modulation_frequency;
      
      assert( std::abs( f1.value() - f2.value() )  < 10e-4 ) ;
      
      auto const lamb1 = make_pair( meta_datas[i-1].monochrometer_wavelength,
                                    meta_datas[i-1].signal_steady_offset_grnd );
      auto const lamb2 = make_pair( meta_datas[i].monochrometer_wavelength,
                                    meta_datas[i].signal_steady_offset_grnd );
      
      auto const freq_det_grnd = f1 ;
      
      
      results.emplace_back( freq_det_grnd, lamb1, lamb2 ) ;
    }
  }

  return results;
}


auto
meta_measurement_descriptions::sort_by_ascending_frequency() const
noexcept -> meta_measurement_descriptions
{
  auto metas_to_sort = meta_datas ;
  
  auto const sort_by_frequency = []( auto const a, auto const b ) noexcept
  {
    auto const first = a.laser_modulation_frequency.value();
    auto const second = b.laser_modulation_frequency.value();
    
    return first < second ;
  };
  
  sort( metas_to_sort, sort_by_frequency );

  return metas_to_sort;
}



auto
meta_measurement_descriptions::filter_using_cutoff_frequencies(
  thermal::equipment::laser::Modulation_cutoff_frequencies const &
  cutoff_frequencies
) const noexcept -> meta_measurement_descriptions
{
  auto filtered_metas = meta_datas;

  auto const new_end = remove_if( filtered_metas , [&cutoff_frequencies]( auto const & e ) noexcept
  {
    auto const frequency_out_of_bound =
    cutoff_frequencies.check_if_out_of_bounds( e.laser_modulation_frequency );
    return frequency_out_of_bound;
  } );
  
  filtered_metas.erase(new_end, filtered_metas.end());
  
  
  auto const filtered = meta_measurement_descriptions( filtered_metas );
  
  auto const sorted_filtered = filtered.sort_by_ascending_frequency();


  return sorted_filtered;
}

} // namespace gMeasure
} // namespace gTBC
