/*----------------------------------------------------------------------------*\
  ========                |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||                   |
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
#include <vector>
#include "thermal/analysis/poptea.hpp"
#include "thermal/analysis/kernal.hpp"
#include "thermal/emission/phase99.hpp"
#include "thermal/analysis/lmdiff_poptea.hpp"
#include "thermal/analysis/lmdiff_poptea_help.hpp"


#include "math/estimation/parameterestimation.hpp"
#include "math/estimation/lmdiff.hpp"
#include "math/estimation/lmdiff_helper.hpp"
#include "math/estimation/utils.hpp"
#include "math/utility.hpp"
#include "math/estimation/constrained.hpp"
#include "algorithms/ThermalProp_Analysis.h"

namespace thermal {
namespace analysis{  

Poptea::Poptea( const class Kernal coreSystem_ ,
                const class math::estimation::settings Settings_,
                const class math::estimation::unknownList unknownParameters_)
  : coreSystem( coreSystem_ ),  LMA(Settings_, unknownParameters_),
    SA(1) //TEMP BUG TODO
{


  /// Heat Transfer and Emission models
  const double l_min = .04;
  const double l_max = 4;
  const size_t LendMinDecade = 50;

  // Populate the experimental phase values in parameters99


  thermalSetup( l_min, l_max, LendMinDecade );
}

class Poptea
Poptea::loadConfig( const class Kernal &coreSystem_,
                    boost::property_tree::ptree pt )
{
  using boost::property_tree::ptree;

  const std::string conjunto = "poptea.";
  const ptree ptchild4 = pt.get_child( conjunto + "ParaEstSettings" );
  const class math::estimation::settings
    Obj4( math::estimation::settings::loadConfigfromXML( ptchild4 ) );

  const ptree ptchild5 = pt.get_child( conjunto );
  const class math::estimation::unknownList
    Obj5( math::estimation::unknownList::loadConfigfromXML( ptchild5 ) );



  //Load class object from previous objects
  class Poptea poptea( coreSystem_, Obj4, Obj5);

  return poptea;
}

Poptea::~Poptea(void){}

void Poptea::setThermalRange( const double lmin, const double lmax )
{

}
void Poptea::loadExperimentalData( const std::vector<double> data )
{}
//void Poptea::setParameterstoFit( class math::estimation::unknownList parameters )
//{
////  unknownParameters = parameters;
//}
//void Poptea::setParametertoHoldX( enum physicalModel::labels::Name currentParameterX_)
//{
////  currentParameterX = currentParameterX_;
////  currentParameter = unknownParameterswithBFdata.getParameter( currentParameterX_ );
//  return;
//}
//double Poptea::Gfunc( const double x )
//{
//  ///Gfunc must work by updating kernal with unknown parameters
//  ///updating experimental with predicted values;

////  unknownParameterswithBFdata.

//  double val = x * 1;


////  TBCsystem::updateVal( currentParameterX , val );


////  current_PHASE_BF


//  return meanError( current_PHASE_BF , ref_PHASE_BF );

//}
//std::pair< double, double >
//Poptea::Gsolve( enum physicalModel::labels::Name currentParameterX_ )
//{
//  double lowerLimit(1);
//  double upperLimit(2);

//  std::pair <double,double> limits (lowerLimit, upperLimit);
//  return limits;
//}
//void Poptea::saveBestFitParameters( void )
//{

//}
//void Poptea::setG1(void)
//{

//}
//double Poptea::meanError( const std::vector<double> curveBF,
//                          const std::vector<double> curveRef )
//{
//  const size_t N = curveBF.size();
//  double error = 0;


//  for(size_t n=0 ; n < N ;  ++n)
//  {
//      error += pow( ( curveBF[n] / curveRef[n] - 1 ), 2);
//  }

//  return sqrt(error / N );
//}
//double Poptea::bestFit( class Kernal core )
//{
//  int nfev;
//  int info = 0;

//  core.LMA.xpredicted = paramter_estimation( core, &info, &nfev );
//  current_PHASE_BF = core.LMA.LMA_workspace.emissionCurrent;
//  S1_current = meanError( current_PHASE_BF , ref_PHASE_BF );

//  return S1_current;
//}
//std::pair< double, double >
//Poptea::parameterInterval(const enum physicalModel::labels::Name currentPx ,
//                          std::vector<double> emissionExperimental)
//{
//  //Step 1
//  loadExperimentalData( emissionExperimental );

//  //Step 2
//  bestFit( coreSystem );

//  //Step 3 Rebuild Core
//  //rebuild unknown list;

////  class kernal coreRebuild( coreSystem.expSetup ,
////                            coreSystem.TBCsystem,
////                            coreSystem.thermalsys,
////                            coreSystem.LMA.Settings,
////                            rebuiltSubSystem,
////                            coreSystem.DataDirectory
////                            )

////      Kernal( class equipment::setup expSetup_,
////              class physicalModel::TBCsystem TBCsystem_,
////              class thermal::model thermalsys_,
////              class math::estimation::settings Settings_,
////              class math::estimation::unknownList unknownParameters_,
////              class filesystem::directory DataDirectory_ ) ;


//  double lowerLimit(1);
//  double upperLimit(2);
//  std::pair <double,double> limits (lowerLimit, upperLimit);
//  return limits;
//}


void Poptea::thermalSetup( const double lmin_, const double lmax_,
                           const size_t LendMin )
{
  const double L_end = thermalSetupTEMP( lmin_, lmax_,
                            coreSystem.TBCsystem.coating.depth,
                            coreSystem.TBCsystem.coating.kthermal.offset,
                            coreSystem.TBCsystem.coating.psithermal.offset ,
                                         LendMin);

  LMA.LMA_workspace.updateArraySize( L_end, LMA.unknownParameters.Nsize()  );
}

double  Poptea::thermalSetupTEMP( const double l_min, const double l_max,
                                  const double L_coat, const double kc,
                                  const double psic, const size_t L_end )
{
  BOOST_ASSERT_MSG( ( l_min < l_max ) , "check min-max logic\n\n" );
  BOOST_ASSERT_MSG( ( L_coat > 0 ) && ( L_end > 0 ) , "check L inputs\n\n" );
  BOOST_ASSERT_MSG( ( kc > 0 ) && ( psic > 0 ) , "check kc inputs\n\n" );

  constexpr size_t box = 7;
  constexpr double rangeLim[box] = {1e-3, 1e-2, 1e-1, 1e0, 1e1, 1e2, 1e3};

  BOOST_ASSERT_MSG( ( l_min >= rangeLim[0] ) &&
                    ( l_max <= rangeLim[box-1] )  , "check min-max range\n\n" );

  /* I need to create a function that determines the number of measurements
  necessary to satisfy L_end_ which is the minimum  number of measurements per
  decade. Once I determine the number of measurements I need then I can use
  the ::rangelog10 function to populate the range.*/

  double rangeFills[box-1] = {0};
  for(size_t i = 0; i < box-1 ; ++i)
  {
    if( l_min >= rangeLim[i+1]  || l_max <= rangeLim[i])
    {
      rangeFills[i] = 0;
    }
    else if( l_min <= rangeLim[i] && l_max >= rangeLim[i+1])
    {
      rangeFills[i] = 1;
    }
    else
    {
      double start = 0;
      if(l_min <= rangeLim[i])
      {
        start = 0;
      }
      else if( l_min < rangeLim[i+1] )
      {
        start = math::percentilelog10(rangeLim[i], rangeLim[i+1], l_min);
      }

      double end1 = 1;
      if(l_max >= rangeLim[i+1])
      {
        end1 = 1;
      }
      else if( l_max < rangeLim[i+1] )
      {
        end1 = math::percentilelog10(rangeLim[i], rangeLim[i+1], l_max);
      }

      rangeFills[i] = end1 - start;
    }
  }

  double sum = 0;
  for(size_t i = 0; i < box-1 ; ++i)
  {
    sum += rangeFills[i];
  }

  size_t Lnew = L_end;

  if( sum > 1)
  {
    Lnew = L_end;
    Lnew *=sum;
  }
  else if(sum <= 1)  //TODO REMOVE?
  {
    Lnew = L_end;
  }

  updateNMeasurements( Lnew );
  math::range1og10(l_min, l_max, Lnew, l_thermal);

  for (size_t i=0; i < Lnew; ++i )
  {
    omegas[i] = thermal::omega(L_coat, l_thermal[i], kc, psic);
  }

  return Lnew;
}


void  Poptea::updateNMeasurements( const double L_end )
{
  omegas.resize(L_end);
  l_thermal.resize(L_end);
}




}}
