#include "../Header.h"

namespace parameterEstimation{

settings::settings(double ftol_, double xtol_, double gtol_, size_t maxfev_,
                 double epsfcn_, double factor_, size_t mode_,
                 size_t nprint_)
  :ftol(ftol_), xtol(xtol_), gtol(gtol_), maxfev(maxfev_), epsfcn(epsfcn_),
    factor(factor_), mode(mode_), nprint(nprint_){}

unknown::unknown(enum physicalModel::labels::Name name_,
                 const double lower_,
                 const double upper_)
    :name(name_), constraint(lower_, upper_)
{
    Initialauto();
}

unknown::unknown(enum physicalModel::labels::Name name_,
                 const double lower_,
                 const double upper_,
                 const double initialGuess_)
    :name(name_), constraint(lower_, upper_), initialGuess(initialGuess_)
{}

void unknown::Initialauto(void)
{
  initialGuess = average(constraint.lower, constraint.upper);
}

void unknown::Initialset(const double initial)
{
  initialGuess = initial;
}

double unknown::initialVal(void)
{
  return initialGuess;
}

double unknown::bestfit(void)
{
  return bestfitval;
}

double unknown::upperBound(void)
{
  return constraint.upper;
}
double unknown::lowerBound(void)
{  name.getName();
  return constraint.lower;
}

void unknown::bestfitset(const double input)
{
  bestfitval = input;
}

enum physicalModel::labels::Name unknown::label(void)
{
  return name.getName();
}



unknown::bounds::bounds(const double lower_, const double upper_)
:lower(lower_), upper(upper_){}


void unknownList::addUnknown(enum physicalModel::labels::Name name,
                             const double lower,
                             const double upper)
{
  vectorUnknowns.push_back (unknown(name, lower, upper));
  return;
}

size_t unknownList::Nsize(void)
{
    return vectorUnknowns.size();
}



void LMA_workingArrays::updateArraySize(const size_t Lend_, const size_t N)
{
  /*Lend_ is the total number of unique measurements in a dataset,
  this value is based on the range and the set minimum*/
  if(fjac)
  {
      deleteArray();
  }

  fjac = new double[Lend_*N];
  emissionExperimental    = new double[Lend_];
  emissionNominal         = new double[Lend_];
  emissionCurrent         = new double[Lend_];
  predicted               = new double[Lend_];
  fvec = new double[Lend_];
}

void LMA_workingArrays::deleteArray(void)
{
  delete [] fjac;
  delete [] emissionExperimental;
  delete [] emissionCurrent;
  delete [] emissionNominal;
  delete [] predicted;
  delete [] fvec;
}


LMA_workingArrays::~LMA_workingArrays(void)
{
  if(fjac)
  {
      deleteArray();
  }
}


}
