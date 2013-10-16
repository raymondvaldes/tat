#ifndef NUMERICAL_SETUP_H_INCLUDED
#define NUMERICAL_SETUP_H_INCLUDED
int paramter_estimation(const size_t m, const size_t  n, double ftol,
                        double xtol, double gtol,
                        int maxfev, double epsfcn, int mode,
                        double factor, int nprint, int *info, int *nfev,
                        const struct parameter_constraints *pc_ptr,
                        double *x,
                        struct parameterStr * parametersStr,
                        const double factorMax, const double factorScale,
                        double *xpredicted);

void parameters_update(struct parameterStr * parametersStr, const size_t N);

void fdjac2(void (*fcn)(int, int, double *, double *, int *,
                        const struct parameter_constraints*,
                        struct parameterStr * parametersStr),
            int m,int n,double x[],double fvec[], double fjac[],int ldfjac,
            int *iflag,double epsfcn,double wa[],
            const struct parameter_constraints*st_ptr,
            struct parameterStr * parametersStr);

double kthermalProj(const std::vector<std::vector<double>>& T,const double eta,
                  const double eta_j, const size_t j, const size_t n,
                  const double k_ref);

void parametersStrSetup(struct parameterStr *parametersStr,
                        const enum XParaNames *xParametersNames);

void mainMemoryFree(struct parameterStr * parametersStr);

struct parameter_constraints
{
    double R0_min;
    double R0_max;

    double R1_min ;
    double R1_max ;

    double E_sigma_min ;
    double E_sigma_max ;

    double lambda_min ;
    double lambda_max ;

    double gamma_min ;
    double gamma_max ;

    double a_sub_min ;
    double a_sub_max ;

    double Lcoat_min ;
    double Lcoat_max ;
};

class Mesh
{
public:
    std::vector<double> z_jplus, z_jminus, z_j;

    double *rZeta, *rNorm, *rReal, *rNorm2;
    double *tau, *time;
    double *eta, *z_real, *z_norm,  *zNorm2;
    double *d_eta_plus, *deltaZ, *d_eta_minus;

    mutable size_t M1;
    const size_t M2, Rend, Nend;

    Mesh(const size_t M2_, const size_t Rend_, const size_t Nend_,
         const double beta1_, const double split_);

    void meshUpdate(const double L_coat, const double L_substrate,
                    const double CO2Radius, const double Rdomain);
    void cleanup(void);

private:
    const double beta1, split;
    mutable double beta2;

    double beta2_func(double * variable, double * constants);
    void minimizer(double *variable, double *constants,
                   double temp_variable_min, double temp_variable_max,
                   double min_goal, const size_t max_iterations);
    double z_eta(const double eta_, const double beta1_, const double beta2_);

    double find_beta2(const double L_coat, const double L_substrate);
    size_t discretizeSpace(const double L_coat, const double L_substrate);

    double z_eta(const double eta_);
    double D_eta(const double z_norm_);

    void zUpdate();

};

void parameters_kcp_update(struct parameterStr* parametersStr,
                           const double gamma, const double a_sub);
void parameters_agamma_update(struct parameterStr* parametersStr,
                              const double k_c, const double psi_c);

double gspatial(double eta, double opt, double lambda, double R0,double R1,
                double Iplus0, double Iplus1);

double beta2_func(double* variable, double* constants);

double find_beta2(const double beta1, const double M2,const double L_substrate,
                  const double L_coat,const double split);

int discretize_1d(size_t nodes, size_t Nend, double beta1, double beta2, double split,
                  double *eta, double *z_norm, double *z_real, double *time,
                  double L_coat, double L_substrate, double *tau, double omega,
                  double k_c, double psi_c, double k_ref, double psi_ref);

void cosfcn(int P,int N,double *x,double *fvec,int *iflag, double **variables);

double simpson_3_8(const double *Y, const double *X, const size_t A,
                   const size_t B);
