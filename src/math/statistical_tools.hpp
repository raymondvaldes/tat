/*----------------------------------------------------------------------------*\
  ========                      |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||   	  		|
-------------------------------------------------------------------------------
License
    This file is part of Thermal Analysis Toolbox.

    Thermal Analysis Toolbox is free software: you can redistribute it and/or
    modify it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or (at your
    option) any later version.

    Thermal Analysis Toolbox is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along with
    Thermal Analysis Toolbox.  If not, see <http://www.gnu.org/licenses/>.

\*----------------------------------------------------------------------------*/
#ifndef STATISTICAL_TOOLS_HPP_INCLUDED
#define STATISTICAL_TOOLS_HPP_INCLUDED

#include <vector>
#include <cstddef>

void vector3DSetup(std::vector< std::vector< std::vector< double > > > &Vnew,
                   const size_t x, const size_t y, const size_t z);

void vector2DSetup(std::vector< std::vector< double > > &Vnew,
                   const size_t x, const size_t y);

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

double rss(const double N, const double* exp, const double* x_hat);

double sVarianceEst(const double N, const double k, const double* SS);

double variance(const size_t P, const size_t N, const double S);

double Sobjective(const size_t L_end, const double*emissionExp,
                  const double* emissionNum);

double MSE(const size_t N, std::vector<double> &emissionExp,
           std::vector<double> &emissionEst);
double MSE(const size_t N, const double*emissionExp,
                    const double* emissionEst);

double MSEarea(const size_t N, std::vector<double> &func1,
               std::vector<double> &func2);




#endif // STATISTICAL_TOOLS_HPP_INCLUDED
