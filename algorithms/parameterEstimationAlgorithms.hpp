#ifndef PARAMETERESTIMATIONALGORITHMS_HPP_INCLUDED
#define PARAMETERESTIMATIONALGORITHMS_HPP_INCLUDED
void lmdif(void (*fcn)(int, int, double*, double*, int*, double**), int m,
           int n, double *x, double *fvec, double **variables, double ftol,
           double xtol, double gtol, int maxfev, double epsfcn, double *diag,
           int mode, double factor, int nprint, int *info, int *nfev,
           double *fjac, int ldfjac, int *ipvt, double *qtf, double *wa1,
           double *wa2, double *wa3, double *wa4, double *);

void lmdif(void (*fcn)(int, int, double*, double*, int*,
                       const struct parameter_constraints*,
                       struct parameterStr*), int m, int n, double *x,
           double *fvec, double ftol, double xtol,
           double gtol, int maxfev, double epsfcn, double *diag, int mode,
           double factor, int nprint, int *info, int *nfev, double *fjac,
           int ldfjac, int *ipvt, double *qtf, double *wa1, double *wa2,
           double *wa3, double *wa4, double *wa5,
           const struct parameter_constraints*st_ptr,
           struct parameterStr * parametersStr);



#endif // PARAMETERESTIMATIONALGORITHMS_HPP_INCLUDED
