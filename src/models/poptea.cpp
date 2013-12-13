#include "../Header.h"

namespace thermalAnalysisMethod
{

PopTea::PopTea(class expEquipment::setup expSetup_,
               class physicalModel::TBCsystem TBCsystem_,
               class thermal::ThermalModelSelection thermalModel_,
               class parameterEstimation::settings Settings_,
               class parameterEstimation::unknownList unknownParameters_,
               class filesystem::directory DataDirectory_)
  : expSetup(expSetup_),
    TBCsystem(TBCsystem_),
    thermalModel(thermalModel_),
    LMA(Settings_, unknownParameters_),
    DataDirectory(DataDirectory_)
{
  DataDirectory.mkdir("data");

  const size_t d = LMA.unknownParameters.Nsize();

  xParametersNames.resize(d);
  xParameters95Names  .resize(d);
  N95 = d;

  thermalModel.iter = 1000;
  LMA.LMA_workspace.MSETol = 1e-8;

  /// Heat Transfer and Emission models
  const double l_min = .04;
  const double l_max = 4;
  const size_t LendMinDecade = 50;

  // Populate the experimental phase values in parameters99
  expSetup.laser.L_end = LendMinDecade;
  expSetup.q_surface = 0;
  thermalSetup(l_min, l_max, LendMinDecade);
}

class thermalAnalysisMethod::PopTea
        PopTea::loadConfig(const std::string &filename,
                           const filesystem::directory DataDirectory_)
{
  using boost::property_tree::ptree;
  ptree pt;
  read_xml(filename, pt);
  const std::string conjunto = "poptea.";

  const ptree ptchild1 = pt.get_child( conjunto + "experimentalSetup" );
  const class expEquipment::setup
    Obj1( expEquipment::setup::loadConfigfromXML( ptchild1 ) );

  const ptree ptchild2 = pt.get_child( conjunto + "TBCsystem" );
  const class physicalModel::TBCsystem
    Obj2( physicalModel::TBCsystem::loadConfig( ptchild2 ) );

  const ptree ptchild3 = pt.get_child( conjunto + "thermalModel" );

  ////TODO BUG REMOVE THIS TEMPORARY FIX
  const size_t M2     = ptchild3.get<size_t>( "mesh.M2" );
  const size_t Rend   = ptchild3.get<size_t>( "mesh.Rend");
  const size_t Nend   = ptchild3.get<size_t>( "mesh.Nend" );
  const double beta1  = ptchild3.get<double>( "mesh.beta1" );
  const double split  = ptchild3.get<double>( "mesh.split" );
  class numericalModel::Mesh mesh(M2, Rend, Nend, beta1, split,
                                  Obj2.coating.depth,
                                  Obj2.substrate.depth,
                                  Obj1.laser.radius,
                                  Obj2.radius);

  ////TODO BUG REMOVE THIS TEMPORARY
  const class thermal::ThermalModelSelection
    Obj3( thermal::ThermalModelSelection::loadConfigfromXML( ptchild3, mesh ) );

  const ptree ptchild4 = pt.get_child( conjunto + "ParaEstSettings" );
  const class parameterEstimation::settings
    Obj4( parameterEstimation::settings::loadConfigfromXML( ptchild4 ) );

  const ptree ptchild5 = pt.get_child( conjunto );
  const class parameterEstimation::unknownList
    Obj5( parameterEstimation::unknownList::loadConfigfromXML( ptchild5 ) );

    //Load class object from previous objects
  class PopTea popTea( Obj1, Obj2, Obj3, Obj4, Obj5 , DataDirectory_);

  return popTea;
}

PopTea::~PopTea(void){}


void PopTea::thermalSetup(const double lmin_, const double lmax_,
                                const size_t LendMin)
{
  expSetup.laser.L_end = expSetup.laser.thermalSetup(lmin_, lmax_,
                                      TBCsystem.coating.depth,
                                      TBCsystem.coating.kthermal.offset,
                                      TBCsystem.coating.psithermal.offset ,
                                      LendMin);

  LMA.LMA_workspace.updateArraySize(expSetup.laser.L_end,
                                    LMA.unknownParameters.Nsize());
}

double PopTea::bEval(void) const
{
  return expSetup.laser.radius / TBCsystem.coating.depth;
}

}
