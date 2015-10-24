//
//  finite_disk.cpp
//  tat
//
//  Created by Raymond Valdes on 10/14/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#include "finite_disk.hpp"
#include <cassert>
#include "thermal/model/oneLayer2D/finite_disk/emission/centered_detector_with_view/frequency_sweep.hpp"
#include "thermal/model/oneLayer2D/finite_disk/emission/centered_point/frequency_sweep.hpp"
namespace thermal{
namespace model{
namespace oneLayer2D{
namespace generator{

Finite_disk::Finite_disk
(
  Detector_model const & detector_model,
  slab::Slab const & slab,
  Optics const & optics
)
  : detector_model( detector_model ), slab( slab ), optics(optics)
{

}


auto Finite_disk::evaluate
(
  equipment::laser::Modulation_frequencies const & modulation_frequencies
)
const -> thermal::model::complex::Temperatures
{
  assert( !modulation_frequencies.empty() );
  assert( detector_model == Detector_model::center_with_view ||
          detector_model == Detector_model::center_point
  ) ;
  auto out = thermal::model::complex::Temperatures();
  
  switch( detector_model )
  {
    case Detector_model::center_with_view:
      {
        using finite_disk::disk::emission::centered_detector_with_view::frequency_sweep;
        out = frequency_sweep(slab, optics, modulation_frequencies);
        break;
      }
    case Detector_model::center_point:
      {
        using finite_disk::disk::emission::centered_point::frequency_sweep;
        out = frequency_sweep(slab, optics, modulation_frequencies);
        break;
      }
  }

  assert( out.size() == modulation_frequencies.size() );
  return out;
}


} // namespace generator
} // namespace oneLayer2D
} // namespace model
} // namespace thermal
