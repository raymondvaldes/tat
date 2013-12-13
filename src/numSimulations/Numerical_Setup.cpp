#include "../Header.h"


double x_limiter1(const double xi)
{
    return exp(xi);
}

double x_limiter2(const double xi, const double x_min, const double x_max)
{    
  // converts value from k-space to x_space. In k-space the parameter is free
  // to be any value.  In x-space the parameter is constrained between x_min
  // and x_max.

  double
  x = x_max;
  x -= x_min;
  x /= 1 + exp(xi);
  x += x_min;

  if(x > x_max || x < x_min)
  {
    std::cout << "\nerror!! in x_limiter2" << x << "\t" << x_min;
    std::cout << "\t" << x_max << "\n";
  }

  return x;
}

double kx_limiter1(const double ki)
{
    //converts value to k-space
//    assert(ki > 0);

    return log(ki);
}

double kx_limiter2(const double ki,const double k_min,const double k_max)
{
//    std::cout << "\n\n"<< x_min <<"\t" <<  xi<< "\t" << x_max << "\n\n";
//    std::cout << (xi > x_min) << "\n";
//    std::cout << (xi < x_max) << "\n\n";
//    assert(ki > k_min  && ki < k_max);

    return log( ( (k_max - k_min) / (ki - k_min) ) - 1.);
}


void scaleDiag(const int mode, const size_t N, double * diag,
               const class thermalAnalysisMethod::PopTea poptea )
{
    if(mode == 2)
    {
        for(size_t i = 0; i < N; ++i)
        {
            switch ( poptea.xParametersNames[i] )
            {
                case asub :
                    diag[i] = poptea.TBCsystem.a_sub;
                    break;
                case E1 :
                    diag[i] = poptea.TBCsystem.optical.Emit1;
                    break;
                case gammaEff :
                    diag[i] = poptea.TBCsystem.gamma ;
                    break;
                case R1 :
                    diag[i] = poptea.TBCsystem.optical.R1 ;
                    break;
                case lambda :
                diag[i] = poptea.TBCsystem.coating.lambda;
                    break;
                case R0 :
                    diag[i] = poptea.TBCsystem.optical.R0;
                    break;
                default:
                    std::cout << "\nSwitch Error!!\n";
                    exit(-69);
                    break;
            }
        }
    }
    return;
}

size_t xINTrandom(const size_t xmin, const size_t xmax)
{
    std::mt19937 gen;
    gen.seed(std::time(NULL)+rand());

    std::uniform_int_distribution<> distribution(xmin,xmax);
    return distribution(gen);
}


double x_normal(const double Xmean, const double Xstddev, const double seed1)
{
//    std::default_random_engine gen;
    std::mt19937 gen;
    gen.seed(seed1);

    std::normal_distribution<double> distribution(Xmean,Xstddev);
    return distribution(gen);
}

double x_normal(const double Xmean, const double Xstddev)
{
//    std::default_random_engine gen;
    std::mt19937 gen;
    gen.seed(std::time(NULL)+rand());

    std::normal_distribution<double> distribution(Xmean,Xstddev);
    return distribution(gen);
}

double x_bias(const double Xmean, const double Xstddev)
{
    double xguess = x_normal(Xmean,Xstddev);

    while(xguess<Xmean)
    {
        xguess = x_normal(Xmean,Xstddev);
    }

    return xguess;
}

double x_ini(const double x_min, const double x_max, const size_t position,
             const size_t gN)
{
/*
    Creates a random parameter between two open bounds
    x_min = minimum value
    x_max = maximum value

    In addition, the number will be in a "low", "high" group depending on the gN
    value.  Example:
        gN = 2 would create two groups of "low" and "high".
        gN = 3 would create three groups of "low", "medium", "high" etc.
    The position will depend on the 'position' argument.
*/

    if(position  <= 0 || position  > gN)
    {
        exit(-99);
    }

    double xini = x_min;
    xini += (x_max - x_min) * ( ( position-1 ) / gN ) ;

    double xminNew = xini;
    double xmaxNew = x_max;
    xmaxNew -= (x_max - x_min) * ( ( position-1 ) / gN );

    while (equalto(xini, xminNew) || equalto(xini, xmaxNew) )
    {
        std::mt19937 gen;
        gen.seed(std::time(NULL)+rand());
        std::uniform_real_distribution<> dis(xminNew, xmaxNew);
        xini = dis(gen);
    }

    return xini;
}

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