double simpson_3_8(const std::vector<double>& Y, const double *X,
                   const size_t A,const size_t B);
double simpson_3_8(const std::vector<double>& Y, const std::vector<double>&X,
                   const size_t A,const size_t B);
double simpson_3_8(const double* Y, const std::vector<double>& X,
                   const size_t A, const size_t B);
std::complex<double> simpson_3_8Complex(const double* YReal,
                                        const double* YCPLX,
                                        const std::vector<double>& X,
                                        const size_t A,const size_t B);
std::complex<double> simpson_3_8Complex(const std::vector<double>& YReal,
                                        const std::vector<double>& YCPLX,
                                        const std::vector<double>& X,
                                        const size_t A,const size_t B);
std::complex<double> simpson_3_8Complex(const double* YReal,
                                        const double* YCPLX,
                                        const double* X,
                                        const size_t A,const size_t B);

double x_limiter1(const double xi);
double x_limiter2(const double xi,const double x_min, const double x_max);
double kx_limiter1(const double ki);
double kx_limiter2(const double ki,const double k_min,const double k_max);

double x_ini(double x_min, double x_max);

void solveMatrix(const int64_t n, const std::vector<double>& b,
                 const std::vector<double>& d, const std::vector<double>& a,
                 const std::vector<double>& C, std::vector<double>& u);

double SOR(double**A, double*b, const size_t M2, double*phi, double omega,
           double error);

void minimizer( double (*to_minimize)(double*,double*), double *variable,
               double *constants, double temp_variable_min,
               double temp_variable_max, double min_goal,const size_t max_iterations);

double average(const double a, const double b);

double gs_int(const double eta, const double opt, const double lambda,
              const double R0, const double R1, const double Iplus0,
              const double Iplus1);
double psi(const double eta, const double psi_layer1, const double psi_layer2);
double psi(const std::vector<std::vector<double>>& T, const double eta,
           const size_t j, const size_t n, const double psi_c,
           const double psi_ref);

double k(const std::vector<std::vector<double>>& T, const double zpos,
         const double k_c, const double k_ref);

double kthermal(const double eta, const double k_layer1, const double k_layer2);

double Kappa(const std::vector<std::vector<double>>& T, const double eta,
             const double eta_j, const size_t j, const size_t n,
             const double k_ref, const int prop_linearity, const double k_c);
void scaleDiag(const int mode, const size_t N, double * diag,
               const struct parameterStr * parametersStr );

double x_normal(const double Xmean, const double Xstddev);

double x_normal(const double Xmean, const double Xstddev, const double seed1);

double Psi_non(const std::vector<std::vector<double>>& T, const double eta,
               const double eta_j, const size_t j, const size_t n,
               const double psi_ref, const int prop_linearity,
               const double psi_c);

void cosfit(double **dependent, const double *independent, double *x, int j,
            double omega1, int Nend);

void cosfit(double *dependent, const double *independent, double *x,
            int Nend);

void cosfcn1(int P,int N,double *x,double *fvec,int *iflag, double **variables);

double Iheat(double Isteady, double Itransient, double omega, double t) ;//verified

size_t sumVector(const size_t *const vector1,const size_t sizeV);

double Iheat_int(const double Isteady,const double Itransient,
                        const double omega, const double t); //verified

double tau_0(const double omega);
double x_bias(const double Xmean, const double Xstddev);

size_t discretizeSpace(const int nodes,const double beta1,const double beta2,
                       const double split, double *z_norm, double *z_real,
                       const double L_coat,const double L_substrate, double*eta,
                       double* zNorm2);

double omega(const double L_coat, const double l_thermal, const double k_c,
             const double psi_c);

double lthermal(const double L_coat, const double k_c, const double psi_c,
                const double omega);

double x_ini(const double x_min, const double x_max, const size_t position,
             const size_t gN);
void mainMemoryAllocate(struct parameterStr * parametersStr);

size_t xINTrandom(const size_t xmin, const size_t xmax);
void range1og10(const double l_min, const double l_max, const size_t L_end,
             double* l_thermal);

