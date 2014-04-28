/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
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

#include "math/solvers/sor.h"
#include <cmath>

namespace math{namespace solvers{

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

        using std::abs;
        for (size_t i=0;i<n;i++)
          errorphi[i] = abs( phi[i] - phi_n[i] )/phi[i] ; // convergence check
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

}}