#ifndef PARAMETERESTIMATION_HPP
#define PARAMETERESTIMATION_HPP

namespace parameterEstimation{

struct unknown
{
private:
  struct bounds
  {
    const double lower;
    const double upper;
    bounds(const double lower_, const double  upper_);
  };

public:
  struct physicalModel::labels name;
  struct bounds constraint;
  double initialGuess;
  double bestfit;

  unknown(enum physicalModel::labels::Name name_,
          const double lower_,
          const double upper_);
  unknown(enum physicalModel::labels::Name name_,
          const double lower_,
          const double upper_,
          const double initialGuess_);
  void setInitialGuess(void);
};

struct unknownList
{
//  struct unknown *uParam;
  size_t N;

  unknownList(const double N_);
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


//struct


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
