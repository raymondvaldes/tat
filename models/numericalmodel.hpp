#ifndef NUMERICALMODEL_HPP
#define NUMERICALMODEL_HPP

namespace numericalModel
{
class Mesh
{
public:
  std::vector<double> z_jplus;
  std::vector<double> z_jminus;
  std::vector<double> z_j;

  double *rZeta, *rNorm, *rReal, *rNorm2;
  double *tau, *time;
  double *eta, *z_real, *z_norm,  *zNorm2;
  double *d_eta_plus, *deltaZ, *d_eta_minus;

  mutable size_t M1;
  const size_t M2;
  const size_t Rend;
  const size_t Nend;

  Mesh(const size_t M2_, const size_t Rend_, const size_t Nend_,
       const double beta1_, const double split_, const double L_coat_,
       const double L_substrate_, const double CO2Radius_,
       const double Rdomain_);
  ~Mesh();

  void meshUpdate(const double L_coat, const double L_substrate,
                  const double CO2Radius, const double Rdomain);

private:
  const double beta1, split;
  mutable double beta2;

  double beta2_func(double * variable, double * constants);
  void minimizer(double *variable, double *constants,
                 double temp_variable_min, double temp_variable_max,
                 double min_goal, const size_t max_iterations);
  double z_eta(const double eta_, const double beta1_, const double beta2_);
  double find_beta2(const double L_coat, const double L_substrate);
  size_t discretizeSpace(const double L_coat, const double L_substrate);
  double z_eta(const double eta_);
  double D_eta(const double z_norm_);
  void zUpdate();
};


}

#endif // NUMERICALMODEL_HPP
