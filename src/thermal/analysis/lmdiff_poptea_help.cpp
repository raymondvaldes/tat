/*----------------------------------------------------------------------------*\
  ========                |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||                   |
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

#include <boost/foreach.hpp>
#include "thermal/analysis/lmdiff_poptea_help.hpp"
#include "thermal/analysis/kernal.hpp"
#include "thermal/emission/phase99.hpp"
#include "math/estimation/lmdiff.hpp"
#include "math/estimation/lmdiff_helper.hpp"
#include "math/estimation/constrained.hpp"
#include "math/statistical_tools.hpp"


namespace thermal {
namespace analysis{

#ifndef __USEWXLOG__
#define PRINT printf
#else
#include <wx/log.h>
#define PRINT wxLogMessage
#endif

#define BUG 0
/* resolution of arithmetic */
double MACHEP = 1.2e-16;
extern double MACHEP;
/* smallest nonzero number */
double DWARF = 1.0e-38;
extern double DWARF;


void fdjac2(std::function<void( double*, double*,
                                class thermal::analysis::Kernal&)> fcn,
            int m, int n, double x[], double fvec[], double fjac[], int ldfjac,
            int *iflag, double epsfcn, double wa[],
            class thermal::analysis::Kernal &popteaCore);


void lmdif(std::function<void( double*, double*,
                              class thermal::analysis::Kernal&)> fcn,
           int m, int n, double *x, double *fvec,double ftol, double xtol,
           double gtol, int maxfev, double epsfcn, double *diag, int mode,
           double factor, int nprint, int *info, int *nfev, double *fjac,
           int ldfjac, int *ipvt, double *qtf, double *wa1, double *wa2,
           double *wa3, double *wa4, double */*wa5*/,
           class thermal::analysis::Kernal &popteaCore)
{
/*
*     **********
*
*     subroutine lmdif
*
*     the purpose of lmdif is to minimize the sum of the squares of
*     m nonlinear functions in n variables by a modification of
*     the levenberg-marquardt algorithm. the user must provide a
*     subroutine which calculates the functions. the jacobian is
*     then calculated by a forward-difference approximation.
*
*     the subroutine statement is
*
*	subroutine lmdif(fcn,m,n,x,fvec,ftol,xtol,gtol,maxfev,epsfcn,
*			 diag,mode,factor,nprint,info,nfev,fjac,
*			 ldfjac,ipvt,qtf,wa1,wa2,wa3,wa4)
*
*     where
*
*	fcn is the name of the user-supplied subroutine which
*	  calculates the functions. fcn must be declared
*	  in an external statement in the user calling
*	  program, and should be written as follows.
*
*	  subroutine fcn(m,n,x,fvec,iflag)
*	  integer m,n,iflag
*	  double precision x(n),fvec(m)
*	  ----------
*	  calculate the functions at x and
*	  return this vector in fvec.
*	  ----------
*	  return
*	  end
*
*	  the value of iflag should not be changed by fcn unless
*	  the user wants to terminate execution of lmdif.
*	  in this case set iflag to a negative integer.
*
*	m is a positive integer input variable set to the number
*	  of functions.
*
*	n is a positive integer input variable set to the number
*	  of variables. n must not exceed m.
*
*	x is an array of length n. on input x must contain
*	  an initial estimate of the solution vector. on output x
*	  contains the final estimate of the solution vector.
*
*	fvec is an output array of length m which contains
*	  the functions evaluated at the output x.
*
*	ftol is a nonnegative input variable. termination
*	  occurs when both the actual and predicted relative
*	  reductions in the sum of squares are at most ftol.
*	  therefore, ftol measures the relative error desired
*	  in the sum of squares.
*
*	xtol is a nonnegative input variable. termination
*	  occurs when the relative error between two consecutive
*	  iterates is at most xtol. therefore, xtol measures the
*	  relative error desired in the approximate solution.
*
*	gtol is a nonnegative input variable. termination
*	  occurs when the cosine of the angle between fvec and
*	  any column of the jacobian is at most gtol in absolute
*	  value. therefore, gtol measures the orthogonality
*	  desired between the function vector and the columns
*	  of the jacobian.
*
*	maxfev is a positive integer input variable. termination
*	  occurs when the number of calls to fcn is at least
*	  maxfev by the end of an iteration.
*
*	epsfcn is an input variable used in determining a suitable
*	  step length for the forward-difference approximation. this
*	  approximation assumes that the relative errors in the
*	  functions are of the order of epsfcn. if epsfcn is less
*	  than the machine precision, it is assumed that the relative
*	  errors in the functions are of the order of the machine
*	  precision.
*
*	diag is an array of length n. if mode = 1 (see
*	  below), diag is internally set. if mode = 2, diag
*	  must contain positive entries that serve as
*	  multiplicative scale factors for the variables.
*
*	mode is an integer input variable. if mode = 1, the
*	  variables will be scaled internally. if mode = 2,
*	  the scaling is specified by the input diag. other
*	  values of mode are equivalent to mode = 1.
*
*	factor is a positive input variable used in determining the
*	  initial step bound. this bound is set to the product of
*	  factor and the euclidean norm of diag*x if nonzero, or else
*	  to factor itself. in most cases factor should lie in the
*	  interval (.1,100.). 100. is a generally recommended value.
*
*	nprint is an integer input variable that enables controlled
*	  printing of iterates if it is positive. in this case,
*	  fcn is called with iflag = 0 at the beginning of the first
*	  iteration and every nprint iterations thereafter and
*	  immediately prior to return, with x and fvec available
*	  for printing. if nprint is not positive, no special calls
*	  of fcn with iflag = 0 are made.
*
*	info is an integer output variable. if the user has
*	  terminated execution, info is set to the (negative)
*	  value of iflag. see description of fcn. otherwise,
*	  info is set as follows.
*
*	  info = 0  improper input parameters.
*
*	  info = 1  both actual and predicted relative reductions
*		    in the sum of squares are at most ftol.
*
*	  info = 2  relative error between two consecutive iterates
*		    is at most xtol.
*
*	  info = 3  conditions for info = 1 and info = 2 both hold.
*
*	  info = 4  the cosine of the angle between fvec and any
*		    column of the jacobian is at most gtol in
*		    absolute value.
*
*	  info = 5  number of calls to fcn has reached or
*		    exceeded maxfev.
*
*	  info = 6  ftol is too small. no further reduction in
*		    the sum of squares is possible.
*
*	  info = 7  xtol is too small. no further improvement in
*		    the approximate solution x is possible.
*
*	  info = 8  gtol is too small. fvec is orthogonal to the
*		    columns of the jacobian to machine precision.
*
*	nfev is an integer output variable set to the number of
*	  calls to fcn.
*
*	fjac is an output m by n array. the upper n by n submatrix
*	  of fjac contains an upper triangular matrix r with
*	  diagonal elements of nonincreasing magnitude such that
*
*		 t     t	   t
*		p *(jac *jac)*p = r *r,
*
*	  where p is a permutation matrix and jac is the final
*	  calculated jacobian. column j of p is column ipvt(j)
*	  (see below) of the identity matrix. the lower trapezoidal
*	  part of fjac contains information generated during
*	  the computation of r.
*
*	ldfjac is a positive integer input variable not less than m
*	  which specifies the leading dimension of the array fjac.
*
*	ipvt is an integer output array of length n. ipvt
*	  defines a permutation matrix p such that jac*p = q*r,
*	  where jac is the final calculated jacobian, q is
*	  orthogonal (not stored), and r is upper triangular
*	  with diagonal elements of nonincreasing magnitude.
*	  column j of p is column ipvt(j) of the identity matrix.
*
*	qtf is an output array of length n which contains
*	  the first n elements of the vector (q transpose)*fvec.
*
*	wa1, wa2, and wa3 are work arrays of length n.
*
*	wa4 is a work array of length m.
*
*     subprograms called
*
*	user-supplied ...... fcn
*
*	minpack-supplied ... dpmpar,enorm,fdjac2,lmpar,qrfac
*
*	fortran-supplied ... dabs,dmax1,dmin1,dsqrt,mod
*
*     argonne national laboratory. minpack project. march 1980.
*     burton s. garbow, kenneth e. hillstrom, jorge j. more
*
*     **********
*/
using namespace math::estimation;



int iter = 0;
int i,iflag,ij,jj,j,l;
double actred,delta,dirder,fnorm,fnorm1,gnorm;
double par,pnorm,prered,ratio;
double sum,temp,temp1,temp2,temp3,xnorm;
static double one = 1.0;
static double p1 = 0.1;
static double p5 = 0.5;
static double p25 = 0.25;
static double p75 = 0.75;
static double p0001 = 1.0e-4;
static double zero = 0.0;
/* static double p05 = 0.05; */

*info = 0;
iflag = 0;
*nfev = 0;
delta = 0.0;
xnorm = 0.0;
/*
*     check the input parameters for errors.
*/
if( (n <= 0) || (m < n) || (ldfjac < m) || (ftol < zero)
  || (xtol < zero) || (gtol < zero) || (maxfev <= 0)
  || (factor <= zero) )
  goto L300;



if( mode == 2 )
  { /* scaling by diag[] */
  for( j=0; j<n; j++ )
    {
    if( diag[j] <= 0.0 )
      goto L300;
    }
  }

#if BUG
PRINT( "lmdif\n" );
#endif
/*
*     evaluate the function at the starting point
*     and calculate its norm.
*/
iflag = 1;

fcn(x,fvec,popteaCore);

//popteaCore.LMA.LMA_workspace.MSEinitial = popteaCore.LMA.LMA_workspace.MSE;

*nfev = 1;
if(iflag < 0)
  goto L300;
fnorm = enorm(m,fvec);
/*
*     initialize levenberg-marquardt parameter and iteration counter.
*/
par = zero;
iter = 1;
/*
*     beginning of the outer loop.
*/

L30:

/*
*	 calculate the jacobian matrix.
*/
iflag = 2;

////////////////////////////////////////////////////////////////////////////////////
thermal::analysis::fdjac2(fcn, m, n, x, fvec, fjac, ldfjac, &iflag, epsfcn, wa4, popteaCore);

////Store a forward difference jacobian
//ij = 0;
//for(j = 0 ; j < n ; ++j)
//        for(i = 0 ; i < m ; ++i)
//    {
//            wa5[ij] = fjac[ij];    //  fjac[i+m*j]
//            popteaCore.LMA.LMA_workspace.fjac[ij] = wa5[ij] ;
//            ij++;
//    }
////////////////////////////////////////////////////////////////////////////////////

//exit(-99);

*nfev += n;
if(iflag < 0)
  goto L300;
/*
*	 if requested, call fcn to enable printing of iterates.
*/
if( nprint > 0 )
  {
  iflag = 0;
  if(mod(iter-1,nprint) == 0)
    {
    fcn(x,fvec,popteaCore);
    if(iflag < 0)
      goto L300;
//z		PRINT("\n   fnorm %.15e\n", enorm(m,fvec) );
    }
  }
/*
*	 compute the qr factorization of the jacobian.
*/
qrfac(m,n,fjac,ldfjac,true,ipvt,n,wa1,wa2,wa3);
/*
*	 on the first iteration and if mode is 1, scale according
*	 to the norms of the columns of the initial jacobian.
*/
if(iter == 1)
  {
  if(mode != 2)
    {
    for( j=0; j<n; j++ )
      {
      diag[j] = wa2[j];
      if( wa2[j] == zero )
        diag[j] = one;
      }
    }

/*
*	 on the first iteration, calculate the norm of the scaled x
*	 and initialize the step bound delta.
*/
  for( j=0; j<n; j++ )
    wa3[j] = diag[j] * x[j];

  xnorm = enorm(n,wa3);
  delta = factor*xnorm;
  if(delta == zero)
    delta = factor;
  }
/*
*	 form (q transpose)*fvec and store the first n components in
*	 qtf.
*/
for( i=0; i<m; i++ )
  wa4[i] = fvec[i];
jj = 0;
for( j=0; j<n; j++ )
  {
  temp3 = fjac[jj];
  if(temp3 != zero)
    {
    sum = zero;
    ij = jj;
    for( i=j; i<m; i++ )
      {
      sum += fjac[ij] * wa4[i];
      ij += 1;	/* fjac[i+m*j] */
      }
    temp = -sum / temp3;
    ij = jj;
    for( i=j; i<m; i++ )
      {
      wa4[i] += fjac[ij] * temp;
      ij += 1;	/* fjac[i+m*j] */
      }
    }
  fjac[jj] = wa1[j];
  jj += m+1;	/* fjac[j+m*j] */
  qtf[j] = wa4[j];
  }

/*
*	 compute the norm of the scaled gradient.
*/
 gnorm = zero;
 if(fnorm != zero)
        {
        jj = 0;
        for( j=0; j<n; j++ )
                {
                l = ipvt[j];
                if(wa2[l] != zero)
                        {
                        sum = zero;
                        ij = jj;
                        for( i=0; i<=j; i++ )
                                {
                                sum += fjac[ij]*(qtf[i]/fnorm);
                                ij += 1; /* fjac[i+m*j] */
                                }
                        gnorm = dmax1(gnorm,fabs(sum/wa2[l]));
                        }
                jj += m;
                }
        }

/*
*	 test for convergence of the gradient norm.
*/
 if(gnorm <= gtol)
        *info = 4;
 if( *info != 0)
        goto L300;
/*
*	 rescale if necessary.
*/
 if(mode != 2)
        {
        for( j=0; j<n; j++ )
                diag[j] = dmax1(diag[j],wa2[j]);
        }

/*
*	 beginning of the inner loop.
*/
L200:
/*
*	    determine the levenberg-marquardt parameter.
*/
lmpar(n,fjac,ldfjac,ipvt,diag,qtf,delta,&par,wa1,wa2,wa3,wa4);
/*
*	    store the direction p and x + p. calculate the norm of p.
*/
for( j=0; j<n; j++ )
        {
       wa1[j] = -wa1[j];
       wa2[j] = x[j] + wa1[j];
       wa3[j] = diag[j]*wa1[j];
        }
pnorm = enorm(n,wa3);
/*
*	    on the first iteration, adjust the initial step bound.
*/
if(iter == 1)
        delta = dmin1(delta,pnorm);
/*
*	    evaluate the function at x + p and calculate its norm.
*/
iflag = 1;
fcn( wa2, wa4, popteaCore ) ;




*nfev += 1;
if(iflag < 0)
  goto L300;
fnorm1 = enorm(m,wa4);
#if BUG
PRINT( "pnorm %.10e  fnorm1 %.10e\n", pnorm, fnorm1 );
#endif
/*
*	    compute the scaled actual reduction.
*/
actred = -one;
if( (p1*fnorm1) < fnorm)
  {
  temp = fnorm1/fnorm;
  actred = one - temp * temp;
  }
/*
*	    compute the scaled predicted reduction and
*	    the scaled directional derivative.
*/
jj = 0;
for( j=0; j<n; j++ )
  {
  wa3[j] = zero;
  l = ipvt[j];
  temp = wa1[l];
  ij = jj;
  for( i=0; i<=j; i++ )
    {
    wa3[i] += fjac[ij]*temp;
    ij += 1; /* fjac[i+m*j] */
    }
  jj += m;
  }
temp1 = enorm(n,wa3)/fnorm;
temp2 = (sqrt(par)*pnorm)/fnorm;
prered = temp1*temp1 + (temp2*temp2)/p5;
dirder = -(temp1*temp1 + temp2*temp2);
/*
*	    compute the ratio of the actual to the predicted
*	    reduction.
*/
ratio = zero;
if(prered != zero)
  ratio = actred/prered;
/*
*	    update the step bound.
*/
if(ratio <= p25)
  {
  if(actred >= zero)
    temp = p5;
  else
    temp = p5*dirder/(dirder + p5*actred);
  if( ((p1*fnorm1) >= fnorm)
  || (temp < p1) )
    temp = p1;
       delta = temp*dmin1(delta,pnorm/p1);
       par = par/temp;
        }
else
  {
  if( (par == zero) || (ratio >= p75) )
    {
    delta = pnorm/p5;
    par = p5*par;
    }
  }
/*
*	    test for successful iteration.
*/
if(ratio >= p0001)
  {
/*
*	    successful iteration. update x, fvec, and their norms.
*/
  for( j=0; j<n; j++ )
    {
    x[j] = wa2[j];
    wa2[j] = diag[j]*x[j];
    }
  for( i=0; i<m; i++ )
    fvec[i] = wa4[i];
  xnorm = enorm(n,wa2);
  fnorm = fnorm1;
  iter += 1;
  }
/*
*	    tests for convergence.
*/
if( (fabs(actred) <= ftol)
  && (prered <= ftol)
  && (p5*ratio <= one) )
        *info = 1;
if(delta <= xtol*xnorm)
        *info = 2;
if( (fabs(actred) <= ftol)
  && (prered <= ftol)
  && (p5*ratio <= one)
  && ( *info == 2) )
        *info = 3;
if( *info != 0)
        goto L300;
/*
*	    tests for termination and stringent tolerances.
*/
if( *nfev >= maxfev)
        *info = 5;
if( (fabs(actred) <= MACHEP)
  && (prered <= MACHEP)
  && (p5*ratio <= one) )
        *info = 6;
if(delta <= MACHEP*xnorm)
        *info = 7;
if(gnorm <= MACHEP)
        *info = 8;
if( *info != 0)
        goto L300;
/*
*	    end of the inner loop. repeat if iteration unsuccessful.
*/
if(ratio < p0001)
        goto L200;
/*
*	 end of the outer loop.
*/
goto L30;

L300:
/*
*     termination, either normal or user imposed.
*/
if(iflag < 0)
        *info = iflag;
iflag = 0;
if(nprint > 0)
        fcn( x, fvec, popteaCore ) ;
/*
      last card of subroutine lmdif.
*/

}