void cosfit(double **dependent, const double *independent, double *x, int j,
            double omega1, int Nend)
{
    constexpr size_t N = 3; // number  of constants to be fitted
    const size_t P = Nend-1; //number of datapoints to be used in the fitting process
    constexpr double ftol = 1.e-13;
    constexpr double xtol = 1.e-13;
    constexpr double gtol = 1.e-13;
    constexpr int maxfev = 1e8;
    constexpr double epsfcn = 1.e-13;
    constexpr double factor = .01;
    constexpr int mode = 1;
    constexpr int nprint = 0;

///Transform input into offset, amplitude, phase
    /*
    The offset is limited to positive values.
    The amplitude if limited to positive values.  This is accomplished
    by reparameterization (Bates and Watts, 1988). See pg 163 Englezos
    (applied parameter estimation)
    ex. k_i = exp(kappa_i)

    By conducting our search over kappa regardless of its value, exp(kappa)
    and hence k is always positive.

    The phase is bounded from -pi to +pi.
    */
    x[0] = kx_limiter1(x[0]);
    x[1] = kx_limiter1(x[1]);
    x[2] = kx_limiter2(x[2], -M_PI, M_PI );

///Fitting in kappa space
    /*
    loop is run for each time
    newdependent is the temperature data
    newindependent sets B and B to corresponding values (time)
    */
    {
        double *fjac = new double[P*N];
        double *wa5 = new double[P*N];

        double *fvec = new double[P];
        double *wa4 = new double[P];
        double *newdependent = new double[P];//dependent array for fits
        double *newindependent = new double[P]; //independent array for fits

        double *qtf     = new double[N];
        double *wa1     = new double[N];
        double *wa2     = new double[N];
        double *wa3     = new double[N];
        double *diag    = new double[N];
        int *ipvt       = new int[N];

        int nfev;
        int info=0;

        for (size_t g = 0; g <P; g++)
        {
            newdependent[g]   = dependent[g][j];
            newindependent[g] = g*(independent[1]-independent[0]);
        }

        double *variables[3];
        for(size_t a=0; a<=2 ; ++a)
            variables[a]=new double [P];

        for(size_t g = 0; g <P; g++)
        {
            variables[0][g] =   newdependent[g];
            variables[1][g] =   newindependent[g];
        }
        variables[2][0]=omega1;

        lmdif(&cosfcn,P,N,x,fvec,variables,ftol,xtol,gtol,maxfev,epsfcn,diag,
              mode,factor,nprint,&info,&nfev,fjac,P,ipvt,qtf,wa1,wa2,wa3,wa4,
              wa5);

        ///Clean Up
        for(size_t a=0; a<=2 ; ++a)
        {
            delete[] variables[a];
        }
        delete [] fvec;    delete [] qtf;
        delete [] wa1;     delete [] wa2;
        delete [] wa3;     delete [] wa4;
        delete [] fjac;    delete [] wa5;
        delete [] ipvt;    delete [] diag;

        delete [] newdependent;
        delete [] newindependent;
    }

///Transform output back to offset, amplitude, phase
    x[0] = x_limiter1(x[0]);
    x[1] = x_limiter1(x[1]);
    x[2] = x_limiter2(x[2],-M_PI,M_PI);

    return;
}

