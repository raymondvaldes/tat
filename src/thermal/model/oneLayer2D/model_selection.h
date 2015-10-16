//
//  model_selection.h
//  tat
//
//  Created by Raymond Valdes on 10/14/15.
//  Copyright © 2015 Raymond Valdes. All rights reserved.
//

#ifndef model_selection_h_101415
#define model_selection_h_101415

namespace thermal{
namespace model{
namespace oneLayer2D{

enum class Conduction_model {
  infinite_disk,
  finite_disk
};

enum class Detector_model {
  center_point,
  center_with_view,
  offset_point,
  offset_with_view
};

} // namespace oneLayer2D
} // namespace model
} // namespace thermal

#endif /* model_selection_h */
