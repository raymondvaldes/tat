/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#include "math/solvers/tma.h"

namespace math{namespace solvers{


void solveMatrix( const size_t n, const std::vector<double>& b,
                  const std::vector<double>& d,
                  const std::vector<double>& a,
                  const std::vector<double>& C,
                  std::vector<double>& u ) noexcept
{
     /**
     * Impliment Thomas Algorithm to solve matrix.
     * Solve the Problem A u = C  -> u = Inverse[A].C
     * n - number of equations
     * b - sub diagonal
     * d - the main diagonal
     * a - sup-diagonal
     * C - right part
     * u - the answer
     */

    double*dw = new double[n];
    double*Cw = new double[n];

    Cw[0] = C[0];
    dw[0] = d[0];

    double m1;
    {
        constexpr int i = 1;
        m1 = b[i] / d[i-1];
        dw[i] = d[i] - m1 * a[i-1];
        Cw[i] = C[i] - m1 * C[i-1];
    }


    for (size_t i = 1 ; i < static_cast<size_t>(n)  ; ++i)
    {
        m1 = -b[i];
        m1 /= dw[i-1];
        dw[i] =  m1;
        dw[i] *= a[i-1];
        dw[i] += d[i];
        Cw[i] =  m1;
        Cw[i] *= Cw[i-1];
        Cw[i] += C[i];
    }

    u[n-1] = Cw[n-1];
    u[n-1] /= dw[n-1];

    for (int si = static_cast<int>(n) - 2 ; si >= 0 ; --si )
    {
      const size_t i = static_cast<size_t>(si);
      u[i]  = u[i+1];
      u[i] *= -a[i];
      u[i] += Cw[i];
      u[i] /= dw[i];
    }

  delete[] dw;
  delete[] Cw;

  return;
}
}}
