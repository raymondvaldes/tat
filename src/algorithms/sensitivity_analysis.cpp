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
#include "algorithms/sensitivity_analysis.hpp"
#include "algorithms/statistical_tools.hpp"
#include "thermal/emission/noise.hpp"
#include "thermal/emission/phase99.hpp"
#include "thermal/analysis/poptea.hpp"
#include "thermal/analysis/kernal.hpp"
#include "math/utility.hpp"
#include "math/numIntegration/gslfunc.hpp"

void fitting(class thermal::analysis::Poptea poptea, double *xInitial,
             const size_t interants)
{
  const size_t N = poptea.LMA.unknownParameters.Nsize();

/// Scale jacobian if enabled
  double *xpredicted = new double[N];
  std::ofstream myfile;
  std::stringstream filename;
  filename <<  "../data/fittingData.dat";
  myfile.open(filename.str().c_str());
  myfile << std::setprecision(8);
  myfile << "#run\tasub_0\tgamma_0\tEsigma_0\tR1_0\tlambda_0";
  myfile << "\tasub\tgamma\tEsigma\tR1\tlambda\n";

  double*xSave = new double[N];
  for(size_t i =0 ; i < N ; ++i)
  {
      xSave[i] = xInitial[i];
  }

  for(size_t i=0; i<interants; ++i)
  {
      int nfev;
      int info = 0;
      myfile << i << "\t";

      poptea.LMA.xpredicted =
          poptea.LMA.paramter_estimation( &info, &nfev, poptea.coreSystem,
                                          poptea.thermalData );

      poptea.LMA.LMA_workspace.MSE =
          MSE( poptea.thermalData.l_thermal.size(),
               poptea.LMA.LMA_workspace.emissionExperimental,
               poptea.LMA.LMA_workspace.predicted);

      myfile << poptea.coreSystem.TBCsystem.gammaEval() << "\t"
             << poptea.coreSystem.TBCsystem.a_subEval() << "\t"
             << poptea.coreSystem.TBCsystem.optical.Emit1 << "\t"
             << poptea.coreSystem.TBCsystem.optical.R1<< "\t"
             << poptea.coreSystem.TBCsystem.coating.lambda << "\t"
             << poptea.LMA.LMA_workspace.MSE << "\n";

      printPEstimates( poptea.coreSystem.TBCsystem, poptea.LMA.unknownParameters ) ;


      xInitial = new double[5]{ math::x_ini10(2.3), math::x_ini10(3.8),
          math::x_ini10(42), math::x_ini10(.8), math::x_ini10(0.57) };
  }

  myfile.close();

  delete []xSave;
  delete []xpredicted;

  return;
}

double evaluateUncertainty(const double MSEarea, double* perturbationTable,
                           const std::vector<double>& calibrationTable,
                           size_t xnum)
{
    if(MSEarea < 1e-10)
    {
        return 0;
    }

    double value = 0;
    double*calibration = new double[xnum];
    for(size_t i=0; i<xnum ; ++i)
    {
        calibration[i] = calibrationTable[i];
    }

    struct math::numIntegration::funcClass *Func1;
    Func1 = new struct math::numIntegration::funcClass(perturbationTable, calibration, xnum);

    const double stepsize = fabs(perturbationTable[1] -perturbationTable[0])/1000;
    double perturbation = 0;

    ///Start cycling through the perturbation interpolation table
    double diffminPos = perturbation;
    double diffminOld = MSEarea;

    while(perturbation >= 0
           && perturbation <= perturbationTable[xnum-1])
    {
        value = Func1->eval(perturbation);

        double diffmin = fabs(MSEarea - value);

        if(diffmin < diffminOld)
        {
            diffminPos = perturbation;
            diffminOld = diffmin;
        }

        if( (perturbation+stepsize) <= perturbationTable[xnum-1]  )
        {
            perturbation += stepsize;
        }
        else
        {
            break;
        }
    }

    delete Func1;
    delete[]calibration;

    return diffminPos;
}
