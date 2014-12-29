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
#include <boost/assert.hpp>
#include "math/numIntegration/simpsons_3_8.hpp"

namespace math{
  namespace numIntegration{

double simpson_3_8( const double *Y, const double *X, const size_t A,
                    const size_t B) noexcept
{
  BOOST_ASSERT( Y != nullptr ) ;
  BOOST_ASSERT( X != nullptr ) ;

    //A is lower limit element number, B is upper limit element number
    //calculates integral of Y dX from X[A] to X[B] using Y[n][i]
    double S = 0;
    size_t i = A;

    if( ( B - A ) % 3 == 1 )
    {
        S  = X[i+3];
        S -= X[i];
        S /= 8;
        S *= Y[i] + 3*Y[i+1] + 3*Y[i+2] + Y[i+3];
        S -= ( X[i+3]-X[i+1] )/6 * ( Y[i+1] + 4*Y[i+2] + Y[i+3] );
        i += 1;
    }

    if( ( B - A) % 3 == 2 )
    {
        S  = ( X[i+3] - X[i] ) / 8 * ( Y[i] + 3 * Y[i+1] + 3 * Y[i+2] + Y[i+3]);
        S -= ( X[i+3] - X[i+1]) / 6 *( Y[i+1] + 4 * Y[i+2] + Y[i+3] ) ;
        i += 1;
        S += ( X[i+3] - X[i]) / 8 * ( Y[i] + 3 * Y[i+1] + 3 * Y[i+2] + Y[i+3] ) ;
        S -= ( X[i+3] - X[i+1] ) / 6 * ( Y[i+1] + 4*Y[i+2] + Y[i+3] );
        i += 1;
    }

    while( i+3 <= B )
    {
        double
        sum = Y[i] ;
        sum += 3 * Y[i+1];
        sum += 3 * Y[i+2];
        sum += Y[i+3];

        double
        sum1 = X[i+3];
        sum1 -= X[i];
        sum1 /= 8;

        S += sum1 * sum;
        i += 3;
    }

    return S;
}

double simpson_3_8(const std::vector<double>& Y, const double *X,
                   const size_t A,const size_t B) noexcept
{
  BOOST_ASSERT( X != nullptr ) ;

    //A is lower limit element number, B is upper limit element number
    //calculates integral of Y dX from X[A] to X[B] using Y[n][i]
    double S = 0;
    size_t i = A;

    if( (B-A)%3==1)
    {
        S  = X[i+3] - X[i];
        S /= 8.;
        S *= (Y[i]+3.*Y[i+1]+3.*Y[i+2]+Y[i+3]);
        S -= (X[i+3]-X[i+1])/6.*(Y[i+1]+4.*Y[i+2]+Y[i+3]);
        i+=1;
    }

    if((B-A)%3==2)
    {
        S=(X[i+3]-X[i])/8.*(Y[i]+3.*Y[i+1]+3.*Y[i+2]+Y[i+3]);
        S-=(X[i+3]-X[i+1])/6.*(Y[i+1]+4.*Y[i+2]+Y[i+3]);
        i+=1;
        S+=(X[i+3]-X[i])/8.*(Y[i]+3.*Y[i+1]+3.*Y[i+2]+Y[i+3]);
        S-=(X[i+3]-X[i+1])/6.*(Y[i+1]+4.*Y[i+2]+Y[i+3]);
        i+=1;
    }

    while(i+3.<=B)
    {
        S+=(X[i+3]-X[i])/8.*(Y[i]+3.*Y[i+1]+3.*Y[i+2]+Y[i+3]);
        i+=3;
    }

    return S;
}

double simpson_3_8( const double *Y, const std::vector<double>& X,
                    const size_t A, const size_t B ) noexcept
{
  BOOST_ASSERT( Y != nullptr ) ;

    //A is lower limit element number, B is upper limit element number
    //calculates integral of Y dX from X[A] to X[B] using Y[n][i]
    double S = 0;
    size_t i = A;

    if( (B-A)%3==1)
    {
        S  = X[i+3] - X[i];
        S /= 8.;
        S *= (Y[i]+3.*Y[i+1]+3.*Y[i+2]+Y[i+3]);
        S -= (X[i+3]-X[i+1])/6.*(Y[i+1]+4.*Y[i+2]+Y[i+3]);
        i+=1;
    }

    if((B-A)%3==2)
    {
        S=(X[i+3]-X[i])/8.*(Y[i]+3.*Y[i+1]+3.*Y[i+2]+Y[i+3]);
        S-=(X[i+3]-X[i+1])/6.*(Y[i+1]+4.*Y[i+2]+Y[i+3]);
        i+=1;
        S+=(X[i+3]-X[i])/8.*(Y[i]+3.*Y[i+1]+3.*Y[i+2]+Y[i+3]);
        S-=(X[i+3]-X[i+1])/6.*(Y[i+1]+4.*Y[i+2]+Y[i+3]);
        i+=1;
    }

    while(i+3.<=B)
    {
        S+=(X[i+3]-X[i])/8.*(Y[i]+3.*Y[i+1]+3.*Y[i+2]+Y[i+3]);
        i+=3;
    }

    return S;
}

std::complex<double> simpson_3_8Complex(const double* YReal,
                                        const double* YCPLX,
                                        const double* X,
                                        const size_t A,const size_t B) noexcept
{
    const double
    sumReal = simpson_3_8(YReal, X, A, B);

    const double
    sumImag = simpson_3_8(YCPLX, X, A, B);

    ///Cleanup
    const std::complex<double> sum (sumReal,sumImag);

    return sum;
}






  }
}
