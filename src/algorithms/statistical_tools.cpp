#include <vector>
#include <cmath>
#include <limits>
#include <cstddef>
#include <iostream>

#include "numSimulations/Numerical_PhaseOfEmission_Results.h"

bool equalto(const double a, const double b)
{
    const double multi = a > b ? a : b;
    const double multi2 = multi >= 1 ? multi  : 1;

    return std::abs(a - b) < (std::numeric_limits<double>::epsilon()) * multi2;
}

bool equalto(const double a, const int b)
{
    const double multi = a > b ? a : b;
    const double multi2 = multi > 1 ? multi  : 1;

    return std::abs(a - b) < (std::numeric_limits<double>::epsilon()) * multi2;
}


double arrayMax(const double* x, const size_t I)
{
    double maxi = x[0];
    for(size_t i = 1; i < I ; ++i)
    {
        if(x[i] > maxi ) maxi = x[i];
    }


    return maxi;
}

double arrayMin(const double* x, const size_t I)
{
    double maxi = x[0];
    for(size_t i = 1; i < I ; ++i)
    {
        if(x[i] < maxi ) maxi = x[i];
    }

    return maxi;
}


void vector3DSetup(std::vector< std::vector< std::vector< double > > > &Vnew,
                   const size_t x, const size_t y, const size_t z)
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
                   const size_t x, const size_t y)
{
    Vnew.resize(x);
    for(size_t i = 0; i < x ; ++i )
    {
        Vnew[i].resize(y);
    }
}

double rss(const double N, const double* exp, const double* x_hat)
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

double variance(const size_t P, const size_t N, const double S)
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

double SobjectiveLS(const size_t N, const std::vector<double>& emissionExp,
                    const std::vector<double>& emissionEst)
{
    /*
        The objective function is evaluated for all the measurements.
        emissionEst[n]  ...     is calculated through the model
        emissionExp[n]  ...     is determined through the experiment

    */
    double fvec_objective = 0;

    for(size_t n=0 ; n < N; n++)
    {
        fvec_objective += pow( emissionExp[n] - emissionEst[n]  , 2);
    }

    return fvec_objective;
}

double SobjectiveLS(const size_t N, const double*emissionExp,
                    const double* emissionEst)
{
    /*
        The objective function is evaluated for all the measurements.
        emissionEst[n]  ...     is calculated through the model
        emissionExp[n]  ...     is determined through the experiment

    */
    double fvec_objective = 0;

    for(size_t n=0 ; n < N; n++)
    {
        fvec_objective += pow( emissionExp[n] - emissionEst[n]  , 2);
    }

    return fvec_objective;
}

double chisquare(const size_t N, const double*emissionExp,
                    const double* emissionEst)
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
                  const double* emissionNum)
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
           std::vector<double> &emissionEst)
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
           const double* const emissionEst)
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

void matrixTranspose(const size_t P, const size_t N, double*matrix)
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

void matrixTranspose(const size_t P, const size_t N, const double*matrix,
                     double*matrixT)
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
               double* MatrixResultant)
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
                      const double* Amatrix, double* cov)
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

void standardError(const size_t N, const double *cov, double* standardError)
{
    for(size_t i=0; i<N; ++i)
    {
        standardError[i] = sqrt( cov[ i + N * i ] );
    }

    return;
}

void printVariable(const double X1, const double X2, const double X3,
                   const size_t X4)
{
    std::cout << "\n";
    std::cout << X1 << "\t"<< X2 << "\t" << X3 << "\t" << X4;
    std::cout << "\n";
    return;
}

void printArray(const double* const matrix, const size_t N)
{
    std::cout << "\n";
    for(size_t j = 0 ; j < N ; ++j)
    {
        std::cout<< matrix[j] << "\n";
    }
    std::cout << "\n";
    return;
}

void printArray(const std::vector<double> &matrix, const size_t N)
{
    std::cout << "\n";
    for(size_t j = 0 ; j < N ; ++j)
    {
        std::cout<< matrix[j] << "\n";
    }
    std::cout << "\n";
    return;
}

void printArray2d(const size_t N, const size_t M, const double* const matrix)
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
                  const std::vector<std::vector<double>>& matrix)
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

void Amatrix(const size_t P, const size_t N, const double*fjac, double* Amatrix)
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

double fintegrate(double x, void *p)
{
  struct funcClass &params = *reinterpret_cast<struct funcClass *>(p);
  return params.eval(x);
}

double integrate(struct funcClass *Func, double xlow, double xhigh)
{
    //http://www.bnikolic.co.uk/nqm/1dinteg/gslgk.html

    struct funcClass &params = *Func;

    gsl_function F;
    F.function = &fintegrate;
    F.params = reinterpret_cast<void *>(&params);

    Func->code = gsl_integration_qng(&F, xlow, xhigh, params.epsabs,
                                     params.epsrel, &params.result,
                                     &params.error, &params.neval);
    return Func->result;
}

double MSEarea(const size_t N, std::vector<double> &func1,
               std::vector<double> &func2)
{
    ///Startup and initialization
    double sum = 0;
    for(size_t i=0 ; i < N ; i++)
    {
        sum += fabs(func1[i] - func2[i]);
    }

    return sum / N;
}

double MSEarea1(size_t N, double* func1, double* func2, double* xvar)
{
/*
  This function calculates the area between two curves.  This is done by
  feeding in two lists of points (func1 and func2) along with the independent
  variable (xvar).  The lists of points are fitted to an interpolating
  cubic spline.  This spline is then used to evaluate the integral and area
  between the lists.

*/
  ///Startup and initialization
  struct funcClass *Func1;
  Func1 = new struct funcClass (xvar, func1, N);
  struct funcClass *Func2;
  Func2 = new struct funcClass (xvar, func2, N);

  ///Evaluate Integration
  double etol = 1e-5;
  double xStep = etol;
  double xo;
  double area = 0;

  for (double xi = xvar[0]; xi <= xvar[N-1]; xi += xStep)
  {
    xo = xi;
    if(Func1->eval(xi) > Func2->eval(xi))
    {
      while(Func1->eval(xi) > Func2->eval(xi))
      {
          xi += xStep;
      }
      area += integrate(Func1, xo, xi) - integrate(Func2, xo, xi);
      xi -= xStep;
    }

    else if(Func2->eval(xi) > Func1->eval(xi))
    {
      while(Func2->eval(xi) > Func1->eval(xi))
      {
          xi += xStep;
      }
      area += integrate(Func2, xo, xi) - integrate(Func1, xo, xi);
      xi -= xStep;
    }

    else if( fabs(Func2->eval(xi) - Func1->eval(xi)) <  etol)
    {
      area +=0;
    }
  }

  ///Cleanup
  delete Func1;
  delete Func2;

  return area;
}

template< typename Type >
constexpr Type maximum( Type a, Type b )
{
    return a < b ? b : a;
}