void fdjac2(std::function<void( double*, double*,
                                class thermal::analysis::Kernal&)> fcn,
            int m, int n, double x[], double fvec[], double fjac[], int ldfjac,
            int *iflag, double epsfcn, double wa[],
            class thermal::analysis::Kernal &popteaCore)
{
/*
*     **********
*
*     subroutine fdjac2
*
*     this subroutine computes a forward-difference approximation
*     to the m by n jacobian matrix associated with a specified
*     problem of m functions in n variables.
*
*     the subroutine statement is
*
*	subroutine fdjac2(fcn,m,n,x,fvec,fjac,ldfjac,iflag,epsfcn,wa)
*
*     where
*
*	fcn is the name of the user-supplied subroutine which
*	  calculates the functions. fcn must be declared
*	  in an external statement in the user calling
*	  program, and should be written as follows.
*
*	  subroutine fcn(m,n,x,fvec,iflag)
*	  integer m,n,iflag
*	  double precision x(n),fvec(m)
*	  ----------
*	  calculate the functions at x and
*	  return this vector in fvec.
*	  ----------
*	  return
*	  end
*
*	  the value of iflag should not be changed by fcn unless
*	  the user wants to terminate execution of fdjac2.
*	  in this case set iflag to a negative integer.
*
*	m is a positive integer input variable set to the number
*	  of functions.
*
*	n is a positive integer input variable set to the number
*	  of variables. n must not exceed m.
*
*	x is an input array of length n.
*
*	fvec is an input array of length m which must contain the
*	  functions evaluated at x.
*
*	fjac is an output m by n array which contains the
*	  approximation to the jacobian matrix evaluated at x.
*
*	ldfjac is a positive integer input variable not less than m
*	  which specifies the leading dimension of the array fjac.
*
*	iflag is an integer variable which can be used to terminate
*	  the execution of fdjac2. see description of fcn.
*
*	epsfcn is an input variable used in determining a suitable
*	  step length for the forward-difference approximation. this
*	  approximation assumes that the relative errors in the
*	  functions are of the order of epsfcn. if epsfcn is less
*	  than the machine precision, it is assumed that the relative
*	  errors in the functions are of the order of the machine
*	  precision.
*
*	wa is a work array of length m.
*
*     subprograms called
*
*	user-supplied ...... fcn
*
*	minpack-supplied ... dpmpar
*
*	fortran-supplied ... dabs,dmax1,dsqrt
*
*     argonne national laboratory. minpack project. march 1980.
*     burton s. garbow, kenneth e. hillstrom, jorge j. more
*
      **********
*/
using namespace math::estimation;

int i,j,ij;
double eps,h,temp;
static double zero = 0.0;
extern double MACHEP;

temp = dmax1(epsfcn,MACHEP);
eps = sqrt(temp);
#if BUG
PRINT( "fdjac2\n" );
#endif
ij = 0;


for( j=0; j<n; j++ )
  {
  temp = x[j];
  h = eps * fabs(temp);
  if(h == zero)
    h = eps;
  x[j] = temp + h;

  fcn( x, wa, popteaCore ) ;

  if( *iflag < 0)
    return;

  x[j] = temp;
  for( i=0; i<m; i++ )
    {
    fjac[ij] = (wa[i] - fvec[i])/h;
    ij += 1;	/* fjac[i+m*j] */
    }
  }
#if BUG
pmat( m, n, fjac );
#endif
/*
*     last card of subroutine fdjac2.
*/
}


void scaleDiag( double *diag, class math::estimation::unknownList List,
                const physicalModel::TBCsystem TBCsystem, const int mode )
{
  if( mode == 2 )
  {
    int i = 0;

    for( const class math::estimation::unknown &unknown : List() )
    {
      diag[i++] = TBCsystem.returnVal( unknown.label() );
    }
  }
}



LMA_workingArrays::LMA_workingArrays(const size_t Lend_, const size_t N_)
{
  updateArraySize( Lend_, N_ );
}

void LMA_workingArrays::updateArraySize( const size_t Lend_, const size_t N )
{
  /*Lend_ is the total number of unique measurements in a dataset,
  this value is based on the range and the set minimum*/

  fjac.resize(Lend_* N );
//  emissionExperimental.resize(Lend_);

  fvec.resize(Lend_);

}

LMA_workingArrays::~LMA_workingArrays(void)
{}


}
}