void range(double* l_thermal, const double l_min, const double l_max,
           const size_t L_end);
void range(std::vector<double>& l_thermal, const double l_min,
           const double l_max, const size_t L_end);

double percentile(const double xmin, const double xmax, const double x);
double percentilelog10(const double xmin, const double xmax, const double x);

class perturbStruct
{
  public:
    size_t pNum;

    size_t xnumber;  //keep this odd
    double spread;
    double lmin1;

    double lmax2;
    double PtolBand;
    const double lminRef = 0.2;
    const double lmaxRef = 0.8;
    const double lmin2 = .6;
    const double lmax1 = lmin1;

    size_t iterates;
    double* xArea;
    double* lmin;
    double* lmax;
    double* temp;
    double* bands;

    perturbStruct(const size_t a, const size_t b, const double c );
    perturbStruct(const size_t a, const size_t b, const double c,
                  const double e, const double h, const size_t i);
    void lThermalMC();
    void lthermalDeterministic();
    void lthermalBands(const double PtolBand1);
    void cleanup();
    void cleanup2();
};

class Laser
{
private:
    double area(void) const;
    double IntensityTotal(void) const;
    double IntensitySteady(void) const;
    double IntensityTransient(void) const;
    double offset, amplitude;
    void update(void);
    double l_min, l_max;
    void updateNMeasurements();

public:
    double Qlaser, radius;
    double Is, It;

    size_t L_end;
    double *omegas = nullptr;
    double *l_thermal = nullptr;

    Laser(const double a, const double b, const double c, const double d);
    void updateRadius(const double r);
    void updatePower(const double Qpower);

    double thermalSetup(const double lmin_, const double lmax_,
                      const double L_coat, const double kc, const double psic,
                      const double L_end_);
    void cleanup(void);
};


struct parameterStr
{

public:
    class Mesh *mesh;
    class ThermalModel *thermalModel;
    class Laser *laser;

    ///layer 1
    class property *k1_thermal, *psi1_thermal;
    double L_coat, lambda;
    double diffusivity_coat, effusivity_coat;
    double c_coat = 1.;
    double a_coat;

    ///layer 2
    class property *k2_thermal, *psi2_thermal;
    double L_substrate, lambda_Sub;
    double diffusivity_sub, effusivity_sub;
    double c_sub = 1.;
    double a_sub;

    ///system
    double R_domain, T_ref, T_rear, R0, R1;

    ///nondimensional
    double gamma, E_sigma, epsilon;

    ///parameter estimation
    double *emissionExperimental;
    double *emissionNominal;
    double *xParameters54;

    double *emissionCurrent = nullptr;
    double *fjac = nullptr;
    double *predicted = nullptr;
    double *fvec = nullptr;

    size_t *xParameters95, *xParameters;
    double Ttol, MSE, MSEinitial, MSETol, ChiSquare, coscheck, fvecTotal;
    double fvecTol, variance;
    size_t iterPE, iterPEnum, N95, temp_output;
    enum XParaNames *xParameters95Names, *xParametersNames;
    int iterC;
    size_t L_end, N;

    ///other
    std::string dir;
    double q_surface, Rtc, T_base;
    double detector_lam, bNorm;
    size_t iter, prop_linearity, e_model;
    double detector_rad;

    void thermalSetup(const double lmin, const double lmax,
                      const size_t LendMin);

    parameterStr(const size_t d, class Mesh *mesh_);
    void parametersStrSetup(const enum XParaNames *xParametersNames_);
    void update_b(const double radius, const double L);
    void update_b(void);
    void EmissionNoise(const double a, const double b, const bool d1,
                       const bool d2, const int s1, const double noiseRandom,
                       const double* emissionNominal,
                       const double lmin, const double lmax);
    void cleanup();

private:
    void updateNMeasurements(const size_t Lend_);

};



#endif // NUMERICAL_SETUP_H_INCLUDED
