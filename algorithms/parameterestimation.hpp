#ifndef PARAMETERESTIMATION_HPP
#define PARAMETERESTIMATION_HPP

namespace parameterEstimation{

//struct constraints
//{
//  struct bounds
//  {
//    const double lower;
//    const double upper;
//    bounds(const double lower_, const double  upper_);
//  };
//  const struct bounds a_sub;
//  const struct bounds gamma;
//  const struct bounds E1emit;
//  const struct bounds R1;
//  const struct bounds R0;
//  const struct bounds lambda;

//  constraints(const struct bounds a_sub_, const struct bounds gamma_,
//              const struct bounds E1emit_, const struct bounds R1_,
//              const struct bounds R0_, const struct bounds lambda_ );
//};

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
  struct bounds constraint;
  double initialGuess;
  double bestfit;

  unknown(const double lower_, const double upper_);
  unknown(const double lower_, const double upper_, const double initialGuess_);
  void resetInitialGuess(void);
};

struct unknowns
{

  std::vector<struct unknown> unknown;
  size_t N;

  unknowns(const double N_);
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
