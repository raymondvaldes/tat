#ifndef SENSITIVITY_PAPER_HPP_INCLUDED
#define SENSITIVITY_PAPER_HPP_INCLUDED

#include "numSimulations/Numerical_Setup.h"
#include "numSimulations/Numerical_PhaseOfEmission.h"
#include "numSimulations/Experimental_PhaseOfEmission.h"
#include "algorithms/sensitivity_analysis.hpp"
#include "algorithms/ThermalProp_Analysis.h"

namespace SensitivityValdes2013
{
    struct parameter_constraints;
    void figureSensitivityIntro(class thermalAnalysisMethod::PopTea poptea);


    void CC_APS2(class thermalAnalysisMethod::PopTea poptea);

}

#endif // SENSITIVITY_PAPER_HPP_INCLUDED
