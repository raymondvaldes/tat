#ifndef NUMERICAL_PHASEOFEMISSION_H_INCLUDED
#define NUMERICAL_PHASEOFEMISSION_H_INCLUDED

#include "numSimulations/Numerical_Temperature.h"
#include "models/poptea.hpp"

class Temperature
{
public:
    explicit Temperature( const size_t Nend_, const size_t M2_ );
    double eval( const size_t Nvalue, const size_t M2Value ) const;
    void assgn( const size_t i, const size_t j, const double value );
    void cleanup( void );

private:
    const size_t Nend;
    const size_t M2;
    double *temperature = nullptr;
};

class emissionNoiseParameters
{
public:
    double a, b, noiseRandom;
    bool d1, d2;
    int s1;
    explicit emissionNoiseParameters( const double a1_, const double b1_,
                                      const bool d1_,
                                      const bool d2_, const int s1_,
                                      const double noiseRandom_);
};

double PhaseOfEmission2DAna(const int flag,
                            const thermalAnalysisMethod::PopTea &poptea);
double PhaseOfEmission1DNum(const int flag,
                            const thermalAnalysisMethod::PopTea &poptea);
double PhaseOfEmission1DAna(const int flag,
                            const thermalAnalysisMethod::PopTea &poptea);


#endif // NUMERICAL_PHASEOFEMISSION_H_INCLUDED
