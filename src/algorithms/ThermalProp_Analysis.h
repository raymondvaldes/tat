#ifndef THERMALPROP_ANALYSIS_H_INCLUDED
#define THERMALPROP_ANALYSIS_H_INCLUDED
#include <boost/foreach.hpp>

int paramter_estimation(const size_t m, const size_t  n,
                        struct parameterEstimation::settings ParaEstSetting,
                        int *info, int *nfev,
                        double *x, class thermalAnalysisMethod::PopTea poptea,
                        const double factorMax, const double factorScale,
                        double *xpredicted);

void ThermalProp_Analysis(int, int N, double*x, double*fvec, int*,
                          class thermalAnalysisMethod::PopTea poptea );

void printPEstimates(const size_t N, class thermalAnalysisMethod::PopTea poptea);
void printfJac(const size_t N, const size_t P, const double*fjac);
void InformationIndexAll(const size_t P, const size_t N,
                         const class thermalAnalysisMethod::PopTea poptea);

void InformationIndex(const size_t P, double *Index,
                      const size_t I, const double ki, const double *const fjac);

void InformationIndex(const size_t P, std::vector<double> Index,
                      const size_t I, const double ki,
                      const double* fjac);

#endif // THERMALPROP_ANALYSIS_H_INCLUDED
