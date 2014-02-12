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
#include <cmath>
#include <iostream>
#include <random>

#include "thermal/analysis/kernal.hpp"
#include "math/statistical_tools.hpp"
#include "thermal/simulations/Numerical_Setup.h"
#include "math/estimation/lmdiff.hpp"
#include "math/utility.hpp"

double Iheat(double Isteady, double Itransient, double omega, double t) //verified
{
    return Isteady + Itransient * cos( omega * t )  ;
}

double Iheat_int(const double Isteady,const double Itransient,
                        const double omega, const double t) //verified
{
    return Isteady * t + ( Itransient * sin( omega * t ) ) / omega ;
}

double tau_0(const double omega)
{
    return ( 2. * M_PI ) / omega;
}

size_t sumVector(const size_t *const vector1,const size_t sizeV)
{
    /*
    Accepts a vector of length sizeV of type size_t and returns the sum of the
    vector.
    */

    size_t sum=0;
    for(size_t i=0; i< sizeV; ++i)
    {
        sum += vector1[i];
    }

    return sum;
}

double SOR(double **A, double *b,const size_t n,double *phi, double omega,
           double error)
{
	// omega is the relaxation parameter
	double sigma;
	double *phi_n = new double[n];
	double errorphimax = 0.5;
	double *errorphi = new double[n];

	int iteration = 0;
	int iter_max = -1+30;

////copy this into main to test sor -- start
//    double *A_test[2];
//    for ( int n = 0 ; n < 2 ; ++n )
//        A_test[n]= new double [2];
//    double x_test[2];
//    double b_test[2];
//    A_test[0][0] = 1;     A_test[0][1] = 0;
//    A_test[1][0] = 2;     A_test[1][1] = 1;
//
//    b_test[0] = 1;
//    b_test[1] = 2;
//    SOR(A_test , b_test , 2 , x_test,1.94,.001);
//    View A,b matrix
//
//    for (int i = 0 ; i < 2 ; i++)
//    {
//        cout<<"";
//        for (int j = 0 ; j < 2; j++)
//            cout << "\t" << A_test[i][j];
//        cout<<"\t";
//        cout << "\t" << b_test[i] << "\tx = " << x_test[i] << "\n" ;
//    }
////copy this into main to test sor -- end


	//Set initial distribution of phi
    for ( size_t i = 0 ; i < n ; i++ )
            phi[i] = 1.;

	//Start solvigng for phi
	while ( errorphimax > error  && ++iteration <= iter_max)
	{
        for ( size_t i = 0 ; i < n ; i++ )
            phi_n[i] = phi[i];

		for(size_t i = 0 ; i < n ; i++ )
		{
			sigma = b[i];

			for(size_t j = 0 ; j < i ; j++ )
                sigma -= A[i][j] * phi[j];

            for(size_t j = i+1 ; j < n ; j++ )
                sigma -= A[i][j] * phi_n[j];

//			for(int j = 0 ; j < i-1 ; j++ )
//                sigma -= A[i][j] * phi[j];
//
//            for(int j = i+1 ; j < n ; j++ )
//                sigma -= A[i][j] * phi_n[j];

            //Gauss-Siedel Iteration;
            phi[i] = sigma / A[i][i];

            //SOR Implementation
            phi[i] = omega * phi[i] + (1.-omega) * phi_n[i];

		}

        for (size_t i=0;i<n;i++)
            errorphi[i] = fabs( phi[i] - phi_n[i] )/phi[i] ; // convergence check
        errorphimax = errorphi[0];       // start with max = first element
        for(size_t i = 1; i<n; i++)
        {
            if(errorphi[i] > errorphimax)
                errorphimax = errorphi[i]; //find max error amongst all elements of array and use that as error check
        }

//        cout << "SOR iteration error = " << errorphimax << "\t" << phi[0] << "\t" << phi_n[0]<< "\n" ;
//if(iteration==10)
//printf("\n10iteration=%i\t%e\n",iteration,errorphimax);
	}
//	cout << "SOR iteration error = \n" << errorphimax << "\t" << phi[0] << "\t" << phi_n[0]<< "\n" ;
//	cout << "\nSOR iterations = \n" <<  iteration << "\n";

//    for ( int i = 0 ; i < n ; i++ )
//            printf("\nphi in sor=%e\n",phi[i]);
    delete []phi_n;
	delete []errorphi;
	return phi[0];
}


// Temperature dependent variables and functions


double gspatial(double z, double opt, double lambda, double R1, double Iplus0,
                double Iplus1)
{
// z must be normalized by the coating thickness
  double gs ;
  gs =  Iplus0 * exp( -z / lambda );
  gs += R1 * Iplus1 * exp( ( z - 1 ) / lambda );
  gs *= (1. / opt) ;

  if( z<=1)
    return gs;
  else if (z>1)
    return 0;

  return 0;
  }







void solveMatrix(const int n, const std::vector<double>& b,
                 const std::vector<double>& d,
                 const std::vector<double>& a,
                 const std::vector<double>& C,
                 std::vector<double>& u)
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


    for (int i = 1 ; i < n  ; i++)
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

    for (int i = n - 2; i >= 0; i--)
    {
        u[i]  = u[i+1];
        u[i] *= -a[i];
        u[i] += Cw[i];
        u[i] /= dw[i];
    }

  delete[] dw;
  delete[] Cw;

  return;
}





double gs_int(const double eta, const double opt, const double lambda,
              const double R1, const double Iplus0,
              const double Iplus1)
{
    // z must be normalized by the coating thickness
    if ( eta > 1 )
    {
        return 0;
    }
    else if( eta <= 1 )
    {
        double gs = eta;
        gs -= 1;
        gs /= lambda;
        gs = exp(gs);
        gs *= Iplus1;
        gs *= R1 ;
        gs -= Iplus0 *  exp( -eta / lambda );
        gs *= lambda;
        gs /= opt;
        return gs;
    }

    return -1;
}
