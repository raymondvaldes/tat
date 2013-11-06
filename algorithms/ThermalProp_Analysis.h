#ifndef THERMALPROP_ANALYSIS_H_INCLUDED
#define THERMALPROP_ANALYSIS_H_INCLUDED



int paramter_estimation(const size_t m, const size_t  n,
                        struct parameterEstimation::settings ParaEstSetting,
                        int *info, int *nfev,
                        const struct parameter_constraints *pc_ptr,
                        double *x, struct parameterStr * pStruct,
                        const double factorMax, const double factorScale,
                        double *xpredicted);

void ThermalProp_Analysis(int, int N, double*x, double*fvec, int*,
                          const struct parameter_constraints* st_ptr,
                          struct parameterStr * parametersStr );

double ThermalProp_error(void (*fcn)(size_t, size_t, double *, double *, int*,
                                     double **, struct parameter_constraints*,
                                     struct parameterStr*), size_t m, size_t n,
                         double *x, double *fvec,double **variables,
                         struct parameter_constraints*st_ptr,
                         struct parameterStr *parametersStr);

void printPEstimates(const size_t N, struct parameterStr * parametersStr);
void printfJac(const size_t N, const size_t P, const double*fjac);
void InformationIndexAll(const size_t P, const size_t N,
                         const struct parameterStr * parametersStr);

void InformationIndex(const size_t P, double *Index,
                      const size_t I, const double ki, const double *const fjac);

void InformationIndex(const size_t P, std::vector<double> Index,
                      const size_t I, const double ki,
                      const double* fjac);



#endif // THERMALPROP_ANALYSIS_H_INCLUDED
