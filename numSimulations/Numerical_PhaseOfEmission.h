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
                            const struct parameterStr*const parametersStr);
double PhaseOfEmission1DAna(const int flag,
                            const struct parameterStr*const parametersStr);

#endif // NUMERICAL_PHASEOFEMISSION_H_INCLUDED
