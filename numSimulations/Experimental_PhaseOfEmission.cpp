#include "../Header.h"

void phase99(const size_t L_end,
             const struct parameterStr *parametersStr, double *arrayVal)
{
    /* calculate emission and print */
    size_t n = 0;

//    #pragma omp parallel for schedule(dynamic) private(n)
    for(n = 0 ; n < L_end ; n++ )
    {
//        arrayVal[n] = PhaseOfEmission1DNum(n , parametersStr);
//        arrayVal[n] = PhaseOfEmission2DAna(n, parametersStr) ;
        arrayVal[n] = PhaseOfEmission1DAna(n , parametersStr);
    }

    Print_Emission(parametersStr->laser->l_thermal, arrayVal, arrayVal,
                   parametersStr->laser->l_thermal, L_end);
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

