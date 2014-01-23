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

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <gsl/gsl_math.h>

namespace tools
{

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

}
