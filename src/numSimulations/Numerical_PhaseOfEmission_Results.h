#ifndef NUMERICAL_PHASEOFEMISSION_RESULTS_H_INCLUDED
#define NUMERICAL_PHASEOFEMISSION_RESULTS_H_INCLUDED
#include <gsl/gsl_spline.h>
#include <gsl/gsl_integration.h>

double Print_Emission(const double*phase, const double*num_phase,
                      const double*ana_phase,
                      const double*l_thermal, const size_t L_end);

inline double mean(const double a, const double b)
{
    double mean1 = a;
    mean1 +=b;
    mean1 *=0.5;
    return mean1;
}

struct funcClass
{
public:
  /*
  F:          the gsl_function which is the integrand
  xlow:       lower integration limit
  xhigh:      higher integration limit
  abstol:     absolute tolerance
  reltol:     relative tolerance
  result:     a pointer to a gdouble in which stores the result
  error:      a pointer to a gdobuel in which the function stores the
              estimed error
  */

  const double* xvar;
  const double* func;
  const size_t  N;

  size_t neval;
  double epsabs = 1e-8;
  double epsrel = 1e-8;

  double result, error;
  int code;
  const size_t limit = 1001;    //defines size of workspace

  ///Allocate pointer to interpolation iterator
  gsl_interp_accel *acc   = gsl_interp_accel_alloc();

  ///Declare pointer to interpolations
  gsl_spline *spline      = nullptr;

  ///Declare pointer to workspace
  gsl_integration_workspace * workspace  = nullptr;

  explicit funcClass(double* a, double* b, size_t c): xvar(a), func(b), N(c)
  {
      /*The arguments include two arrays where
          a ...independent array
          b ...dependent array
          c ...size of array */
      ///alloc space for the spline anbd assign to pointer
      spline = gsl_spline_alloc(gsl_interp_cspline, N);
      gsl_spline_init(spline, xvar, func, N);
      workspace = gsl_integration_workspace_alloc (limit);
  }
  ~funcClass(void)
  {
    cleanup();
  }

  double eval(const double xpos) const
  {
      if( xpos < xvar[0] || xpos > xvar[N-1] )
      {
          std::cout << "outside range!!\n\n"
          <<xpos<<" is outside of range "<<xvar[0]<<"\t"<<xvar[N-1]<<"\n";

          exit(-71);
          return 0;
      }

      return gsl_spline_eval(spline, xpos, acc);
  }

  static double CCallback(double d, void*params)
  {
      return static_cast<funcClass*>(params)->eval(d);
  }

  double integrate_a_b(const double xlow, const double xhigh,
                       const double epsabs_, const double epsrel_)
  {
      //http://www.bnikolic.co.uk/nqm/1dinteg/gslgk.html
      if( (xlow < xvar[0]) || (xhigh > xvar[N-1]) || (xlow > xhigh) )
      {
          std::cout << "\n\n" << std::setprecision(4) << (xlow < xvar[0]);
          std::cout << "\t" << (xhigh > xvar[N-1]) << "\t" << (xlow > xhigh);
          std::cout << "\t" << xlow <<"\t"<< xhigh << "\t" << xvar[0] << "\t";
          std::cout << xvar[N-1] << "\n";
          std::cout << "error - redefine integration domain"; exit(64);
      }

      gsl_function F;
      F.function = &funcClass::CCallback;
      F.params = this;

      code = gsl_integration_qng(&F, xlow, xhigh, epsabs_, epsrel_, &result,
                                 &error, &neval);
      return result;
  }

private:
  void cleanup(void)
  {
    gsl_spline_free(spline);
    gsl_interp_accel_free(acc);
    gsl_integration_workspace_free(workspace);
  }
};

class calibration_curves
{
private:
    double *bandsize;
    size_t spread, increments, samples, N, RangeN;
    double range, asubRef, gammaRef, E1Ref, R1Ref, lambdaRef;

public:
    double*perturbation;
    std::vector<std::vector<double>>
    caliDiff, caliEff, caliR1, caliEmission, caliOptical;

    explicit calibration_curves(const std::string filename);
    void cleanup() const;
};




#endif // NUMERICAL_PHASEOFEMISSION_RESULTS_H_INCLUDED
