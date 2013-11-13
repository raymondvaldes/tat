#include "../Header.h"

namespace parameterEstimation{

settings::settings(double ftol_, double xtol_, double gtol_, size_t maxfev_,
                 double epsfcn_, double factor_, size_t mode_,
                 size_t nprint_)
  :ftol(ftol_), xtol(xtol_), gtol(gtol_), maxfev(maxfev_), epsfcn(epsfcn_),
    factor(factor_), mode(mode_), nprint(nprint_){}



unknown::unknown(const double lower_, const double upper_)
:constraint(lower_, upper_)
{
    resetInitialGuess();
}

unknown::unknown(const double lower_, const double upper_,
                 const double initialGuess_)
:constraint(lower_, upper_), initialGuess(initialGuess_)
{}

void unknown::resetInitialGuess(void)
{
    initialGuess = average(constraint.lower, constraint.upper);
}

unknown::bounds::bounds(const double lower_, const double upper_)
:lower(lower_), upper(upper_){}

unknownList::unknownList(const double N_): N(N_)
{
}


}