#ifndef PARAMETERESTIMATION_HPP
#define PARAMETERESTIMATION_HPP

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
  explicit unknown(enum physicalModel::labels::Name name_,
          const double lower_,
          const double upper_);
  explicit unknown(enum physicalModel::labels::Name name_,
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
  size_t N;

public:
  void addUnknown(physicalModel::labels::Name name,
                  const double lower,
                  const double upper);
  ~unknownList();
  size_t Nsize(void);
  void NAssign(size_t xInput);
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
  ~settings();
};

class LMA_workingArrays
{
public:
  std::vector<double> fjac;
  std::vector<double> predicted;
  std::vector<double> fvec;
  std::vector<double> emissionExperimental;
  std::vector<double> emissionNominal;
  std::vector<double> emissionCurrent;

//  double *fjac = nullptr;
//  double *predicted = nullptr;
//  double *fvec = nullptr;
//  double *emissionExperimental;
//  double *emissionNominal;
//  double *emissionCurrent = nullptr;

  double MSE, MSEinitial, MSETol, fvecTotal;

  ~LMA_workingArrays(void);
  void updateArraySize(const size_t Lend_, const size_t N);
  void deleteArray(void);
};


class LMA
{
public:
  class LMA_workingArrays LMA_workspace;
  struct settings Settings;
  class unknownList unknownParameters;

  explicit LMA(const struct settings Settings_,
      const class unknownList unknownParameters);
  ~LMA(void);
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