void cosfit(double *dependent,const std::vector<double> &independentVec,
            double *x, int Nend)
{
///Must replace const double *independent by vector.  However, will create a
///new object replace back in.

  double*independent = new double[Nend];
  for(int i=0 ; i< Nend; ++i)
  {
      independent[i] = independentVec[i];
  }


    constexpr size_t N = 3; // number  of constants to be fitted
    const size_t P = Nend-1;
    //number of datapoints to be used in the fitting process
    constexpr double ftol = 1.e-10;
    constexpr double xtol = 1.e-10;
    constexpr double gtol = 1.e-10;
    constexpr int maxfev = 1e8;
    constexpr double epsfcn = 1.e-12;
    constexpr double factor = 1;
    constexpr int mode = 1;
    constexpr int nprint = 0;

///Transform input into offset, amplitude, phase
    /*
    The offset is limited to positive values.
    The amplitude if limited to positive values.  This is accomplished
    by reparameterization (Bates and Watts, 1988). See pg 163 Englezos
    (applied parameter estimation)
    ex. k_i = exp(kappa_i)

    By conducting our search over kappa regardless of its value, exp(kappa)
    and hence k is always positive.

    The phase is bounded from -pi to +pi.
    */
    x[0] = kx_limiter1(x[0]);
    x[1] = kx_limiter1(x[1]);
    x[2] = kx_limiter2(x[2], -M_PI, M_PI );

///Fitting in kappa space
    /*
    loop is run for each time
    newdependent is the temperature data
    newindependent sets B and B to corresponding values (time)
    */
    {
        double *fjac = new double[P*N];
        double *wa5 = new double[P*N];

        double *fvec = new double[P];
        double *wa4 = new double[P];
        double *newdependent = new double[P];//dependent array for fits
        double *newindependent = new double[P]; //independent array for fits

        double *qtf     = new double[N];
        double *wa1     = new double[N];
        double *wa2     = new double[N];
        double *wa3     = new double[N];
        double *diag    = new double[N];
        int *ipvt       = new int[N];

        int nfev;
        int info=0;

        for (size_t g = 0; g <P; g++)
        {
            newdependent[g]   = dependent[g];
            newindependent[g] = g*(independent[1]-independent[0]);
        }
        delete[] independent;


        double *variables[3];
        for(size_t a=0; a<=2 ; ++a)
            variables[a]=new double [P];

        for(size_t g = 0; g <P; g++)
        {
            variables[0][g] =   newdependent[g];
            variables[1][g] =   newindependent[g];
        }
        variables[2][0]=0;

        lmdif(&cosfcn1,P,N,x,fvec,variables,ftol,xtol,gtol,maxfev,epsfcn,diag,
              mode,factor,nprint,&info,&nfev,fjac,P,ipvt,qtf,wa1,wa2,wa3,wa4,
              wa5);

        ///Clean Up
        for(size_t a=0; a<=2 ; ++a)
        {
            delete[] variables[a];
        }
        delete [] fvec;    delete [] qtf;
        delete [] wa1;      delete [] wa2;
        delete [] wa3;     delete [] wa4;
        delete [] fjac;    delete [] wa5;
        delete [] ipvt;     delete [] diag;

        delete [] newdependent;
        delete [] newindependent;
    }

///Transform output back to offset, amplitude, phase
    x[0] = x_limiter1(x[0]);
    x[1] = x_limiter1(x[1]);
    x[2] = x_limiter2(x[2],-M_PI,M_PI);

    return;
}

