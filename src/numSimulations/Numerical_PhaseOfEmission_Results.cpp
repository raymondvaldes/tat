/*----------------------------------------------------------------------------*\
  ========                |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |        
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||   	  						|
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
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <iomanip>
#include <gsl/gsl_math.h>

#include "numSimulations/Numerical_PhaseOfEmission_Results.h"

double Print_Emission(const double *phase, const double* num_phase,
                      const double *ana_phase,const double *l_thermal,
                      const size_t L_end)
{
    ///output data for printing
    std::ofstream myoutputfile;
    std::stringstream filename;
    filename <<  "../data/EmissionHERE.dat";
    myoutputfile.open(filename.str().c_str());
    myoutputfile << std::setprecision(16);

    for(size_t i = 0 ; i < L_end; ++i)
    {
        myoutputfile << l_thermal[i] << "\t";
        myoutputfile << phase[i] << "\n";
    }
    myoutputfile.close();

    ///output data for printing
    std::ofstream myoutputfile1;
    std::stringstream filename2;
    filename2 <<  "../data/Emission_error.dat";
    myoutputfile1.open(filename2.str().c_str());
    myoutputfile1 << std::setprecision(16);

    for(size_t i = 0 ; i < L_end; ++i)
    {
        myoutputfile1 << l_thermal[i] << "\t";
        myoutputfile1 <<  100*((num_phase[i]  - ana_phase[i])/M_PI_2) << "\n";
    }
    myoutputfile1.close();
  return 0;
}




calibration_curves::calibration_curves(const std::string filename)
{
    std::ifstream myfile;
    myfile.open(filename); //or whatever the file name is

    if(myfile.is_open())
    {
        //read input parameters
        myfile.good();
        myfile >> range >> spread >> increments;
        myfile.good();
        myfile >> RangeN;
        myfile.good();
        myfile >> asubRef >> gammaRef >> E1Ref >> R1Ref >> lambdaRef;

        std::cout << range << "\t" <<  spread << "\t" << increments << "\t" <<
        RangeN << "\t" << asubRef << "\t" <<
        gammaRef << "\t" << E1Ref << "\t" << R1Ref << "\t" << lambdaRef;

        ///allocate space for the vectors
        for (size_t i = 0; i < RangeN; ++i)
        {
            // Move push_back() into the outer loop so it's called once per
            // iteration of the x-loop
            caliDiff.push_back(std::vector <double> ());
            caliEff.push_back(std::vector <double> ());
            caliR1.push_back(std::vector <double> ());
            caliEmission.push_back(std::vector <double> ());
            caliOptical.push_back(std::vector <double> ());
            for (size_t j = 0; j< spread; ++j)
            {
                caliDiff[i].push_back(j);
                caliEff[i].push_back(j);
                caliR1[i].push_back(j);
                caliEmission[i].push_back(j);
                caliOptical[i].push_back(j);
            }
        }

        perturbation = new double[spread];
        myfile.good();
        for (size_t j = 0; j< spread; ++j)
        {
            myfile >> perturbation[j];
        }

        bandsize = new double[RangeN];
        double dump;
        for (size_t i = 0; i < RangeN; ++i)
        {
            myfile.good();
            myfile >> dump >> bandsize[i] >> dump >> dump;

            for (size_t j = 0; j < spread; ++j)
            {myfile >> caliDiff[i][j];   }
            for (size_t j = 0; j < spread; ++j)
            {myfile >> caliEff[i][j];    }
            for (size_t j = 0; j < spread; ++j)
            {myfile >> caliR1[i][j];     }
            for (size_t j = 0; j < spread; ++j)
            {myfile >> caliEmission[i][j];}
            for (size_t j = 0; j < spread; ++j)
            {myfile >> caliOptical[i][j];}
        }
        myfile.close();
    }
    else
    {
        std::cout << "Unable to open file"; exit(-23);
    }
}

void calibration_curves::cleanup()
const
{
    delete[] perturbation;
    delete[] bandsize;
}


