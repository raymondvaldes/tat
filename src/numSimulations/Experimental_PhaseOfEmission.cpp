#include "../Header.h"

void phase99(const size_t L_end,
             class thermalAnalysisMethod::PopTea &poptea, double *arrayVal)
{
  /*The phase for each thermal penetration is calculated in parallel using the
  OpenMP framework.  This gives significant increases in the speed of the code
  for all ranges of L_end.  This also allows the code to be parallelized at
  a very high level. No further modifications of the code is necessary.*/

  size_t n = 0;
  #pragma omp parallel for schedule(dynamic) private(n)
  for(n = 0 ; n < L_end ; n++ )
  {
    arrayVal[n] = PhaseOfEmission1DNum(n , poptea);
//        arrayVal[n] = PhaseOfEmission2DAna(n, poptea);
//        arrayVal[n] = PhaseOfEmission1DAna(n , poptea);
  }

  return;
}

void phase99(const size_t L_end,
             const class thermalAnalysisMethod::PopTea &poptea,
             std::vector<double> &arrayVal)
{
  /*The phase for each thermal penetration is calculated in parallel using the
  OpenMP framework.  This gives significant increases in the speed of the code
  for all ranges of L_end.  This also allows the code to be parallelized at
  a very high level. No further modifications of the code is necessary.*/

  size_t n = 0;
  #pragma omp parallel for schedule(dynamic) private(n)
  for(n = 0 ; n < L_end ; n++ )
  {
    arrayVal[n] = PhaseOfEmission1DNum(n , poptea);
//        arrayVal[n] = PhaseOfEmission2DAna(n, poptea);
//        arrayVal[n] = PhaseOfEmission1DAna(n , poptea);
  }

  return;
}

double Experimental_PhaseOfEmission(double*phase, const size_t L_end)
{
    size_t n=0;
    double *dump = new double[L_end+1];

    ///Open file
    std::ifstream Emission_Dat;
    Emission_Dat.open("data/Emission.dat"); //or whatever the file name is

    while(!Emission_Dat.eof())
    {
        Emission_Dat >> dump[n] >> phase[n];
        if(n>L_end)
            break;
        n++;
    }
    Emission_Dat.close();

    ///Clean Up
    delete [] dump;
    dump = NULL;

    return 0;
}
