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
#include "thermal/emission/noise.hpp"
#include "thermal/emission/phase99.hpp"

void parameterUncertainty(const size_t n,
                          class math::estimation::settings ParaEstSetting,
                          double *xInitial,
                          class thermal::analysis::Kernal popteaCore,
                          const double factorMax, const double factorScale,
                          class perturbStruct *pStruct,
                          const class thermal::emission::ExpNoiseSetting myEmissionNoise,
                          const std::string filename)
{
  /*The idea with the perturbation test is that I have my "perfect fit" and
  then refit each while changing one paramter +-20% for example. */
  const int xnum = pStruct->xnumber;
  const double gammaTrue    = popteaCore.TBCsystem.gammaEval();
  const double a_subTrue    = popteaCore.TBCsystem.a_subEval();
  const double R1True       = popteaCore.TBCsystem.optical.R1;
  const double E_sigmaTrue  = popteaCore.TBCsystem.optical.Emit1;
  const double lambdaTrue   = popteaCore.TBCsystem.coating.lambda;
  const double R0True       = popteaCore.TBCsystem.optical.R0;
  const double lminN  = popteaCore.expSetup.laser.l_thermal[0];
  const double lmaxN  = popteaCore.expSetup.laser.l_thermal[popteaCore.expSetup.laser.L_end-1];
  double*xpredicted = new double[n];
  int nfev;
  int info = 0;

///Input calibration file and read data
  class calibration_curves *CCurves = nullptr;
  CCurves = new class calibration_curves(filename);

///Create Initial Experimental Data
  ///setup the nominal data
  thermal::emission::phase99(popteaCore, popteaCore.LMA.LMA_workspace.emissionNominal);

  ///let the experimental be equal to the nominal data
  for(size_t i =0 ; i < popteaCore.expSetup.laser.L_end; i++)
  {
      popteaCore.LMA.LMA_workspace.emissionExperimental[i]
              = popteaCore.LMA.LMA_workspace.emissionNominal[i];
  }

///Initial Fit to get initial guesses
  constexpr size_t interants = 0;
  fitting(popteaCore, xInitial, interants, factorMax, factorScale);

///prepare output file with parameter uncertainty data
  popteaCore.DataDirectory.mkdir("debug");
  std::ofstream myoutputfile;
  std::stringstream filename1;
  filename1 <<  "../data/ParameterUncertainty.dat";
  myoutputfile.open(filename1.str().c_str());
  myoutputfile << std::setprecision(8);

///Implement iteration
  for(size_t j = 0; j <  pStruct->iterates ; ++j)
  {
    ///setup thermal penetration distribution
    const double lmin = pStruct->lmin[j];
    const double lmax = pStruct->lmax[j];
    constexpr size_t lEndMin = 50;
    popteaCore.thermalSetup(lmin, lmax, lEndMin);

    ///Create Initial Experimental Data
    thermal::emission::phase99(popteaCore, popteaCore.LMA.LMA_workspace.emissionNominal);
    for(size_t i =0 ; i < popteaCore.expSetup.laser.L_end; i++)
    {
        popteaCore.LMA.LMA_workspace.emissionExperimental[i]
        = popteaCore.LMA.LMA_workspace.emissionNominal[i];
    }

    ///add artificial experimental data
//        popteaCore.EmissionNoise(myEmissionNoise,
//                                     popteaCore->emissionNominal, lminN,
//                                     lmaxN); //BUG MUST MOVE

    ///estimate unknown parameters
    paramter_estimation(popteaCore.expSetup.laser.L_end,
                        popteaCore.LMA.unknownParameters.Nsize(),
                        ParaEstSetting, &info, &nfev, xInitial,
                        popteaCore, factorMax, factorScale, xpredicted);
    thermal::emission::phase99(popteaCore, popteaCore.LMA.LMA_workspace.predicted);

    ///develop the uncertainties
    double msearea = MSEarea(popteaCore.expSetup.laser.L_end,
                             popteaCore.LMA.LMA_workspace.emissionNominal,
                             popteaCore.LMA.LMA_workspace.predicted);
    double
    diffUncerntainty = evaluateUncertainty(msearea,
                                           CCurves->perturbation,
                                           CCurves->caliDiff[j],
                                           xnum);
    double
    effUncerntainty = evaluateUncertainty(msearea,
                                          CCurves->perturbation,
                                          CCurves->caliEff[j],
                                          xnum);
    double
    R1Uncerntainty = evaluateUncertainty(msearea,
                                         CCurves->perturbation,
                                         CCurves->caliR1[j],
                                         xnum);
    double
    E1Uncerntainty = evaluateUncertainty(msearea,
                                         CCurves->perturbation,
                                         CCurves->caliEmission[j],
                                         xnum);
    double
    OptUncerntainty = evaluateUncertainty(msearea,
                                          CCurves->perturbation,
                                          CCurves->caliOptical[j],
                                          xnum);

    myoutputfile << pStruct->bands[j] << "\t" << lmin << "\t" << lmax;
    myoutputfile << "\t" << msearea;
    myoutputfile << "\t" << diffUncerntainty << "\t" << effUncerntainty ;
    myoutputfile << "\t" << R1Uncerntainty << "\t" << E1Uncerntainty ;
    myoutputfile << "\t" << OptUncerntainty <<"\n";

    ///Reset Inputs

    BOOST_FOREACH( class math::estimation::unknown &unknown,
                   popteaCore.LMA.unknownParameters.vectorUnknowns )
    {
      switch( unknown.label() )
      {
        case physicalModel::labels::Name::asub :
          popteaCore.TBCsystem.a_sub = a_subTrue;
          break;

        case physicalModel::labels::Name::E1 :
          popteaCore.TBCsystem.optical.Emit1=E_sigmaTrue;
          break;

        case physicalModel::labels::Name::gammaEff :
          popteaCore.TBCsystem.gamma = gammaTrue;
          break;

        case physicalModel::labels::Name::lambda :
          popteaCore.TBCsystem.coating.lambda = lambdaTrue;
          break;

        case physicalModel::labels::Name::R1 :
          popteaCore.TBCsystem.optical.R1 = R1True;
          break;

        default:
          std::cout << "\nSwitch Error!!\n";
          exit(-69);
          break;
      }
    }

    ///Reset Initial Guess
    xInitial[0] = 2.5;
    xInitial[1] = 3.9;
    xInitial[2] = 44;
    xInitial[3] = .83;
    xInitial[4] = .6;
  }

  myoutputfile.close();


  delete []xpredicted;
  CCurves->cleanup();
  delete CCurves;

  return;
}

