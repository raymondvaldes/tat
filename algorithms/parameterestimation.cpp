#include "parameterestimation.hpp"

namespace parameterEstimation{

  constraints::bounds::bounds(const double lower_, const double upper_)
    : lower(lower_), upper(upper_){}

  constraints::constraints(const struct bounds a_sub_,
                           const struct bounds gamma_,
                           const struct bounds E1emit_,
                           const struct bounds R1_,
                           const struct bounds R0_,
                           const struct bounds lambda_ )
    : a_sub(a_sub_), gamma(gamma_), E1emit(E1emit_), R1(R1_), R0(R0_),
      lambda(lambda_) {}

}
