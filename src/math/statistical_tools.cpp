/*----------------------------------------------------------------------------*\
  ========                      |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||   	  		|
-------------------------------------------------------------------------------
License
    This file is part of Thermal Analysis Toolbox.

    Thermal Analysis Toolbox is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    Thermal Analysis Toolbox is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with
    Thermal Analysis Toolbox.  If not, see <http://www.gnu.org/licenses/>.

\*----------------------------------------------------------------------------*/

#include <vector>
#include <cmath>
#include <limits>
#include <cstddef>
#include <iostream>

#include <boost/assert.hpp>

#include "math/statistical_tools.hpp"
#include "math/numIntegration/gslfunc.hpp"

void vector3DSetup(std::vector< std::vector< std::vector< double > > > &Vnew,
                   const size_t x, const size_t y, const size_t z) noexcept
{
  Vnew.resize(x);
  for(size_t i = 0; i < x ; ++i )
  {
    Vnew[i].resize(y);

    for(size_t j = 0; j < y ; ++j)
    {
       Vnew[i][j].resize(z);
    }
  }
  return;
}

void vector2DSetup(std::vector< std::vector< double > > &Vnew,
                   const size_t x, const size_t y) noexcept
{
    Vnew.resize(x);
    for(size_t i = 0; i < x ; ++i )
    {
        Vnew[i].resize(y);
    }
}

double rss(const double N, const double* exp, const double* x_hat) noexcept
{
    /*
        This function calculated the residual sum of squares between an
        experimental results and predicted results.
            exp         experimental results
            x_hat       predicted results
            N           number of measurements
    */
    double sum = 0;
    for(size_t n = 0; n < N ; n++)
    {
        sum += (exp[n] - x_hat[n]) * (exp[n] - x_hat[n]);
    }

    return sum;
}

double variance(const size_t P, const size_t N, const double S) noexcept
{
    /*
        The estimate of the variance (sigma^2)  is obtained from the degrees of
        freedom and the objective function.
            S ... objective function
            P ... number of measurements
            N ... number of unknown parameters
    */
    return S / (P-N);
}

double chisquare(const size_t N, const double*emissionExp,
                    const double* emissionEst) noexcept
{
    /*
        The objective function is evaluated for all the measurements.
        emissionEst[n]  ...     is calculated through the model
        emissionExp[n]  ...     is determined through the experiment
    */

    double chisquare = 0;

    for(size_t n=0 ; n < N; n++)
    {
        chisquare += (pow( emissionExp[n] - emissionEst[n]  , 2) / emissionEst[n]);
    }
    return chisquare;
}

double Sobjective(const size_t L_end, const double*emissionExp,
                  const double* emissionNum) noexcept
{
    /*
        The objective function is evaluated for all the measurements and the
        mean square is returned.

    */
    double fvec_objective = 0;

    for(size_t n=0 ; n < L_end; n++)
    {
        fvec_objective += pow((emissionExp[n] / emissionNum[n] - 1), 2);
    }

    return sqrt(fvec_objective / L_end );
}

double MSE(const size_t N, std::vector<double> &emissionExp,
           std::vector<double> &emissionEst) noexcept
{
    /*
        The objective function is evaluated for all the measurements and the
        mean square is returned.
    */
    double fvec_objective = 0;

    for(size_t n=0 ; n < N; n++)
    {
        fvec_objective += pow( emissionEst[n]/emissionExp[n] - 1  , 2);
    }

    return 100*(fvec_objective / N);
}

double MSE(const size_t N, const double* const emissionExp,
           const double* const emissionEst) noexcept
{
    /*
        The objective function is evaluated for all the measurements and the
        mean square is returned.

    */
    double fvec_objective = 0;

    for(size_t n=0 ; n < N; n++)
    {
        fvec_objective += pow( emissionEst[n]/emissionExp[n] - 1  , 2);
    }

    return 100*(fvec_objective / N);
}

void matrixTranspose(const size_t P, const size_t N, double*matrix) noexcept
{
    /*
       N is parameters being estimated
       P number of measurements
    */

    for(size_t j = 0 ; j < P ; ++j)
    {
        for(size_t i = 0 ; i < N ; ++i)
        {
            matrix[j+P*i] = matrix[i+j*N];
        }
    }

    return;
}

void matrixTranspose( const size_t P, const size_t N, const double*matrix,
                      double*matrixT ) noexcept
{
    /*
       N is parameters being estimated
       P number of measurements
    */

    for(size_t j = 0 ; j < P ; ++j)
    {
        for(size_t i = 0 ; i < N ; ++i)
        {
            matrixT[j+P*i] = matrix[i+j*N];
        }
    }

    return;
}

