#ifndef THERMALPROP_ANALYSIS_H_INCLUDED
#define THERMALPROP_ANALYSIS_H_INCLUDED

void ThermalProp_Analysis(int P, int N, double*x, double*fvec, int*iflag,
                          const struct parameter_constraints* st_ptr,
                          struct parameterStr * parametersStr );

double ThermalProp_error(void (*fcn)(size_t, size_t, double *, double *, int*,double **,
                                     struct parameter_constraints*,
                                     struct parameterStr*), size_t m, size_t n,
                         double *x, double *fvec,double **variables,
                         struct parameter_constraints*st_ptr,
                         struct parameterStr *parametersStr);

void printPEstimates(const size_t N, struct parameterStr * parametersStr);
void printfJac(const size_t N, const size_t P, const double*fjac);
void InformationIndexAll(const size_t P, const size_t N,
                         const struct parameterStr * parametersStr);

void InformationIndex(const size_t P, const size_t N, double *Index,
                      const size_t I, const double ki,const double *const fjac);

void InformationIndex(const size_t P, const size_t N, std::vector<double> Index,
                      const size_t I, const double ki,
                      const double* fjac);
#endif // THERMALPROP_ANALYSIS_H_INCLUDED
