//
//  disk.cpp
//  tat
//
//  Created by Raymond Valdes on 10/21/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "disk.hpp"
#include <cassert>
#include "thermal/model/oneLayer2D/thermal_emission/frequency_sweep.h"
#include "finite_disk.hpp"
#include "infinite_disk.hpp"

namespace thermal{
namespace model{
namespace oneLayer2D{
namespace generator{

Disk::Disk
(
  Conduction_model const & conduction_model,
  Detector_model const & detector_model,
  slab::Slab const & slab,
  Optics const & optics
)
  : conduction_model(conduction_model),
    detector_model( detector_model ),
    slab( slab ), optics(optics)
{
}


auto Disk::evaluate
(
  equipment::laser::Modulation_frequencies const & modulation_frequencies
)
const -> thermal::model::complex::Temperatures
{
  assert( !modulation_frequencies.empty() );
  assert( detector_model == Detector_model::center_with_view ||
          detector_model == Detector_model::center_point) ;
  
  auto out = thermal::model::complex::Temperatures();
  
  switch( conduction_model )
  {
    case Conduction_model::finite_disk: {
        auto const disk = Finite_disk( detector_model, slab, optics );
        out = disk.evaluate( modulation_frequencies );
        break;
      }
    case Conduction_model::infinite_disk: {
        auto const disk = Infinite_disk( detector_model, slab, optics );
        out = disk.evaluate( modulation_frequencies );
        break;
      }
  }

  assert( out.size() == modulation_frequencies.size() );
  return out;
}

auto Disk::get_disk() const noexcept -> slab::Slab{ return slab;} ;
auto Disk::get_optics() const noexcept -> Optics{ return optics;} ;

} // namespace generator
} // namespace oneLayer2D
} // namespace model
} // namespace thermal

