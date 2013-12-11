#include "../Header.h"

double property::Current(const double temperature) const
{
    if(!tempDependent) return offset;

    double
    currT = temperature;
    currT *= slope;
    currT += offset;

    return currT;
//        return offset + slope * temperature;
}

double property::Projected(const double temperature1, const double temperature2)
const
{
    if(!tempDependent) return offset;

    double
    projT = temperature1;
    projT -= temperature2;
    projT *= slope;
    projT += Current(temperature1) ;

    return projT;
//        return Current(temperature1) + slope * (temperature1 - temperature2);
}

double property::Current(const std::vector<std::vector<double>>& T, const size_t n,
               const size_t j) const
{
    if(!tempDependent) return offset;

    return offset + slope * T[n][j];
}

double property::Current(const std::vector<std::vector<double>>& T, const size_t n,
               const size_t j1, const size_t j2) const
{
    if(!tempDependent) return offset;

    return mean( Current( T[n][j1] ) , Current( T[n][j2] ) );
}


double property::Current(const class Temperature Tprofile, const size_t n,
               const size_t j) const
{
    if(!tempDependent) return offset;

    return offset + slope * Tprofile.eval(n,j);
}

double property::Current(const class Temperature Tprofile, const size_t n,
               const size_t j1, const size_t j2) const
{
    if(!tempDependent) return offset;

    return mean( Current( Tprofile.eval(n, j1 ) ) ,
                 Current( Tprofile.eval(n,j2  ) ) );
}


double property::Projected(const std::vector<std::vector<double>>& T,
                           const size_t n, const size_t j) const
{
    if(!tempDependent) return offset;

    if( n == 0 ) return Current( T[n][j] );


    return Current(T[n][j]) + slope * (T[n][j] - T[n-1][j]);
}

double property::Projected(const std::vector<std::vector<double>>& T, const size_t n,
                 const size_t j1, const size_t j2)
const
{
    if(!tempDependent) return offset;
    if( n == 0 )
    {
        return mean( Current(  T[n][j1] ) , Current( T[n][j2] ) );
    }

    return mean( Projected(T, n, j1), Projected(T, n, j2) );
}

double property::Projectedt(const std::vector<std::vector<double>>& T,
                            const size_t n,const size_t /*n1*/, const size_t j)
const
{
    if(!tempDependent) return offset;

    return mean( Current(T, n, j) ,  Projected(T, n, j));
}

double property::Projected(const class Temperature Tprofile,
                           const size_t n, const size_t j) const
{
    if(!tempDependent) return offset;

    if( n == 0 ) return Current( Tprofile.eval(n,j) );


    return Current(Tprofile.eval(n,j)) + slope * (Tprofile.eval(n,j) -
                                        Tprofile.eval(n-1,j));
}

double property::Projected(const class Temperature Tprofile, const size_t n,
                 const size_t j1, const size_t j2)
const
{
    if(!tempDependent) return offset;
    if( n == 0 )
    {
        return mean( Current(  Tprofile.eval(n,j1) ) ,
                    Current( Tprofile.eval(n,j2) ) );
    }

    return mean( Projected(Tprofile, n, j1), Projected(Tprofile, n, j2) );
}

double property::Projectedt(const class Temperature Tprofile,
                            const size_t n,const size_t /*n1*/, const size_t j)
const
{
    if(!tempDependent) return offset;

    return mean( Current(Tprofile, n, j) ,  Projected(Tprofile, n, j));
}

property::property(const double offset_,const double slope_)
    : offset(offset_), slope(slope_)
{}

property::property(void){}

class property
    property::loadConfigfromXMLTree(const boost::property_tree::ptree pt)
{
  const double offset_ = pt.get<double>( "offset" );
  const double slope_ = pt.get<double>( "slope" );
  return property(offset_, slope_);
}


