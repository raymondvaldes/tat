#ifndef SENSITIVITY_ANALYSIS_HPP
#define SENSITIVITY_ANALYSIS_HPP

void perturbationTest(const size_t m, const size_t n,
                      struct parameterEstimation::settings ParaEstSetting,
                      double *xInitial,
                      class thermalAnalysisMethod::PopTea poptea,
                      const double factorMax, const double factorScale,
                      class perturbStruct *pStruct);

void calibrationSweep(struct parameterEstimation::settings ParaEstSetting,
                      double *xInitial,
                      class thermalAnalysisMethod::PopTea poptea,
                      const double factorMax, const double factorScale,
                      class perturbStruct *pStruct, const std::string filename,
                      const size_t lEndMin);

void fitting(class thermalAnalysisMethod::PopTea poptea, double * xInitial,
             const size_t interants, const double factorMax,
             const double factorScale);

void bootstrap(size_t P, size_t N, double ftol, double xtol, double gtol,
               int maxfev, double epsfcn, int mode, double factor, int nprint,
               const struct parameter_constraints *st_ptr,
               class thermalAnalysisMethod::PopTea poptea,
               const double ExpStddev, const double *Numerical_Phase,
               const double *Analytical_Phase, double *xInitial,
               const size_t interants, const double factorMax,
               const double factorScale);

void parameterUncertainty(const size_t n,
                          struct parameterEstimation::settings ParaEstSetting,
                          double *xInitial, class thermalAnalysisMethod::PopTea poptea,
                          const double factorMax, const double factorScale,
                          class perturbStruct *pStruct,
                          const class emissionNoiseParameters myEmissionNoise,
                          const std::string filename);

double evaluateUncertainty(const double MSEarea, double* perturbationTable,
                           const std::vector<double>& calibrationTable,
                           size_t xnum);

#endif // SENSITIVITY_ANALYSIS_HPP