void minimizer(double (*to_minimize)(double *,double *), double *variable,
               double *constants, double temp_variable_min,
               double temp_variable_max, double min_goal,
               const size_t max_iterations)
{
    double fraction = 0;
    double *temp_to_minimize = new double [max_iterations];

    size_t while_j=0;
    int best_minimum_element = 0;
    variable[0] = temp_variable_min;
    temp_to_minimize[best_minimum_element] = min_goal*10;

    while(temp_to_minimize[best_minimum_element]>=min_goal &&
          while_j<max_iterations)
    {
        fraction = pow(10,-1*double (while_j));
        variable[0] = temp_variable_min+fraction;
        temp_to_minimize[0] = to_minimize(variable,constants);
        for(size_t for_j=1 ; for_j <= max_iterations ; for_j++ )
        {
            variable[0]+=fraction;
            temp_to_minimize[for_j]=to_minimize(variable,constants);
            if(fabs(temp_to_minimize[for_j])>=fabs(temp_to_minimize[for_j-1]) ||
               variable[0]>   temp_variable_max)
            {
                variable[0]-=fraction;
                best_minimum_element=for_j-1;
                break;
            }
        }
        while_j+=1;
    }
    variable[0]+=fraction;
    temp_to_minimize[best_minimum_element+1]=to_minimize(variable,constants);
    variable[0]-=fraction;


    delete []temp_to_minimize;
    return;
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





size_t discretizeSpace(const int nodes,const double beta1,const double beta2,
                       const double split, double *z_norm, double *z_real,
                       const double L_coat,const double L_substrate, double*eta,
                       double* zNorm2)
{
    const double L1 = 1; //coating nondimensional thickness
                    //z transformed to eta from 0-L_coat  to 0-1.
	const double L2 = 1; //substrate ....Do not change these parameters.
    const double M2 = nodes;

    size_t M1 = split * (M2-1);

// define eta (computational grid)
    for(size_t j = 0; j <= M1 ; j++)
        eta[j] =  (double (j) / double (M1)) * L1;
    for(size_t j = 1 ; j <= (M2-1) - M1 ; j ++)
        eta[M1+j] = ( double ( j ) / ( double (M2-1) - double (M1) ) ) * L2 + eta[M1];

    for ( size_t j = 0 ; j < M2; j++ )
       z_norm[j] = z_eta( eta[j], beta1,  beta2) ;

    for (size_t j = 0 ; j < M2 ; j++)
    {
        if ( j <= M1) z_real[j] = z_norm[j] * L_coat;
//        if ( j == M1 || j == M1) z_real[j] = L_coat;
        if ( j > M1 && j < M2)  z_real[j] = (z_norm[j] - 1) * L_substrate + L_coat;
    }

    for(size_t i = 0 ; i < M2 ; i++)
    {
        if(i <= M1)
        {
            zNorm2[i] = z_norm[i];
        }
        else if(i > M1)
        {
            zNorm2[i] = (L_substrate/L_coat) * ( z_norm[i] - 1 ) + 1;
        }
    }

    return M1;
}



void cosfcn(int P,int /*N*/,double *x,double *fvec,int */*iflag*/,
            double **variables)
{  // function to be fitted:
   // dependent[i] = x[0]+x[1]*cos(independent[i]*omega+x[2])
   // constants to be found by the fit are: x[0],x[1],x[2] which respectively
   // are offset, amplitude, phase

    double *dependent = new double[P];
    double *independent = new double[P];
    for(int i=0;i<P;i++)
    {
        dependent[i] = variables[0][i];
        independent[i] = variables[1][i];
    }

    double omega = variables[2][0];

    for( int g=0 ; g<P ; ++g )
    {
        fvec[g] = cos( independent[g] * omega + x_limiter2(x[2], -M_PI, M_PI) );
        fvec[g] *= x_limiter1(x[1]);
        fvec[g] += x_limiter1(x[0]);

        fvec[g] *= -1;
        fvec[g] += dependent[g];
    }

    delete [] dependent;
    delete [] independent;

    return;
}

void cosfcn1(int P,int /*N*/,double *x,double *fvec,int */*iflag*/, double **variables)
{  // function to be fitted:
   // dependent[i] = x[0]+x[1]*cos(independent[i]*2*PI+x[2])
   // constants to be found by the fit are: x[0],x[1],x[2] which respectively
   // are offset, amplitude, phase

    double *dependent = new double[P];
    double *independent = new double[P];
    for(int i=0;i<P;i++)
    {
        dependent[i] = variables[0][i];
        independent[i] = variables[1][i];
    }

    for( int g=0 ; g<P ; ++g )
    {
        fvec[g] = cos(independent[g] * 2 * M_PI + x_limiter2(x[2], -M_PI, M_PI) );
        fvec[g] *= x_limiter1(x[1]);
        fvec[g] += x_limiter1(x[0]);

        fvec[g] *= -1;
        fvec[g] += dependent[g];
    }

    delete [] dependent;
    delete [] independent;

    return;
}
double simpson_3_8(const double *Y, const double *X, const size_t A,
                   const size_t B)
{
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
                   const size_t A,const size_t B)
{
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

double simpson_3_8(const double *Y, const std::vector<double>& X,
                   const size_t A,const size_t B)
{
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
                                        const size_t A,const size_t B)
{
    const double
    sumReal = ::simpson_3_8(YReal, X, A, B);

    const double
    sumImag = ::simpson_3_8(YCPLX, X, A, B);

    ///Cleanup
    const std::complex<double> sum (sumReal,sumImag);

    return sum;
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

double omega(const double L_coat, const double l_thermal, const double k_c,
             const double psi_c)
{
    return ( k_c / psi_c ) / ( pow(L_coat * l_thermal,2) );
}

double lthermal(const double L_coat, const double k_c, const double psi_c,
                const double omega)
{
    double lthermal = k_c;
    lthermal /= psi_c*omega;
    lthermal = sqrt(lthermal);
    lthermal /= L_coat;

    return lthermal;
}

double average(const double a, const double b)
{
    return (a+b)*.5;
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

double x_ini10(const int x_ref)
{
    return x_ini10(double(x_ref));
}
double x_ini10(const double x_ref)
{
/*
    Creates a random parameter between two open bounds
    x_ref*.9 = minimum value
    x_ref*1.1 = minimum value
*/
    const double percent = .1;
    return x_ini(x_ref*(1-percent), x_ref*(1+percent));
}



double x_ini(const double x_min, const double x_max)
{
/*
    Creates a random parameter between two open bounds
    x_min = minimum value
    x_max = maximum value
*/
    double xini = x_min ;
    while (equalto(xini,x_min) || equalto(xini,x_max))
    {
        std::mt19937 gen;
        gen.seed(std::time(NULL)+rand());
        std::uniform_real_distribution<> dis(x_min, x_max);
        xini = dis(gen);
    }

    return xini;
}

double percentile(const double xmin, const double xmax, const double x)
{
    /*
    This function returns the percentile of x in log10 space with respect to the
    x_min to x_max range.
    */

    if( x > xmax || x < xmin)
    {
        std::cout << "\noutside range linear\n";
        exit(-99);
    }

    return x / (xmax-xmin);
}

double percentilelog10(const double xmin, const double xmax, const double x)
{
    /*
    This function returns the percentile of x in log10 space with respect to the
    x_min to x_max range.
    */

    constexpr double epsilon = 1e-12;
    if( ( (x-epsilon) > xmax) || ( (x+epsilon) < xmin ) )
    {
        std::cout << "\n" << xmin << "\t" << xmax << "\t" << x << "\t"
        << (x > xmax) << "\t" << (x < xmin) << "\n";

        std::cout << "\noutside range logspace\n";
        exit(-99);
    }


    return (log10(x) - log10(xmin)) / (log10(xmax) - log10(xmin));
}


void range(double* l_thermal, const double l_min, const double l_max,
           const size_t L_end)
{
    for(size_t i = 0 ; i <  L_end; ++i)
    {
        l_thermal[i] = ( l_max - l_min ) * ( double(i) / ( L_end - 1 ) );
    }
}

void range(std::vector<double>& l_thermal, const double l_min,
           const double l_max, const size_t L_end)
{
  for(size_t i = 0 ; i <  L_end; ++i)
  {
    l_thermal[i] = (l_max-l_min)*(double(i)/(L_end-1));
  }
}

void range1og10(const double l_min, const double l_max, const size_t L_end,
                std::vector<double> &l_thermal)
{
  BOOST_ASSERT_MSG( L_end >= 1 , "check inputs \n\n" );
  BOOST_ASSERT_MSG( l_min < l_max , "check inputs \n\n" );
  BOOST_ASSERT_MSG( l_min > 0 , "check inputs \n\n" );

  if (L_end == 1)
  {
    l_thermal[0] = l_min;
  }
  else if(L_end == 2)
  {
    l_thermal[0] = l_min;
    l_thermal[L_end-1] = l_max;
  }
  else if(L_end > 2)
  {
    const double start1 = log10(l_min * 10);
    const double end1   = log10(l_max * 10);
    const double increments = (end1 - start1) / (L_end -1);
    double rangeI = start1;

    for(size_t n = 0 ; n < L_end-1 ; ++n )
    {
        l_thermal[n] = pow(10, rangeI - 1);
        rangeI += increments;
    }
    l_thermal[L_end-1] = l_max;
  }
}

void range1og10(const double l_min, const double l_max, const size_t L_end,
                double* l_thermal)
{
    /*
    Creates a closed logarithmic distribution from l_min to l_max.
    log base 10
    */
    if( (L_end < 1) || (l_min > l_max) || (equalto(l_min,l_max))
        || (l_min <= 0))
    {
        std::cout << "\nerror in range1og10()";
        exit(-69);
    }

    if (L_end == 1)
    {
        l_thermal[0] = l_min;
    }
    else if(L_end == 2)
    {
        l_thermal[0] = l_min;
        l_thermal[L_end-1] = l_max;
    }
    else if(L_end > 2)
    {
        const double start1 = log10(l_min * 10);
        const double end1   = log10(l_max * 10);
        const double increments = (end1 - start1) / (L_end -1);
        double rangeI = start1;

        for(size_t n = 0 ; n < L_end-1 ; ++n )
        {
            l_thermal[n] = pow(10, rangeI - 1);
            rangeI += increments;
        }
        l_thermal[L_end-1] = l_max;
    }
}

perturbStruct::perturbStruct(const size_t a, const size_t b, const double c)
                             : pNum(a), xnumber(b), spread(c)
{
    xArea = new double[a];
    temp = new double[xnumber * pNum];
}

perturbStruct::perturbStruct(const size_t a, const size_t b, const double c,
                              const double e, const double h,
                             const size_t i)
                             : pNum(a), xnumber(b), spread(c),
                             lmin1(e), lmax2(h), iterates(i)
{
    temp = new double[xnumber * pNum];
    xArea = new double[a];
}

void perturbStruct::lThermalMC()
{
    lmin = new double[iterates];
    lmax = new double[iterates];

    for(size_t i = 0; i <=  iterates ; ++i)
    {
        lmin[i] = 0;
        lmax[i] = 0;

        if(i == 0)
        {
            lmin[i] = lminRef;
            lmax[i] = lmaxRef;
        }

        while (lmin[i] >= lmax[i])
        {
            lmin[i]  = ::x_ini(lmin1, lmin2);
            lmax[i]  = ::x_ini(lmax1, lmax2);
        }
    }
}

void perturbStruct::lthermalDeterministic()
{
    const size_t iteratesO = iterates-1;
    lmin = new double[iteratesO];
    lmax = new double[iteratesO];
    double*A1t = new double[iteratesO];
    double*B2t = new double[iteratesO];

    const double C1 = (lmax2 - lmax1) / (lmin2 - lmin1);

    size_t A1 = sqrt(iterates / C1);
    size_t B1 = C1 * A1;

    lmin[0] = lminRef;
    lmax[0] = lmaxRef;

    size_t counter = 1;
    while(counter <= iteratesO)
    {
        counter = 1;
        iterates = B1 * A1;
        ::range1og10(lmin1, lmin2, A1, A1t);
        ::range1og10(lmax1, lmax2, B1, B2t);

        for(size_t i = 0; i < A1 ; i++)
        {
            for(size_t j = 0 ; j < B1 ; j++)
            {
                if (A1t[i] < B2t[j])
                {
                    counter++;
                }
            }
        }

        if(counter%2 == 0)
        {
            A1++;
        }
        else
        {
            B1++;
        }
    }

    while(counter > iteratesO)
    {
        if(B1 >= A1)
        {
            --B1;
        }
        else if (A1 >= B1)
        {
            --A1;
        }

        counter = 1;
        iterates = B1 * A1;
        ::range1og10(lmin1, lmin2, A1, A1t);
        ::range1og10(lmax1, lmax2, B1, B2t);
        for(size_t i = 0; i < A1 ; i++)
        {
            for(size_t j = 0 ; j < B1 ; j++)
            {
                if (A1t[i] < B2t[j])
                {
                    counter++;
                }
            }
        }
    }

    counter = 1;
    for(size_t i = 0; i < A1 ; i++)
    {
        for(size_t j = 0 ; j < B1 ; j++)
        {
            if (A1t[i] < B2t[j])
            {
                lmin[counter] = A1t[i];
                lmax[counter] = B2t[j];
                counter++;
            }
        }
    }
    iterates = counter;

    delete[] A1t;
    delete[] B2t;
}


void perturbStruct::lthermalBands(const double PtolBand1)
{
    PtolBand = PtolBand1;
    const size_t Npoints = 1 / (PtolBand/2) + 1;
    bands = new double[Npoints];

    double *thermalRange = new double[Npoints];

    ::range1og10(lmin1, lmax2, Npoints, thermalRange);

    lmin = new double[Npoints/2+1];
    lmax = new double[Npoints/2+1];

    iterates = 0;
    for(size_t i = 1; i <= Npoints/2 ; i++)
    {
        if( PtolBand*i >= .2 )
        {
            bands[iterates] = PtolBand*(i) ;
            lmin[iterates] = thermalRange [ size_t(floor( Npoints / 2 )-i)];
            lmax[iterates] = thermalRange [ size_t(floor( Npoints / 2 )+i)];
            iterates++;
        }
    }


    delete[] thermalRange;
}

void perturbStruct::cleanup()
{
    delete[] xArea;
    delete[] temp;

}

void perturbStruct::cleanup2()
{
    cleanup();
    delete[] lmin;
    delete[] lmax;
    delete[] bands;
}
