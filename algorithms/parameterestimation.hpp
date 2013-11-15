#ifndef PARAMETERESTIMATION_HPP
#define PARAMETERESTIMATION_HPP


enum XParaNames
{
    gammaEff,
    asub,
    E1,
    R1,
    lambda,
    R0
};

namespace parameterEstimation{

class unknown
{
private:
  struct bounds
  {
    const double lower;
    const double upper;
    bounds(const double lower_, const double  upper_);
  };
  struct physicalModel::labels name;
  struct bounds constraint;
  double initialGuess;
  double bestfitval;

public:
  unknown(enum physicalModel::labels::Name name_,
          const double lower_,
          const double upper_);
  unknown(enum physicalModel::labels::Name name_,
          const double lower_,
          const double upper_,
          const double initialGuess_);

  void Initialauto(void);

  void Initialset(const double input);
  void bestfitset(const double input);

  double initialVal(void);
  double bestfit(void);
  double upperBound(void);
  double lowerBound(void);

  enum physicalModel::labels::Name label(void);

};

class unknownList
{
private:
  std::vector<class unknown> vectorUnknowns;

public:
  void addUnknown(physicalModel::labels::Name name,
                  const double lower,
                  const double upper);
  size_t Nsize(void);
};

struct settings
{
  double ftol;
  double xtol;
  double gtol;
  size_t maxfev;
  double epsfcn;
  double factor;
  size_t mode;
  size_t nprint;

  settings(double ftol_, double xtol_, double gtol_, size_t maxfev_,
           double epsfcn_, double factor_, size_t mode_, size_t nprint_);
};

class LMA_workingArrays
{
public:
  double *fjac = nullptr;
  double *predicted = nullptr;
  double *fvec = nullptr;

  ///poptea structures
  double *emissionExperimental;
  double *emissionNominal;
  double *emissionCurrent = nullptr;

  double MSE, MSEinitial, MSETol, ChiSquare, fvecTotal;
  double variance;
};

}

struct parameter_constraints
{
  double R0_min;
  double R0_max;

  double R1_min ;
  double R1_max ;

  double E_sigma_min ;
  double E_sigma_max ;

  double lambda_min ;
  double lambda_max ;

  double gamma_min ;
  double gamma_max ;

  double a_sub_min ;
  double a_sub_max ;

  double Lcoat_min ;
  double Lcoat_max ;
};


#endif // PARAMETERESTIMATION_HPP