void fitting(class thermal::analysis::Kernal popteaCore, double *xInitial,
             const size_t interants, const double factorMax,
             const double factorScale)
{
  const size_t P = popteaCore.expSetup.laser.L_end;
  const size_t N = popteaCore.LMA.unknownParameters.Nsize();
  class math::estimation::settings ParaEstSetting(popteaCore.LMA.Settings);


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

      paramter_estimation(P, N, ParaEstSetting, &info, &nfev,
                          xInitial, popteaCore, factorMax, factorScale,
                          xpredicted);
      popteaCore.LMA.LMA_workspace.MSE =
          MSE(popteaCore.expSetup.laser.L_end,
              popteaCore.LMA.LMA_workspace.emissionExperimental,
              popteaCore.LMA.LMA_workspace.predicted);

      myfile << popteaCore.TBCsystem.gammaEval() << "\t"
             << popteaCore.TBCsystem.a_subEval() << "\t"
             << popteaCore.TBCsystem.optical.Emit1 << "\t"
             << popteaCore.TBCsystem.optical.R1<< "\t"
             << popteaCore.TBCsystem.coating.lambda << "\t"
             << popteaCore.LMA.LMA_workspace.MSE << "\n";

      printPEstimates( popteaCore ) ;
      xInitial = new double[5]{x_ini10(2.3), x_ini10(3.8), x_ini10(42),
              x_ini10(.8), x_ini10(0.57)};
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

    struct funcClass *Func1;
    Func1 = new struct funcClass(perturbationTable, calibration, xnum);

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
