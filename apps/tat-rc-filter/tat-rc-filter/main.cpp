#include <iostream>
#include <vector>
#include "units.h"
#include "electronics/filter/low-pass/RC-first-order/phase_shifts_from_input.hpp"
#include "cout/vector/print.h"
#include "plot/gnuplot.h"

int main()
{
  // apply RC filter

  using namespace units;
  using std::cout;
  using std::vector;
  namespace filter = electronics::filter::low_pass::RC_first_order;

  auto const frequencies = vector< quantity < frequency > >({
    .088 * hertz,
    .125 * hertz,
    .177 * hertz,
    .250 * hertz,
    .354 * hertz,
    .500 * hertz,
    .707 * hertz,
    1.0 * hertz,

    1.414213623 * hertz,
    2.0 * hertz,
    2.828427246 * hertz,
    4 * hertz,
    5.656854492 * hertz,
    8 * hertz,

    11.31370898 * hertz,
    16 * hertz,
    22.62741797 * hertz,
    32 * hertz,
    45.25483594 * hertz,
    64 * hertz,
    90.50967188 * hertz,

    128 * hertz,
    181.0193438 * hertz,
    256 * hertz,
    362.0386875 * hertz,
    512 * hertz,
    724.077375 * hertz,
    1024 * hertz,

    1448.15475 * hertz,
    2048 * hertz,
    2896.3095 * hertz,
    4096 * hertz,
    5792.619 * hertz,
    8192 * hertz,
    11585.238 * hertz
  });

  auto const tau = quantity< electrical_time_constant >( 3e-6 * si::seconds );
  auto const bias = filter::phase_shifts_from_input( frequencies, tau );


  cout::vector::print_table_values( frequencies, bias );

  return 0;
}

