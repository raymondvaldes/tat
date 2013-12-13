#ifndef NUMERICAL_TEMPERATURE_H_INCLUDED
#define NUMERICAL_TEMPERATURE_H_INCLUDED

class matrixArrays
{
    public:
    std::vector<double> A1, A2, A3;
    std::vector<double> b;
    std::vector<double> Temperature;
    std::vector<double> B1, B2, B3;

    const size_t M2;
    double B4;

    explicit matrixArrays(const size_t length): A1(length), A2(length),
      A3(length), b(length), Temperature(length), B1(length), B2(length),
      B3(length), M2(length)
    {    }
};

double Numerical_Temperature( const double *const *parameters, double **T,
                              const int flag ,
                              const struct parameter_constraints *st_ptr);

double Tss1D_ana(const double z, const double R1, const double lambda,
                 const double Is, const double L, const double d,
                 const double k_ref, const double Iplus0, const double Iplus1,
                 const double q_surface, const double k_c);

std::complex<double> Tac1D_ana(const double z, const double R0, const double R1,
                               const double epsilon, const double Lam,
                               const double Lthrm);

void temperature_1D(const class physicalModel::TBCsystem TBCsystem,
                    const class thermal::ThermalModelSelection thermalModel,
                    const expEquipment::setup expSetup,
                    const double omega1,
                    class Temperature Tprofile);

double eta_z(const double z,const double beta1,const double beta2);

double abMatrixPrepopulate(std::vector<double>& B1,
                           std::vector<double>& B2,
                           std::vector<double>& B3,
                           const size_t M1, const size_t M2,
                           const std::vector<double> &tau,
                           const double L_coat, const double L_substrate,
                           const double tau_ref,
                           const std::vector<double> &eta,
                           const double q_surface,
                           const std::vector<double>& z_jplus,
                           const std::vector<double>& z_jminus,
                           const std::vector<double>& z_j,
                           const std::vector<double> &d_eta_plus,
                           const std::vector<double> &deltaZ,
                           const std::vector<double> &d_eta_minus);

void bMatrixPrepopulate1(const size_t n, std::vector<double>& B2,
                         std::vector<double>& b, const size_t M1,
                         const size_t M2, const std::vector<double> &tau,
                         const double Is, const double It, const double L_coat,
                         const double tau_ref, const double R1,
                         const double Iplus1, const double omega,
                         const std::vector<double>& z_jminus,
                         const std::vector<double>& z_j, const std::vector<double> &deltaZ,
                         const double* genProfile, const double T_rear);

double Gaverage(const double opt, const double lambda,
                const double R1, const double Iplus0, const double Iplus1,
                const double z1, const double z2);

void heatingProfile(const double opt, const double lambda,
                    const double R1, const double Iplus0, const double Iplus1,
                    const std::vector<double>& z_jplus,
                    const std::vector<double>& z_jminus,
                    const std::vector<double>& z_j, double*genProfile,
                    const size_t M1 );

void Ab_transient(const size_t n,
                  std::vector<double>& A1,
                  std::vector<double>& A2,
                  std::vector<double>& A3,
                  std::vector<double>& b, const class Temperature Tprofile,
//                  const std::vector<std::vector<double>>& T,
                  const size_t M1,
                  const size_t M2,
                  const std::vector<double>& B1,
                  const std::vector<double>& B2,
                  const std::vector<double>& B3,
                  const double B4,
                  const class property *kLayer1,
                  const class property *kLayer2,
                  const class property *psiLayer1,
                  const class property *psiLayer2
                  );

double t_tau(const double tau, const double tau_ref);

double Iaverage(const double Is, const double It, const double omega,
                const double tau_ref, const std::vector<double> &tau, const size_t n);

double qGenAverage(const double I_avg, const double opt, const double lambda,
                   const double R1, const double Iplus0, const double Iplus1,
                   const double z1, const double z2);

double r_xi(const double xi, const double beta);

double Iplus1Func(const double R0, const double R1, const double lambda);
double Iplus0Func(const double R0, const double R1, const double lambda);


#endif // NUMERICAL_TEMPERATURE_H_INCLUDED
