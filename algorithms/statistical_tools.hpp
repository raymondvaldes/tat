#ifndef STATISTICAL_TOOLS_HPP_INCLUDED
#define STATISTICAL_TOOLS_HPP_INCLUDED
bool equalto(const double a, const double b);
bool equalto(const double a, const int b);

void vector3DSetup(std::vector< std::vector< std::vector< double > > > &Vnew,
                   const size_t x, const size_t y, const size_t z);
void vector2DSetup(std::vector< std::vector< double > > &Vnew,
                   const size_t x, const size_t y);

double rss(const double N, const double* exp, const double* x_hat);

double sVarianceEst(const double N, const double k, const double* SS);

double variance(const size_t P, const size_t N, const double S);

double Sobjective(const size_t L_end, const double*emissionExp,
                  const double* emissionNum);

double SobjectiveLS(const size_t N, const double*emissionExp,
                    const double* emissionEst);
double SobjectiveLS(const size_t N, const double*emissionExp,
                    const std::vector<double>& emissionEst);
double MSE(const size_t N, const double* const emissionExp,
           const std::vector<double>& emissionEst);
double MSE(const size_t N, const double*emissionExp,
                    const double* emissionEst);
double MSEarea1(size_t N, double* func1, double* func2, double* xvar);

void matrixTranspose(const size_t P, const size_t N, double*matrix);

void matrixTranspose(const size_t P, const size_t N, const double*matrix,
                     double*matrixT);

void matrixDot(const double* MatrixA, const size_t rowA, const size_t columnA,
               const double* MatrixB, const size_t rowB, const size_t columnB,
               double* MatrixResultant);

void covarianceMatrix(const size_t N, const double variance,
                      const double* Amatrix, double* cov);

void standardError(const size_t N, const double *cov, double* standardError);
void printArray(const double* const matrix, const size_t N);

void printArray2d(const size_t N, const size_t M, const double* const matrix);

void printArray(const std::vector<double> &matrix, const size_t N);

void printVariable(const double X1, const double X2, const double X3,
                   const size_t X4);
void printArray2d(const size_t N, const size_t M,
                  const std::vector<std::vector<double>>& matrix);

void Amatrix(const size_t P, const size_t N, const double*fjac, double* Amatrix);

double chisquare(const size_t N, const double*emissionExp,
                    const double* emissionEst);

void perturbationTest(const size_t m, const size_t n, const double ftol,
                      const double xtol, const double gtol,
                      const int maxfev, const double epsfcn, const int mode,
                      double factor, const int nprint,
                      const struct parameter_constraints *pc_ptr,
                      double *xInitial, struct parameterStr * parametersStr,
                      const double factorMax, const double factorScale,
                      class perturbStruct *pStruct);

void calibrationSweep(const size_t m, const size_t n, const double ftol,
                      const double xtol, const double gtol,
                      const int maxfev, const double epsfcn, const int mode,
                      double factor, const int nprint,
                      const struct parameter_constraints *pc_ptr,
                      double *xInitial, struct parameterStr *pStructp,
                      const double factorMax, const double factorScale,
                      class perturbStruct *pStruct, const std::string filename,
                      const size_t lEndMin);


void statisticalPrintOut(size_t m, size_t n,
                        const struct parameter_constraints *pc_ptr,
                        double *xInitial, struct parameterStr * parametersStr,
                        const double Xstddev,double *Numerical_Phase,
                        double *Analytical_Phase, const double factorMax,
                        const double factorScale);

void fitting(size_t m, size_t n, double ftol, double xtol, double gtol,
             int maxfev, double epsfcn, int mode, double factor, int nprint,
             const struct parameter_constraints *st_ptr,
             struct parameterStr * pStruct, double * xInitial,
             const size_t interants, const double factorMax,
             const double factorScale);

void bootstrap(size_t P, size_t N, double ftol, double xtol, double gtol, int maxfev,
             double epsfcn, int mode, double factor, int nprint,
             const struct parameter_constraints *st_ptr,
             struct parameterStr * parametersStr, const double ExpStddev,
             const double *Numerical_Phase, const  double *Analytical_Phase,
             double *xInitial, const size_t interants, const double factorMax,
             const double factorScale);

void lthermalOptimization(const size_t n, const double ftol, const double xtol,
                          const double gtol, const int maxfev,
                          const double epsfcn, const int mode, double factor,
                          const int nprint,
                          const struct parameter_constraints *st_ptr,
                          double *xInitial, struct parameterStr * parametersStr,
                          const double factorMax, const double factorScale,
                          class perturbStruct *pStruct, const double a,
                          const double b, const bool d1, const bool d2,
                          const int s1, const double noiseRandom,
                          const std::string filename);

double arrayMax(const double* x, const size_t I);
double arrayMin(const double* x, const size_t I);


double fintegrate(double x, void *p);
double integrate(struct funcClass *Func, double xlow, double xhigh);
double MSEarea(const size_t N, const double* const func1,
               const double* const func2);

double evaluateUncertainty(const double MSEarea, double* perturbationTable,
                           const std::vector<double>& calibrationTable,
                           size_t xnum);



#endif // STATISTICAL_TOOLS_HPP_INCLUDED
