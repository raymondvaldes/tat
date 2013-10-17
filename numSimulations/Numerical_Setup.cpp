#include "../Header.h"


double x_limiter1(const double xi)
{
    return exp(xi);
}

double x_limiter2(const double xi, const double x_min, const double x_max)
{
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
    return log(ki);
}

double kx_limiter2(const double ki,const double k_min,const double k_max)
{
    return log( ( (k_max - k_min) / (ki - k_min) ) - 1.);
}

int paramter_estimation(const size_t m,const size_t n, double ftol, double xtol,
                        double gtol, int maxfev, double epsfcn, int mode,
                        double factor, int nprint, int *info, int *nfev,
                        const struct parameter_constraints *pc_ptr, double *x,
                        struct parameterStr * pStruct,
                        const double factorMax, const double factorScale,
                        double *xpredicted)
{
/*
    The parameter estimation function takes in the function, fitting parameters,
    initial guess.  If no initial guess is given then it will populate an
    initial guess based on a random distribution of the parameter range. The
    initial guess is then transformed based on the parameter estimation ranges.
    The parameter estimation employed is the levenberg-marquardt algorithm(LMA).
    The the objective function is evaluated and compared against a tolerance.
    If it is larger than the tolerance than a new initial guess will be
    initialized.  This process is repeated until the objective function
    satisfies the tolerance or the number of iterations maxes out. The final
    values are populated back into the parameter structure and the dependent
    parameters are updated.
*/
    double *fvec = new double[m];
    double *qtf = new double[n];
    double *wa1 = new double[n];
    double *wa2 = new double[n];
    double *wa3 = new double[n];
    double *wa4 = new double[m];
    double *fjac = new double[m*n];
    double *wa5 = new double[m*n];
    int *ipvt = new int[n];
    double *diag = new double[n];

    scaleDiag(mode, n, diag, pStruct );

    double *xinitial = new double[n];
    double *xguess = new double[n];

    for(size_t i=0 ; i< n ; i++)
    {
        xinitial[i] = x[i];
    }

    for(size_t iter = 0; iter < pStruct->iterPE; iter++ )
    {
        ///set initial guesses
        if ( x[0] == 0 )
        {
            for(size_t i=0 ; i<n ; ++i)
            {
                switch ( pStruct->xParametersNames[i] )
                {
                    case asub :
                        x[i] = x_ini(pc_ptr->a_sub_min, pc_ptr->a_sub_max);
                        break;
                    case E1 :
                        x[i] = x_ini(pc_ptr->E_sigma_min, pc_ptr->E_sigma_max);
                        break;
                    case gammaEff :
                        x[i] = x_ini(pc_ptr->gamma_min, pc_ptr->gamma_max);
                        break;
                    case R1 :
                        x[i] = x_ini(pc_ptr->R1_min, pc_ptr->R1_max);
                        break;
                    case lambda :
                        x[i] = x_ini(pc_ptr->lambda_min, pc_ptr->lambda_max);
                        break;
                    case R0 :
                        x[i] = x_ini(pc_ptr->R0_min, pc_ptr->R0_max);
                        break;
                    default:
                        std::cout << "\nSwitch Error!!\n";
                        exit(-69);
                        break;
                }
            }
        }

        for(size_t i=0; i< n; i++)
        {
            xguess[i] = x[i];
        }

        ///Transform inputs
        for(size_t i=0 ; i< n ; i++)
        {
            switch ( pStruct->xParametersNames[i] )
            {
                case asub :
                    x[i] = kx_limiter2(x[i],pc_ptr->a_sub_min,pc_ptr->a_sub_max);
                    break;
                case E1 :
                    x[i] = kx_limiter2(x[i],pc_ptr->E_sigma_min,pc_ptr->E_sigma_max);
                    break;
                case gammaEff :
                    x[i] = kx_limiter2(x[i], pc_ptr->gamma_min, pc_ptr->gamma_max);
                    break;
                case R1 :
                    x[i] = kx_limiter2(x[i],pc_ptr->R1_min,pc_ptr->R1_max);
                    break;
                case lambda :
                    x[i] = kx_limiter2(x[i],pc_ptr->lambda_min,pc_ptr->lambda_max);
                    break;
                case R0 :
                    x[i] = kx_limiter2(x[i],pc_ptr->R0_min,pc_ptr->R0_max);
                    break;
                default:
                    std::cout << "\nSwitch Error!!\n";
                    exit(-69);
                    break;
            }
        }

        ///levenberg-marquardt algorithm
        lmdif(&ThermalProp_Analysis, m, n, x, fvec, ftol, xtol, gtol,
              maxfev, epsfcn, diag, mode, factor, nprint, info, nfev, fjac, m, ipvt,
              qtf, wa1, wa2, wa3, wa4, wa5, pc_ptr,pStruct);

        ///Exit Routine
    /*
        Sets up a condition where the total error in the phase is compared
        against a fvec Tolerance.  If the error is greater than this constant,
        then the parameter estimation algorithm is reset with a new set of
        initial guesses. This is let to run a fixed number of iterations.
    */
        constexpr double ExpStddev = 0;
        const double ExpVarianceEst = ExpStddev * ExpStddev;
        pStruct->fvecTotal = SobjectiveLS(pStruct->L_end,
                                          pStruct->emissionExperimental,
                                          pStruct-> predicted);
        const size_t v1 = pStruct->L_end - n;
        double reduceChiSquare;

        if(ExpVarianceEst ==0 )
        {
            reduceChiSquare = 100;
        }
        else
        {
            reduceChiSquare = (pStruct->fvecTotal / ExpVarianceEst) / v1;
        }

        if( reduceChiSquare < 2
           || factor == factorMax
           || pStruct->fvecTotal < pStruct->MSETol
           )
        {

            const bool
            condition1 = reduceChiSquare < 2;
            const bool
            condition2 = factor == factorMax;
            const bool
            condition3 = pStruct->fvecTotal < pStruct->MSETol;

//            std::cout <<  "\nexit with     "
//            << condition1 << "\t" << condition2
//            << "\t" << condition3 <<"\n";
//
//            std::cout << "\n"<<reduceChiSquare << "\t" << pStruct->fvecTotal
//            << "\t" << pStruct->MSETol << "\t" << factor << "\n";

            ///Transform outputs
            for(size_t i=0 ; i< n ; i++)
            {
                switch ( pStruct->xParametersNames[i] )
                {
                    case asub :
                        pStruct->a_sub =
                        x_limiter2(x[i], pc_ptr->a_sub_min, pc_ptr->a_sub_max);
                        xpredicted[i] = pStruct->a_sub;
                        break;

                    case E1 :
                        pStruct->E_sigma =
                        x_limiter2(x[i], pc_ptr->E_sigma_min,
                                   pc_ptr->E_sigma_max);
                        xpredicted[i] = pStruct->E_sigma;
                        break;

                    case gammaEff :
                        pStruct->gamma =
                        x_limiter2(x[i], pc_ptr->gamma_min, pc_ptr->gamma_max);
                        xpredicted[i] = pStruct->gamma;
                        break;

                    case R1 :
                        pStruct->R1 =
                        x_limiter2(x[i], pc_ptr->R1_min, pc_ptr->R1_max);
                        xpredicted[i] = pStruct->R1;
                        break;

                    case lambda :
                        pStruct->lambda =
                        x_limiter2(x[i], pc_ptr->lambda_min,
                                   pc_ptr->lambda_max);
                        xpredicted[i] = pStruct->lambda;
                        break;

                    case R0 :
                        pStruct->R0 =
                        x_limiter2(x[i], pc_ptr->R0_min, pc_ptr->R0_max);
                        xpredicted[i] = pStruct->R0;
                        break;

                    default:
                        std::cout << "\nSwitch Error!!\n";
                        exit(-69);
                        break;
                }
            }

            parameters_update(pStruct, n);
            pStruct->iterPEnum = iter;

            phase99(pStruct->L_end, pStruct, pStruct->predicted);


            delete [] qtf;
            delete [] wa1;
            delete [] wa2;
            delete [] wa3;
            delete [] wa4;
            delete [] wa5;
            delete [] ipvt;
            delete [] fvec;
            delete [] fjac;
            delete [] diag;

            delete [] xinitial;
            delete [] xguess;
            return *info;

        }

        else if (factor <= factorMax/factorScale)
        {
            factor *=factorScale;
//            std::cout << "factor increased to "  << factor <<"\n";

        }
        else if (factor > factorMax/factorScale && factor < factorMax)
        {
            factor = factorMax;
            std::cout << "factor increased max "  << factor <<"\n";
        }

        for(size_t i=0 ; i< n ; i++)
        {
            x[i] = xinitial[i];
        }
    }

    std::cout << "\n";
    for(size_t i = 0 ; i < pStruct->L_end; ++i)
    {
        std::cout << i <<"\t" <<pStruct->predicted[i] << "\n";
    }
    exit(-2);


    delete [] qtf;
    delete [] wa1;
    delete [] wa2;
    delete [] wa3;
    delete [] wa4;
    delete [] wa5;
    delete [] ipvt;
    delete [] fvec;
    delete [] fjac;
    delete [] diag;

    delete [] xinitial;
    delete [] xguess;

    return *info;
}