void matrixDot(const double* MatrixA, const size_t rowA, const size_t columnA,
               const double* MatrixB, const size_t rowB, const size_t columnB,
               double* MatrixResultant) noexcept
{
    /*
        This is for matrices arranged in 1D with the indexes such that:
            i + m * j
                i column
                j row
                m row width

        The arguments row and column are the lengths of the row and column of the
        resultant matrix.
            MatrixResultant[row,column] = MatrixA[row,::] * MatrixB[::,column]
     */
    if(columnA != rowB)
    {
        std::cout << "\nerror with matrix size\n";
        return;
    }

    for(size_t j = 0 ; j < rowA ; ++j)
    {
        for(size_t i = 0 ; i < columnB ; ++i)
        {
            MatrixResultant[i+columnB*j] = 0;

            for (size_t k = 0; k < columnA; ++k)
            {
                MatrixResultant[i+columnB*j] +=
                    MatrixA[k + j*columnA] * MatrixB[i + columnB*k];
            }
        }
    }

    return;
}

void covarianceMatrix(const size_t N, const double variance,
                      const double* Amatrix, double* cov) noexcept
{
    /*
        The covariance matrix is the product of the variance and the jacobian
        matrix.
    */
    double* AmatrixT;
    AmatrixT = (double*)malloc(N * N * sizeof(double));
    matrixTranspose(N, N, Amatrix, AmatrixT);

    size_t ij=0;
    for(size_t j = 0 ; j < N ; ++j)
    {
        for(size_t i = 0 ; i < N ; ++i)
        {
            cov[ij] = variance * AmatrixT[ij] ; //  fjac[i+m*j]
            ij++;
        }
    }

    free(AmatrixT);
    return;
}

void standardError(const size_t N, const double *cov, double* standardError) noexcept
{
  BOOST_ASSERT( cov != nullptr ) ;
  BOOST_ASSERT( standardError != nullptr ) ;
  BOOST_ASSERT( N > 0 ) ;
  
    for(size_t i=0; i<N; ++i)
    {
        standardError[i] = sqrt( cov[ i + N * i ] );
    }

    return;
}

void printVariable(const double X1, const double X2, const double X3,
                   const size_t X4) noexcept
{
    std::cout << "\n";
    std::cout << X1 << "\t"<< X2 << "\t" << X3 << "\t" << X4;
    std::cout << "\n";
    return;
}

void printArray(const double* const matrix, const size_t N) noexcept
{
    std::cout << "\n";
    for(size_t j = 0 ; j < N ; ++j)
    {
        std::cout<< matrix[j] << "\n";
    }
    std::cout << "\n";
    return;
}

void printArray(const std::vector<double> &matrix, const size_t N) noexcept
{
    std::cout << "\n";
    for(size_t j = 0 ; j < N ; ++j)
    {
        std::cout<< matrix[j] << "\n";
    }
    std::cout << "\n";
    return;
}

void printArray2d(const size_t N, const size_t M, const double* const matrix) noexcept
{
    for(size_t j = 0 ; j < M ; ++j)
    {
        for(size_t i = 0 ; i < N ; ++i)
        {
            std::cout<< matrix[i+N*j] << "\t";
        }
        std::cout << "\n";
    }
    return;
}

void printArray2d(const size_t N, const size_t M,
                  const std::vector<std::vector<double>>& matrix) noexcept
{
    for(size_t j = 0 ; j < M ; ++j)
    {
        for(size_t i = 0 ; i < N ; ++i)
        {
            std::cout<< matrix[j][i]<< "\t";
        }
        std::cout << "\n";
    }
    return;
}

void Amatrix(const size_t P, const size_t N, const double*fjac, double* Amatrix) noexcept
{
    /*
        The A matrix is defined as the transpose of the jacobian dot product with
        the jacobian matrix.  The jacobian matrix is of size (N,P).  The resulting
        A matrix will be size (N,N). Where,
            N is the number of parameters to be estimated
            P is the number of measurements used in the estimation algorithm.
    */
    double*fjacT;
    fjacT = (double*)malloc(P * N * sizeof(double));

    matrixTranspose(P, N, fjac, fjacT);
    matrixDot(fjacT, N, P, fjac, P, N, Amatrix);

    free(fjacT);
    return;
}



double MSEarea(const size_t N, std::vector<double> &func1,
               std::vector<double> &func2) noexcept
{
    ///Startup and initialization
    double sum = 0;
    for(size_t i=0 ; i < N ; i++)
    {
      sum += std::fabs(func1[i] - func2[i]);
    }

    return sum / N;
}


template< typename Type >
constexpr Type maximum( Type a, Type b )
{
    return a < b ? b : a;
}


