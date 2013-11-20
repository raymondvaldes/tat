#ifndef EXPERIMENTAL_PHASEOFEMISSION_H_INCLUDED
#define EXPERIMENTAL_PHASEOFEMISSION_H_INCLUDED

double Experimental_PhaseOfEmission(double*phase, const size_t L_end);
void phase99(const size_t L_end,
             const class thermalAnalysisMethod::PopTea poptea,
             double *Numerical_Phase);
void phase99(const size_t L_end,
             const class thermalAnalysisMethod::PopTea poptea,
             std::vector<double> &arrayVal);

#endif // EXPERIMENTAL_PHASEOFEMISSION_H_INCLUDED
