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
#include <boost/foreach.hpp>
#include "algorithms/ThermalProp_Analysis.h"
#include "algorithms/statistical_tools.hpp"
#include "thermal/emission/phase99.hpp"
#include "math/estimation/lmdiff.hpp"
#include "math/estimation/lmdiff_helper.hpp"
#include "math/estimation/constrained.hpp"
#include "math/utility.hpp"


void InformationIndex(const size_t P, double *Index,
                      const size_t I, const double ki, const double *const fjac)
{
/*
    P  is the number of measurements
    N  is the number of parameters
    I  is the parameter name
    kj is the value of the parameter
*/
    for(size_t j = 0; j < P ; ++j)
    {
        Index[j] = fjac[j + P*I];
        Index[j] *= ki;
        Index[j] *= ki;
        Index[j] *= fjac[j + P*I];
        Index[j] = fabs(Index[j]);

    }

    double maxIndex = fabs(Index[0]);
    for(size_t j=0; j<P ; ++j)
    {
        if(Index[j] > maxIndex)
        {
            maxIndex = fabs(Index[j]);
        }
    }

    for(size_t j=0; j<P ; ++j)
    {
        Index[j] /= maxIndex;
    }


    return;
}

void InformationIndex(const size_t P, std::vector<double> Index,
                      const size_t I, const double ki,
                      const double* fjac)
{
/*
    P  is the number of measurements
    N  is the number of parameters
    I  is the parameter name
    kj is the value of the parameter
*/
    for(size_t j = 0; j < P ; ++j)
    {
        Index[j] = fjac[j + P*I];
        Index[j] *= ki;
        Index[j] *= ki;
        Index[j] *= fjac[j + P*I];
        Index[j] = fabs(Index[j]);

    }

    double maxIndex = fabs(Index[0]);
    for(size_t j=0; j<P ; ++j)
    {
        if(Index[j] > maxIndex)
        {
            maxIndex = fabs(Index[j]);
        }
    }

    for(size_t j=0; j<P ; ++j)
    {
        Index[j] /= maxIndex;
    }


    return;
}

void printfJac(const size_t N, const size_t P, const double*fjac)
{
/*
    P  is the number of measurements
    N  is the number of parameters
    I  is the parameter name
*/
    std::ofstream myfile;
    myfile.open("SensitivityMatrix.dat");
    myfile << std::setprecision(16);
    for(size_t j=0 ; j < P; ++j)
    {
        for(size_t i=0 ; i < N; ++i)
        {
            myfile <<  fjac[j + P*i] << "\t";
        }
        myfile << "\n";
    }

    myfile.close();

    return;
}

void printPEstimates( const class physicalModel::TBCsystem TBCSystem,
                      math::estimation::unknownList list )
{
  BOOST_FOREACH( class math::estimation::unknown &unknown, list.vectorUnknowns)
  {
    std::cout << TBCSystem.returnVal( unknown.label() ) << "  ";
  }
  return;
}

//void printPEstimates( class thermal::analysis::Kernal popteaCore ,
//                      const class physicalModel::TBCsystem TBCSystem)
//{
//  BOOST_FOREACH(class math::estimation::unknown &unknown,
//                LMA.unknownParameters.vectorUnknowns)
//  {
//    std::cout << TBCSystem.returnVal( unknown.label() ) << "  ";
//  }

////  LMA.LMA_workspace.MSE = MSE(
////        popteaCore.L_end,
////        LMA.LMA_workspace.emissionExperimental,
////        LMA.LMA_workspace.predicted);

////  std::cout << std::setprecision(10) << popteaCore.LMA.LMA_workspace.MSE;
////  std::cout << std::setprecision(6)  << "\n";

//  return;
//}
