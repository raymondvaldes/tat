#ifndef SENSITIVITY_ANALYSIS_HPP
#define SENSITIVITY_ANALYSIS_HPP

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

void parameterUncertainty(const size_t n, const double ftol, const double xtol,
                          const double gtol, const int maxfev,
                          const double epsfcn, const int mode, double factor,
                          const int nprint,
                          const struct parameter_constraints *st_ptr,
                          double *xInitial, struct parameterStr * parametersStr,
                          const double factorMax, const double factorScale,
                          class perturbStruct *pStruct,
                          const class emissionNoiseParameters myEmissionNoise,
                          const std::string filename);
double evaluateUncertainty(const double MSEarea, double* perturbationTable,
                           const std::vector<double>& calibrationTable,
                           size_t xnum);

#endif // SENSITIVITY_ANALYSIS_HPP
