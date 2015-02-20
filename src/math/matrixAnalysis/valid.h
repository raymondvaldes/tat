//
//  Header.h
//  tat
//
//  Created by Raymond Valdes_New on 2/20/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef tat_Header_h
#define tat_Header_h

namespace math {

namespace matrixAnalysis {

template< typename T>
auto valid( T const & N_rows, T const & N_columns, T const & N_elements )
noexcept -> bool
{
  auto const pass = N_elements == N_rows * N_columns ;
  return pass ;
}

  
} // namespace matrixAnalysis
  
} // namespace math

#endif
