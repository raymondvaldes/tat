#ifndef EXPERIMENTAL_PHASEOFEMISSION_H_INCLUDED
#define EXPERIMENTAL_PHASEOFEMISSION_H_INCLUDED

//void phase99(const size_t L_end,
//             const double* l_thermal, const struct parameterStr * parametersStr,
//             double *Numerical_Phase,
//             double *Analytical_Phase);

double Experimental_PhaseOfEmission(double*phase, const size_t L_end);
void phase99(const size_t L_end,
             const struct parameterStr * parametersStr,
             double *Numerical_Phase);


#endif // EXPERIMENTAL_PHASEOFEMISSION_H_INCLUDED