namespace physicalModel
{
temperatureScale::temperatureScale(const double tolerance_,
                                   const double referance_,
                                   const double base_, const double rear_):
    tolerance(tolerance_), referance(referance_), base(base_), rear(rear_)
{}

temperatureScale::~temperatureScale( void ) { }

struct temperatureScale
        temperatureScale::loadConfigfromXML( const boost::property_tree::ptree pt )
{
  //initialize parameter estimation settings
  const double tolerance    = pt.get<double>( "tolerance" );
  const double referance    = pt.get<double>( "referance" );
  const double base         = pt.get<double>( "base" );
  const double rear         = pt.get<double>( "rear" );

  struct temperatureScale TemperatureScale(tolerance, referance, base, rear);
  return TemperatureScale;
}

struct temperatureScale
        temperatureScale::loadConfig(const std::string &filename)
{
  ///Initialize the config file into memory
  using boost::property_tree::ptree;
  ptree pt;
  read_xml(filename, pt);

  //initialize parameter estimation settings
  const double
  tolerance = pt.get<double>( "poptea.TBCsystem.TemperatureScale.tolerance" );

  const double
  referance = pt.get<double>( "poptea.TBCsystem.TemperatureScale.referance" );

  const double
  base = pt.get<double>( "poptea.TBCsystem.TemperatureScale.base" );

  const double
  rear = pt.get<double>( "poptea.TBCsystem.TemperatureScale.rear" );

  struct temperatureScale TemperatureScale(tolerance, referance, base, rear);
  return TemperatureScale;
}


radiativeSysProp::radiativeSysProp( const double R0_, const double R1_,
                                    const double Emit1_)
    : R0(R0_), R1(R1_), Emit1(Emit1_)
{}

radiativeSysProp::~radiativeSysProp( void ) {}

class radiativeSysProp
    radiativeSysProp::loadConfig( const boost::property_tree::ptree pt )
{
  const double R0_ = pt.get<double>("R0");
  const double R1_ = pt.get<double>("R1");
  const double Emit1_ = pt.get<double>("Emit1");

  class radiativeSysProp Obj( R0_, R1_, Emit1_);

  return Obj;
}

layer::layer( const property kthermal_, const property psithermal_,
              const double depth_, const double lambda_ )
    : kthermal( kthermal_ ), psithermal( psithermal_ ), depth( depth_ ),
      lambda( lambda_ )
{}

double layer::opticalPenetration(void) const
{
  return lambda * depth;
}

double layer::thermalDiffusivity( void ) const
{
  return thermal::diffusivity( kthermal.offset, psithermal.offset );
}
double layer::thermalEffusivity( void ) const
{
  return thermal::effusivity( kthermal.offset, psithermal.offset );
}

layer::~layer(void){}

class layer layer::loadConfigfromXMLTree(const boost::property_tree::ptree pt)
{
  const boost::property_tree::ptree branch1 = pt.get_child("conductivity");
  const property conductivity_ = property::loadConfigfromXMLTree(branch1);

  const boost::property_tree::ptree branch2 = pt.get_child("thermalmass");
  const property thermalMass_  = property::loadConfigfromXMLTree(branch2);

  const double lambda_ = pt.get<double>("lambda");
  const double length_ = pt.get<double>("length");

  class layer layerObj(conductivity_, thermalMass_, length_, lambda_ );
  return layerObj;
}

TBCsystem::TBCsystem( const class layer coating_, const class layer substrate_,
                      const struct temperatureScale Temp_,
                      const struct radiativeSysProp optical_,
                      const double radius_)
    : coating(coating_), substrate(substrate_), Temp(Temp_), optical(optical_),
      radius(radius_)
{
    gamma = gammaEval();
    a_sub = a_subEval();
}
TBCsystem::~TBCsystem(void){}

class TBCsystem TBCsystem::loadConfig(const boost::property_tree::ptree pt)
{  
  using boost::property_tree::ptree;

  const ptree pcoat = pt.get_child( "coating" );
  const class layer coating_( layer::loadConfigfromXMLTree( pcoat ) );

  const ptree psub = pt.get_child( "substrate" );
  const class layer substrate_( layer::loadConfigfromXMLTree( psub ) );

  const ptree ptmp = pt.get_child( "TemperatureScale" );
  const class temperatureScale Temp_( temperatureScale::loadConfigfromXML( ptmp ) );

  const ptree prad = pt.get_child( "RadiationProperties" );
  const class radiativeSysProp optical_( radiativeSysProp::loadConfig( prad ) );

  const double radius_ = pt.get< double >( "radialDomain" );

  const class TBCsystem TBCsystemObj( coating_, substrate_, Temp_, optical_,
                                     radius_ );
  return  TBCsystemObj;
}


double TBCsystem::gammaEval(void) const
{
  return substrate.thermalEffusivity() / coating.thermalEffusivity();
}

double TBCsystem::a_subEval(void) const
{
  return sqrt(substrate.thermalDiffusivity() / coating.thermalDiffusivity());
}

void TBCsystem::updateCoat(void)
{
  const double effusivity_coat = substrate.thermalEffusivity() / gamma;
  const double diffusivty_coat = substrate.thermalDiffusivity() / pow(a_sub,2);

  coating.psithermal.offset = effusivity_coat / sqrt(diffusivty_coat);
  coating.kthermal.offset = coating.psithermal.offset * diffusivty_coat;
  return;
}

labels::labels(void) {}

labels::labels(const Name name_):name(name_){}

enum labels::Name labels::getName(void)
{
  return name;
}



}
