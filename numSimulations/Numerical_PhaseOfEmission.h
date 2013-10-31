#ifndef NUMERICAL_PHASEOFEMISSION_H_INCLUDED
#define NUMERICAL_PHASEOFEMISSION_H_INCLUDED
class Temperature
{
private:
    const size_t Nend;
    const size_t M2;
    double *temperature = nullptr;

public:
    Temperature(const size_t Nend_, const size_t M2_);
    double eval(const size_t Nvalue, const size_t M2Value) const;
    void assgn(const size_t i, const size_t j, const double value);
    void cleanup(void);
};

double PhaseOfEmission2DAna(const int flag,
                            const struct parameterStr *const parametersStr);
double PhaseOfEmission1DNum(const int flag,
                            const struct parameterStr*const pStruct);
double PhaseOfEmission1DAna(const int flag,
                            const struct parameterStr*const parametersStr);

class emissionNoiseParameters
{
public:
    double a, b, noiseRandom;
    bool d1, d2;
    int s1;
    emissionNoiseParameters(const double a1_, const double b1_, const bool d1_,
                            const bool d2_, const int s1_,
                            const double noiseRandom_);
};


struct layer
{
    struct property kthermal;
    struct property psithermal;
    double Length;
};

struct temperatureScale
{
    double referance;
    double rear;
    double tolerance;
};

struct modelSystem
{
    struct layer coating;
    struct layer substrate;
    struct temperatureScale Temp;

    double gamma;
    double Rtc;
    double R0;
    double R1;
    double lambda;
};

#endif // NUMERICAL_PHASEOFEMISSION_H_INCLUDED
