#ifndef STATISTICAL_TOOLS_HPP_INCLUDED
#define STATISTICAL_TOOLS_HPP_INCLUDED

#include <vector>
#include <cstddef>
#include "numSimulations/Numerical_PhaseOfEmission_Results.h"

bool equalto(const double a, const double b);
bool equalto(const double a, const int b);

void vector3DSetup(std::vector< std::vector< std::vector< double > > > &Vnew,
                   const size_t x, const size_t y, const size_t z);

void vector2DSetup(std::vector< std::vector< double > > &Vnew,
                   const size_t x, const size_t y);

double rss(const double N, const double* exp, const double* x_hat);

double sVarianceEst(const double N, const double k, const double* SS);

double variance(const size_t P, const size_t N, const double S);

double Sobjective(const size_t L_end, const double*emissionExp,
                  const double* emissionNum);

double SobjectiveLS(const size_t N, const double*emissionExp,
                    const double* emissionEst);
double SobjectiveLS(const size_t N, const std::vector<double> &emissionExp,
                    const std::vector<double>& emissionEst);
double MSE(const size_t N, std::vector<double> &emissionExp,
           std::vector<double> &emissionEst);
double MSE(const size_t N, const double*emissionExp,
                    const double* emissionEst);
double MSEarea1(size_t N, double* func1, double* func2, double* xvar);

void matrixTranspose(const size_t P, const size_t N, double*matrix);

void matrixTranspose(const size_t P, const size_t N, const double*matrix,
                     double*matrixT);

void matrixDot(const double* MatrixA, const size_t rowA, const size_t columnA,
               const double* MatrixB, const size_t rowB, const size_t columnB,
               double* MatrixResultant);

void covarianceMatrix(const size_t N, const double variance,
                      const double* Amatrix, double* cov);

void standardError(const size_t N, const double *cov, double* standardError);
void printArray(const double* const matrix, const size_t N);

void printArray2d(const size_t N, const size_t M, const double* const matrix);

void printArray(const std::vector<double> &matrix, const size_t N);

void printVariable(const double X1, const double X2, const double X3,
                   const size_t X4);
void printArray2d(const size_t N, const size_t M,
                  const std::vector<std::vector<double>>& matrix);

void Amatrix(const size_t P, const size_t N, const double*fjac, double* Amatrix);

double chisquare(const size_t N, const double*emissionExp,
                    const double* emissionEst);



double arrayMax(const double* x, const size_t I);
double arrayMin(const double* x, const size_t I);


double fintegrate(double x, void *p);
double integrate(struct funcClass *Func, double xlow, double xhigh);
double MSEarea(const size_t N, std::vector<double> &func1,
               std::vector<double> &func2);




#endif // STATISTICAL_TOOLS_HPP_INCLUDED