void scaleDiag(const int mode, const size_t N, double * diag,
               const struct parameterStr * pStruct )
{
    if(mode == 2)
    {
        for(size_t i = 0; i < N; ++i)
        {
            switch ( pStruct->xParametersNames[i] )
            {
                case asub :
                    diag[i] = pStruct->a_sub;;
                    break;
                case E1 :
                    diag[i] = pStruct->E_sigma;
                    break;
                case gammaEff :
                    diag[i] = pStruct->gamma;
                    break;
                case R1 :
                    diag[i] = pStruct->R1 ;
                    break;
                case lambda :
                    diag[i] = pStruct->lambda;
                    break;
                case R0 :
                    diag[i] = pStruct->R0;
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

void parameters_update(struct parameterStr * pStruct,const size_t N)
{
    for(size_t i=0 ; i< N ; ++i)
    {
        if( pStruct->xParametersNames[i] == asub ||
            pStruct->xParametersNames[i] == gammaEff)
            {
                parameters_kcp_update(pStruct, pStruct->gamma,
                                      pStruct->a_sub);
            }
//        else if( pStruct->xParametersNames[i] == k_c ||
//                 pStruct->xParametersNames[i] == psi_c)
//            {
//                parameters_agamma_update(pStruct,
//                                         pStruct->k1_thermal->offset,
//                                         pStruct->psi1_thermal->offset);
//            }
    }

  return;
}

void parameters_kcp_update(struct parameterStr* pStruct,
                           const double gamma, const double a_sub)
{
    pStruct->a_sub = a_sub;
    pStruct->gamma = gamma;

    pStruct->effusivity_coat  = pStruct->effusivity_sub;
    pStruct->effusivity_coat /= gamma;

    pStruct->diffusivity_coat = pStruct->diffusivity_sub ;
    pStruct->diffusivity_coat /= a_sub*a_sub;

    pStruct->psi1_thermal->offset = pStruct->effusivity_coat;
    pStruct->psi1_thermal->offset /= sqrt( pStruct->diffusivity_coat);

    pStruct->k1_thermal->offset = pStruct->psi1_thermal->offset;
    pStruct->k1_thermal->offset *= pStruct->diffusivity_coat;

    return;

}

void parameters_agamma_update(struct parameterStr* pStruct,
                              const double k_c, const double psi_c)
{
    pStruct->k1_thermal->offset = k_c;
    pStruct->psi1_thermal->offset = psi_c;

    pStruct->diffusivity_coat = k_c;
    pStruct->diffusivity_coat /= psi_c;

    pStruct->effusivity_coat = k_c;
    pStruct->effusivity_coat *= psi_c;
    pStruct->effusivity_coat = sqrt( pStruct->effusivity_coat );

    pStruct->gamma  = pStruct->effusivity_sub;
    pStruct->gamma /= pStruct->effusivity_coat ;

    pStruct->a_sub = pStruct->diffusivity_sub;
    pStruct->a_sub /= pStruct->diffusivity_coat;
    pStruct->a_sub = sqrt( pStruct->a_sub );

    return;
}

double SOR(double **A, double *b,const size_t n,double *phi, double omega, double error)
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


void cosfit(double *dependent, const double *independent, double *x, int Nend)
{
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


double gspatial(double z, double opt, double lambda, double R0,
                    double R1, double Iplus0, double Iplus1)
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
//       return gs * ( z <= 1 ? 1. : 0. ) ;
}


double beta2_func(double * variable, double * constants)
{
//    constants[0]=beta1;
//    constants[1]=M2;
//    constants[2]=L_substrate;
//    constants[3]=L_coat;
//    constants[4]=split;
    double a,b,c,d;
//    double eta[int(constants[1])];
    double *eta = new double[int(constants[1])];
    double L1 = 1; //coating nondimensional thickness
                    //z transformed to eta from 0-L_coat  to 0-1.
	double L2 = 1; //substrate ....Do not change these parameters.
    size_t M1 = constants[4] * (constants[1]-1);

    for(size_t j = 0; j <= M1 ; j++)
        eta[j] =  (double (j) / double (M1)) * L1;

    for(size_t j = 1 ; j < constants[1] - M1 ; j ++)
        eta[M1+j] = ( double ( j ) / ( double (constants[1]-1) - double (M1) ) )
         * L2 + eta[M1];

    a = (z_eta(eta[M1+1], constants[0], variable[0])-1.) * constants[2] +
    constants[3];
    b = z_eta(eta[M1], constants[0], variable[0]) * constants[3];
    c = z_eta(eta[M1-1], constants[0], variable[0]) * constants[3];
    d = fabs((a-b)-(b-c));
     //  the two delta_z's are to be the same, this is the error between them

    delete []eta;
    return d;
}

double find_beta2(const double beta1, const double M2,const double L_substrate,
                  const double L_coat,const double split)
{
    ////minimizer start (to find beta2)
    constexpr size_t beta_iter = {100};
    constexpr double beta_tol  = {1e-6};

    double variable;
    double constants[5] = {beta1, M2, L_substrate, L_coat, split};

    minimizer(&beta2_func, &variable, constants, 1., 15., beta_tol, beta_iter);

    return variable;
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

int discretize_1d(size_t nodes, size_t Nend, double beta1, double beta2, double split,
                  double *eta, double *z_norm, double *z_real,
                  double *time, double L_coat, double L_substrate, double *tau,
                  double omega, double k_c, double psi_c, double k_ref,
                  double psi_ref)
{
    double L1 = 1; //coating nondimensional thickness
                    //z transformed to eta from 0-L_coat  to 0-1.
	double L2 = 1; //substrate ....Do not change these parameters.
    double tau_ref = tau_0(omega);
    double M2 = nodes;
    double period = tau_ref;

    size_t M1 = split * (M2-1);

// Time
    for (size_t i = 0; i < Nend; i++)
     {
        time[i] = ((i)/double (Nend-1)) * period;
        tau[i] = time[i] / period ;
     }

// define eta (computational grid)
    for(size_t j = 0; j <= M1 ; j++)
        eta[j] =  (double (j) / double (M1)) * L1;
    for(size_t j = 1 ; j <= (M2-1) - M1 ; j ++)
        eta[M1+j] = ( double ( j ) / ( double (M2-1) - double (M1) ) ) *
         L2 + eta[M1];

    for ( size_t j = 0 ; j < M2; j++ )
       z_norm[j] = z_eta( eta[j], beta1,  beta2) ;

    for (size_t j = 0 ; j < M2 ; j++)
    {
        if ( j <= M1) z_real[j] = z_norm[j] * L_coat;
//        if ( j == M1 || j == M1) z_real[j] = L_coat;
        if ( j > M1 && j < M2)  z_real[j] = (z_norm[j] - 1.) * L_substrate + L_coat;
    }
    return M1;
}

void cosfcn(int P,int N,double *x,double *fvec,int *iflag, double **variables)
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

void cosfcn1(int P,int N,double *x,double *fvec,int *iflag, double **variables)
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

void solveMatrix(const int64_t n, const std::vector<double>& b,
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


//    for (int i = 1 ; i < n  ; ++i)
//    {
//        m1 = -b[i];
//        m1 /= dw[i-1];
//        dw[i] =  m1;
//        dw[i] *= a[i-1];
//        dw[i] += d[i];
//        Cw[i] =  m1;
//        Cw[i] *= Cw[i-1];
//        Cw[i] += C[i];
//    }
//    u[n-1] = Cw[n-1];
//    u[n-1] /= dw[n-1];
//
//    for (int i = n - 2; i >= 1; --i)
//    {
//        u[i]  = u[i+1];
//        u[i] *= -a[i];
//        u[i] += Cw[i];
//        u[i] /= dw[i];
//    }
//    constexpr int j = 0;
//    u[j]  = u[j+1];
//    u[j] *= -a[j];
//    u[j] += Cw[j];
//    u[j] /= dw[j];

    double*dw = new double[n];
    double*Cw = new double[n];

    Cw[0] = C[0];
    dw[0] = d[0];

    double m1;
    {
        const int i = 1;
        m1 = b[i] / d[i-1];
        dw[i] = d[i] - m1 * a[i-1];
        Cw[i] = C[i] - m1 * C[i-1];
    }

    for (int64_t i = 1 ; i+4 < n  ; i += 5)
    {
        m1 = -b[i];
        m1 /= dw[i-1];
        dw[i] =  m1;
        dw[i] *= a[i-1];
        dw[i] += d[i];
        Cw[i] =  m1;
        Cw[i] *= Cw[i-1];
        Cw[i] += C[i];

        m1 = -b[i+1];
        m1 /= dw[i];
        dw[i+1] =  m1;
        dw[i+1] *= a[i];
        dw[i+1] += d[i+1];
        Cw[i+1] =  m1;
        Cw[i+1] *= Cw[i];
        Cw[i+1] += C[i+1];

        m1 = -b[i+2];
        m1 /= dw[i+1];
        dw[i+2] = m1;
        dw[i+2] *= a[i+1];
        dw[i+2] += d[i+2];
        Cw[i+2] =  m1;
        Cw[i+2] *= Cw[i+1];
        Cw[i+2] += C[i+2];

        m1 = -b[i+3];
        m1 /= dw[i+2];
        dw[i+3] =  m1;
        dw[i+3] *= a[i+2];
        dw[i+3] += d[i+3];
        Cw[i+3] =  m1;
        Cw[i+3] *= Cw[i+2];
        Cw[i+3] += C[i+3];

        m1 = -b[i+4];
        m1 /= dw[i+3];
        dw[i+4] =  m1;
        dw[i+4] *= a[i+3];
        dw[i+4] += d[i+4];
        Cw[i+4] =  m1;
        Cw[i+4] *= Cw[i+3];
        Cw[i+4] += C[i+4];
    }

    u[n-1] = Cw[n-1];
    u[n-1] /= dw[n-1];

    for (int64_t i = n - 2; i >= 4; i= i-5)
    {
        u[i]  = u[i+1];
        u[i] *= -a[i];
        u[i] += Cw[i];
        u[i] /= dw[i];

        u[i-1]  = u[i];
        u[i-1] *= -a[i-1];
        u[i-1] += Cw[i-1];
        u[i-1] /= dw[i-1];

        u[i-2]  = u[i-1];
        u[i-2] *= -a[i-2];
        u[i-2] += Cw[i-2];
        u[i-2] /= dw[i-2];

        u[i-3]  = u[i-2];
        u[i-3] *= -a[i-3];
        u[i-3] += Cw[i-3];
        u[i-3] /= dw[i-3];

        u[i-4]  = u[i-3];
        u[i-4] *= -a[i-4];
        u[i-4] += Cw[i-4];
        u[i-4] /= dw[i-4];
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
              const double R0, const double R1, const double Iplus0,
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

Mesh::Mesh(const size_t M2_, const size_t Rend_, const size_t Nend_,
           const double beta1_, const double split_)
           :M2(M2_), Rend(Rend_), Nend(Nend_), beta1(beta1_), split(split_)
{
    time            = new double[Nend];
    tau             = new double[Nend];

    eta             = new double[M2];
    z_real          = new double[M2];
    z_norm          = new double[M2];
    zNorm2          = new double[M2];
    d_eta_plus      = new double[M2];
    deltaZ          = new double[M2];
    d_eta_minus     = new double[M2];

    rNorm2          = new double[Rend];
    rNorm           = new double[Rend];
    rZeta           = new double[Rend];
    rReal           = new double[Rend];

    z_jplus.resize(M2);
    z_jminus.resize(M2);
    z_j.resize(M2);

    for (size_t i = 0; i < Nend; ++i)
    {
        tau[i]  = double(i)/(Nend-1);
    }

    for (size_t i = 0; i < Rend; ++i)
    {
        rZeta[i] = double(i)/(Rend-1);
    }

}


void Mesh::cleanup(void)
{
    delete [] tau;
    delete [] time;

    delete [] eta;
    delete [] z_real;
    delete [] z_norm;
    delete [] zNorm2;
    delete [] d_eta_plus ;
    delete [] deltaZ     ;
    delete [] d_eta_minus;

    delete [] rNorm;
    delete [] rZeta;
    delete [] rNorm2;
    delete [] rReal;
}

double Mesh::beta2_func(double * variable, double * constants)
{
    double a,b,c,d;
    std::vector<double> eta_;
    eta_.resize(int(constants[1]));


//    double *eta_ = new double[int(constants[1])];
    double L1 = 1; //coating nondimensional thickness
                    //z transformed to eta from 0-L_coat  to 0-1.
    double L2 = 1; //substrate ....Do not change these parameters.
    size_t M1_ = constants[4] * (constants[1]-1);

    for(size_t j = 0; j <= M1_ ; j++)
        eta_[j] =  (double (j) / double (M1_)) * L1;

    for(size_t j = 1 ; j < constants[1] - M1_ ; j ++)
        eta_[M1_+j] = ( double ( j ) / ( double (constants[1]-1) -double(M1_)))
         * L2 + eta_[M1_];

    a = (z_eta(eta_[M1_+1], constants[0], variable[0])-1.) * constants[2] +
    constants[3];
    b = z_eta(eta_[M1_], constants[0], variable[0]) * constants[3];
    c = z_eta(eta_[M1_-1], constants[0], variable[0]) * constants[3];
    d = fabs( ( a - b ) - ( b - c ) );

//    delete[] eta_;
    return d;
}

void Mesh::minimizer(double *variable, double *constants,
                     double temp_variable_min, double temp_variable_max,
                     double min_goal, const size_t max_iterations)
{
    double fraction = 0;
//    double *temp_to_minimize = new double [max_iterations];

    size_t while_j=0;
    int best_minimum_element = 0;
    variable[0] = temp_variable_min;
//    temp_to_minimize[best_minimum_element] = min_goal*10;

    std::vector<double> temp_to_minimize;
    temp_to_minimize.resize(max_iterations+1);
    temp_to_minimize[best_minimum_element] = min_goal*10;


    while(temp_to_minimize[best_minimum_element]>=min_goal &&
          while_j<max_iterations)
    {
        fraction = pow(10,-1*double (while_j));
        variable[0] = temp_variable_min+fraction;
        temp_to_minimize[0] = beta2_func(variable,constants);

        for(size_t for_j=1 ; for_j <= max_iterations ; for_j++ )
        {
            variable[0]+=fraction;
            temp_to_minimize[for_j]= beta2_func(variable,constants);

            if(
               fabs(temp_to_minimize[for_j]) >=
               fabs(temp_to_minimize[for_j-1])
               ||
               variable[0] >   temp_variable_max)
            {
                variable[0]-=fraction;
                best_minimum_element=for_j-1;
                break;
            }
        }
        while_j+=1;

    }
    variable[0]+=fraction;
    temp_to_minimize[best_minimum_element+1]= beta2_func(variable,constants);
    variable[0]-=fraction;

//    delete []temp_to_minimize;

    return;
}

double Mesh::find_beta2(const double L_coat, const double L_substrate)
{
    ////minimizer start (to find beta2)
    constexpr size_t beta_iter = {100};
    constexpr double beta_tol  = {1e-6};
    double variable;
    double constants[5] = {beta1, double(M2), L_substrate, L_coat, split};

    minimizer(&variable, constants, 1.001, 15., beta_tol, beta_iter);


    return variable;
}

size_t Mesh::discretizeSpace(const double L_coat, const double L_substrate)
{
    constexpr double L1 = 1; //coating nondimensional thickness
                             //z transformed to eta from 0-L_coat  to 0-1.
    constexpr double L2 = 1; //substrate ....Do not change these parameters.

    const size_t M1_ = split * (M2-1);

// define eta (computational grid)
    for(size_t j = 0; j <= M1_ ; j++)
    {
        eta[j] =  double (j) / M1_ * L1;
    }

    for(size_t j = 1 ; j <= (M2-1) - M1_ ; j ++)
    {
        eta[M1_+j] = ( double ( j ) / (M2-1 -M1_ ) ) * L2;
        eta[M1_+j] += eta[M1_];
    }

    for ( size_t j = 0 ; j < M2; j++ )
    {
        z_norm[j] = z_eta( eta[j], beta1,  beta2) ;

        if ( j <= M1_)
        {
            z_real[j] = z_norm[j] * L_coat;
        }
        else if ( j > M1_ && j < M2)
        {
            z_real[j] = (z_norm[j] - 1) * L_substrate + L_coat;
        }

        if(j <= M1_)
        {
            zNorm2[j] = z_norm[j];
        }
        else if(j > M1_)
        {
            zNorm2[j] = (L_substrate/L_coat) * ( z_norm[j] - 1 ) + 1;
        }
    }


    return M1_;
}

double Mesh::z_eta(const double eta_)
{
    return z_eta(eta_, beta1, beta2);
}

double Mesh::z_eta(const double eta_, const double beta1_, const double beta2_)
{
    /* z_norm accounts for z_real after it has been normalized by L_coat
        and L_substrat double B;*/
    if (equalto(eta_,0))
    {
        return eta_;
    }

    else if (equalto(eta_,1))
    {
        return eta_;
    }

    else if (eta_ < 1)
    {
        const double B = ( beta1_ + 1) / (beta1_ - 1) ;
        return 1 + beta1_ - ( 2 * B * beta1_ ) / ( B + pow( B , eta_ ) ) ;
    }

    else if (eta_ > 1)
    {
        const double B = ( beta2_ + 1) / ( beta2_ - 1) ;
        return 2 + beta2_ - (2 * B * B * beta2_) / (B * B + pow( B , eta_));
    }

    return -1;
}

double Mesh::D_eta(const double z_norm_)
{
    //z_norm accounts for z_real after it has been normalized by
    //L_coat and L_substrate

    if (z_norm_ < 1 || equalto(z_norm_, 1))
    {
        const double B = ( beta1 + 1) / ( beta1 - 1) ;
        return ( -2 * beta1 ) /
        ( ( ( (-1 + z_norm_)*(-1 +z_norm_)) -(beta1*beta1) ) * ( log( B) ) ) ;
    }

    else if (z_norm_ > 1)
    {
        const double B = ( beta2 + 1) / ( beta2 - 1) ;
        return ( -2 * beta2 ) /
        ( ( ((-2 + z_norm_)*(-2 + z_norm_)) - (beta2*beta2) ) * ( log( B ) ) ) ;
    }

    return -1;
}

void Mesh::zUpdate()
{
    /*
    Attempted to autovectorize the for loop but was unable due to the
    conditional statements in the z_eta function. Splitting the loop into
    three loops did not help.
    */
    z_jplus[0] = z_eta( ::average(eta[1], eta[0]));
        z_j[0] = z_eta( eta[0]);

    const size_t endM2 = M2-1;
    for (size_t j = 1; j < endM2; j++)
    {
        z_jplus[j] = z_eta( ::average(eta[j+1], eta[j]) );
        z_jminus[j] = z_eta( ::average(eta[j-1], eta[j]) );
        z_j[j] =  z_eta( eta[j]);
    }

    z_jminus[M2-1] = z_eta( ::average(eta[M2-2], eta[M2-1]) );
         z_j[M2-1] = z_eta( eta[M2-1]);


    for(size_t j = 0; j==0; j++)
        d_eta_plus[j]  = D_eta( z_jplus[j] );
    for (size_t j = 1; j < M2-1 ; ++j)
    {
        d_eta_minus[j] = D_eta( z_jminus[j]);
        d_eta_plus[j]  = D_eta( z_jplus[j]);
        deltaZ[j] = z_jplus[j] - z_jminus[j];
    }

    {
        const size_t j = M2-1;
        d_eta_minus[j] = D_eta( z_jminus[j]);
        d_eta_plus[j]  = D_eta( z_j[j] ) ;
    }

    return;
}

void Mesh::meshUpdate(const double L_coat, const double L_substrate,
                      const double CO2Radius, const double Rdomain)
{
    beta2 = find_beta2(L_substrate, L_coat);
    M1 = discretizeSpace(L_coat, L_substrate);

    for (size_t i = 0; i < Rend; ++i)
    {
        rNorm[i] = rZeta[i] * ( Rdomain / CO2Radius ) ;
        rReal[i] = rNorm[i] * CO2Radius;
    }

    zUpdate();
}


Laser::Laser(const double a, const double b, const double c, const double d):
             offset(c), amplitude(d), Qlaser(a), radius(b)
{
    update();
}

void Laser::update(void)
{
    Is = IntensitySteady();
    It = IntensityTransient();
}

void Laser::updateRadius(const double r)
{
    radius = r;
    update();
}

void Laser::updatePower(const double Qpower)
{
    Qlaser = Qpower;
    update();
}

double Laser::area(void) const
{
    return M_PI_2 * radius * radius;
}

double Laser::IntensityTotal(void) const
{
    return Qlaser / area();
}

double Laser::IntensitySteady(void) const
{
    return IntensityTotal() * offset;
}

double Laser::IntensityTransient(void) const
{
    return IntensitySteady() * amplitude;
}

void Laser::updateNMeasurements()
{
    if(l_thermal)
    {
        delete [] l_thermal;
        delete [] omegas;
    }

    omegas      = new double[L_end];
    l_thermal   = new double[L_end];
}

double Laser::thermalSetup(const double lmin_, const double lmax_,
                           const double L_coat, const double kc,
                           const double psic, const double L_end_)
{
    l_min = lmin_;
    l_max = lmax_;
    /* I need to create a function that determines the number of measurements
    necessary to satisfy L_end_ which is the minimum  number of measurements per
    decade. Once I determine the number of measurements I need then I can use
    the ::rangelog10 function to populate the range.*/

    constexpr size_t box = 7;
    const double rangeLim[box] = {1e-3, 1e-2, 1e-1, 1e0, 1e1, 1e2, 1e3};

    /*check to verify inputs*/
    if(l_min < rangeLim[0] || l_max > rangeLim[box-1])
    {
        std::cout << "error in Laser::thermalSetup" << "\n";
        exit(-1);
    }

    double rangeFills[box-1] = {0};
    for(size_t i = 0; i < box-1 ; ++i)
    {
        if( l_min >= rangeLim[i+1]  || l_max <= rangeLim[i])
        {
            rangeFills[i] = 0;
        }
        else if( l_min <= rangeLim[i] && l_max >= rangeLim[i+1])
        {
            rangeFills[i] = 1;
        }
        else
        {
            double start = 0;
            if(l_min <= rangeLim[i])
            {
                start = 0;
            }
            else if( l_min < rangeLim[i+1] )
            {
                start = ::percentilelog10(rangeLim[i], rangeLim[i+1], l_min);
            }

            double end1 = 1;
            if(l_max >= rangeLim[i+1])
            {
                end1 = 1;
            }
            else if( l_max < rangeLim[i+1] )
            {
                end1 = ::percentilelog10(rangeLim[i], rangeLim[i+1], l_max);
            }

            rangeFills[i] = end1 - start;
        }
    }

    double sum = 0;
    for(size_t i = 0; i < box ; ++i)
    {
        sum += rangeFills[i];
    }

    if( sum > 1)
    {
        L_end = L_end_;
        L_end *=sum;
    }
    else if(sum <= 1)
    {
        L_end = L_end_;
    }

    updateNMeasurements();
    ::range1og10(l_min, l_max, L_end, l_thermal);

    for (size_t i=0; i < L_end; ++i )
    {
        omegas[i] = ::omega(L_coat, l_thermal[i], kc, psic);
    }

    return L_end;
}

void Laser::cleanup(void)
{
    delete [] l_thermal;
    delete [] omegas;
}


parameterStr::parameterStr(const size_t d,class Mesh *mesh_)
             :  mesh(mesh_), N(d)
{
    k1_thermal = new class property;
    psi1_thermal = new class property;
    k2_thermal = new class property;
    psi2_thermal = new class property;

    xParameters54       = new double[d];
    xParameters         = new size_t[d];
    xParameters95       = new size_t[d];
    xParametersNames   = new enum XParaNames[d];
    xParameters95Names = new enum XParaNames[d];

    N95 = d;

}

void parameterStr::updateNMeasurements(const size_t Lend_)
{
    /*Lend_ is the total number of unique measurements in a dataset,
    this value is based on the range and the set minimum*/
    if(fjac)
    {
        delete [] fjac;
        delete [] emissionExperimental;
        delete [] emissionNominal;
        delete [] predicted;
        delete [] fvec;
    }

    fjac = new double[Lend_*N];
    emissionExperimental    = new double[Lend_];
    emissionNominal         = new double[Lend_];
    predicted               = new double[Lend_];
    fvec = new double[Lend_];
}

void parameterStr::parametersStrSetup(const enum XParaNames *xParametersNames_)
{

    mesh->meshUpdate(L_coat, L_substrate, laser->radius, R_domain);
    update_b();

    /// Populate parameters array based on simulation parameters

     diffusivity_sub  = k2_thermal->offset;
     diffusivity_sub /= psi2_thermal->offset;

     effusivity_sub = k2_thermal->offset;
     effusivity_sub *= psi2_thermal->offset;
     effusivity_sub = sqrt( effusivity_sub);

     diffusivity_coat  = k1_thermal->offset;
     diffusivity_coat /= psi1_thermal->offset;

     effusivity_coat = k1_thermal->offset;
     effusivity_coat *= psi1_thermal->offset;
     effusivity_coat = sqrt( effusivity_coat);

     gamma  = effusivity_sub;
     gamma /= effusivity_coat;

     a_sub  =  diffusivity_sub;
     a_sub /=  diffusivity_coat;
     a_sub = sqrt( a_sub);

    for (size_t i=0; i < N; ++i)
    {
        xParametersNames[i] = xParametersNames_[i];
        xParameters95Names[i] = xParametersNames_[i];
    }

    return;
}


void parameterStr::thermalSetup(const double lmin_, const double lmax_,
                                const size_t LendMin)
{
    L_end = laser->thermalSetup(lmin_, lmax_, L_coat, k1_thermal->offset,
                                psi1_thermal->offset, LendMin);
    updateNMeasurements(L_end);
}

void parameterStr::update_b(const double radius, const double L)
{
    laser->updateRadius(radius);
    L_coat = L;
    bNorm = radius / L;
}

void parameterStr::update_b(void)
{
    update_b(laser->radius, L_coat);
}

void parameterStr::EmissionNoise(const double a, const double b, const bool d1,
                                 const bool d2, const int s1,
                                 const double noiseRandom,
                                 const double* emissionNominal_,
                                 const double lmin, const double lmax)
{
    /*
    a is the magnitude of the error at the edges of the range
    b is the stretching parameter that ranges from 1 < b < pi (use around 3)
    c is the location of the center and set it to 0.5.
    d is the orientation options
        d1    true (positive)
        d2    true (monotonically)

    This function needs an emissionProfile already established. This is the
    nominal emission profile used for the simulation.  The EXPERIMENTAL EMISSION
    is in the object (this) scope.

    This function needs l_thermal to be populated with the thermal
    penetration range.

    lmin and lmax are used to determine the nominal limits of the lthermal
    range.

    */
//        a = 0.025;
//        b = 3.05;
//        c = 0.5
//        d1 = 1 or 0;
//        d2 = 1 or 0

    if( (a < 0) || (b < 1) || (b > M_PI) )
    {
        std::cout << "parameters (a,b) out of range"; exit(-99);
    }


    for(size_t i=0 ; i < L_end; ++i)
    {
        constexpr double c = 0.5;

        double
        lthermalPercentile = ::percentilelog10(lmin, lmax, laser->l_thermal[i] );

        ///Determine biased noise
        const double cotbc = tan(M_PI_2 - ( b * c ) );
        double
        noiseBias = -a * cotbc * tan( b * ( c - lthermalPercentile ) );

        if(!d2)
        {
            noiseBias = fabs(noiseBias);
        }

        if(!d1)
        {
            noiseBias *= -1;
        }

        switch(s1)
        {
            case -1:
                if(lthermalPercentile > 0.5) {noiseBias = 0;}
                break;
            case 0:
                break;
            case 1:
                if(lthermalPercentile < 0.5) {noiseBias = 0;}
                break;
            default:
                std::cout << "\n\nerror in symmetry options\n\n"; exit(-1);
        }

        ///Determine random noise
        const double noiseRandomGen = x_normal(0, noiseRandom);

        emissionExperimental[i]  = emissionNominal_[i];
        emissionExperimental[i] += M_PI_2 * noiseBias;
        emissionExperimental[i] += M_PI_2 * noiseRandomGen;
    }
//
//    std::ofstream myfile;
//    std::stringstream filename;
//    filename <<  "data/emissionSimulated.dat";
//    myfile.open(filename.str().c_str());
//    myfile << std::setprecision(8);
//
//    for(size_t i = 0; i < laser->L_end; ++i)
//    {
//        myfile << laser->l_thermal[i] << "\t"
//        << emissionNominal_[i] << "\t"
//        << emissionExperimental[i] << "\n";
//    }
//    myfile.close();
}

void parameterStr::cleanup()
{
    delete [] fjac;
    delete [] emissionExperimental;
    delete [] emissionNominal;

    delete [] predicted;
    delete [] fvec;

    delete [] xParameters;
    delete [] xParameters95;

    delete [] xParameters54;
    delete [] xParametersNames;
    delete [] xParameters95Names;

    delete k1_thermal;
    delete psi1_thermal;
    delete k2_thermal;
    delete psi2_thermal;
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
