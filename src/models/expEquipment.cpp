#include "../Header.h"

namespace expEquipment{

Detector::Detector(const double wavelength_, const double radius_)
    :wavelength(wavelength_), radius(radius_)
{
  BOOST_ASSERT_MSG( ( wavelength > 0 )     &&
                    ( radius > 0 ),
                    "check detector inputs\n\n" );
}

Detector::~Detector(void){}

Laser::Laser(const double a, const double b, const double c, const double d):
             offset(c), amplitude(d), Qlaser(a), radius(b)
{
  BOOST_ASSERT_MSG( ( offset > 0 && offset < 1 )     &&
                    ( amplitude > 0 )                &&
                    ( ( amplitude + offset ) <= 1 )  &&
                    ( amplitude <= offset )          &&
                    ( Qlaser > 0 )                   &&
                    ( radius > 0 ),
                    "check laser inputs\n\n" );
  update();
}

void Laser::update(void)
{
    Is = IntensitySteady();
    It = IntensityTransient();
}

void Laser::updateRadius(const double r)
{
  BOOST_ASSERT_MSG( ( r > 0 ), "check laser radius inputs\n\n" );
  radius = r;
  update();
}

void Laser::updatePower(const double Qpower)
{
  BOOST_ASSERT_MSG(Qpower >= 0, "power can't be negaitve \n\n");
  Qlaser = Qpower;
  update();
}

double Laser::area(void) const
{
    return M_PI_2 * radius * radius;
}

double Laser::IntensityTotal(void) const
{
    return Qlaser / area();
}

double Laser::IntensitySteady(void) const
{
    return IntensityTotal() * offset;
}

double Laser::IntensityTransient(void) const
{
    return IntensitySteady() * amplitude;
}

double Laser::thermalSetup(const double lmin_, const double lmax_,
                           const double L_coat, const double kc,
                           const double psic, const size_t L_end_)
{
  BOOST_ASSERT_MSG( ( lmin_ < lmax_ ) , "check min-max logic\n\n" );
  BOOST_ASSERT_MSG( ( L_coat > 0 ) && ( L_end_ > 0 ) , "check L inputs\n\n" );
  BOOST_ASSERT_MSG( ( kc > 0 ) && ( psic > 0 ) , "check kc inputs\n\n" );

  constexpr size_t box = 7;
  constexpr double rangeLim[box] = {1e-3, 1e-2, 1e-1, 1e0, 1e1, 1e2, 1e3};

  BOOST_ASSERT_MSG( ( lmin_ >= rangeLim[0] ) &&
                    ( lmax_ <= rangeLim[box-1] )  , "check min-max range\n\n" );
  l_min = lmin_;
  l_max = lmax_;
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
        start = ::percentilelog10(rangeLim[i], rangeLim[i+1], l_min);
      }

      double end1 = 1;
      if(l_max >= rangeLim[i+1])
      {
        end1 = 1;
      }
      else if( l_max < rangeLim[i+1] )
      {
        end1 = ::percentilelog10(rangeLim[i], rangeLim[i+1], l_max);
      }

      rangeFills[i] = end1 - start;
    }
  }

  double sum = 0;
  for(size_t i = 0; i < box-1 ; ++i)
  {
    sum += rangeFills[i];
  }

  if( sum > 1)
  {
    L_end = L_end_;
    L_end *=sum;
  }
  else if(sum <= 1)
  {
    L_end = L_end_;
  }

  updateNMeasurements();
  ::range1og10(l_min, l_max, L_end, l_thermal);

  for (size_t i=0; i < L_end; ++i )
  {
    omegas[i] = ::omega(L_coat, l_thermal[i], kc, psic);
  }

  return L_end;
}


void Laser::updateNMeasurements()
{
  omegas.resize(L_end);
  l_thermal.resize(L_end);
}

Laser::~Laser(){}


setup::setup(struct Laser laser_, struct Detector detector_)
    : laser(laser_), detector(detector_) {}

class setup setup::loadConfigfromXML( const boost::property_tree::ptree pt )
{
    //initialize laser
    const double power      = pt.get< double >( "Laser.power" );
    const double radius     = pt.get< double >( "Laser.radius" );
    const double offset     = pt.get< double >( "Laser.offset" );
    const double amplitude  = pt.get< double >( "Laser.amplitude" );
    const class Laser CO2Laser( power, radius, offset, amplitude );

    //initialize detector
    const double detector_rad = pt.get< double >( "Detector.radius" );
    const double detector_lam = pt.get< double >( "Detector.lambda" );
    const class Detector Emissiondetector( detector_lam, detector_rad );

    //initialize experimental setup object
    const class setup expSetup( CO2Laser, Emissiondetector );

    return expSetup;
}


class setup setup::loadConfig(const std::string &filename)
{
  //Initialize the config file into memory
  using boost::property_tree::ptree;
  ptree pt;
  read_xml(filename, pt);

  //initialize laser
  const double
  power = pt.get<double>( "poptea.experimentalSetup.Laser.power" );

  const double
  radius = pt.get<double>( "poptea.experimentalSetup.Laser.radius" );

  const double
  offset = pt.get<double>( "poptea.experimentalSetup.Laser.offset" );

  const double
  amplitude = pt.get<double>( "poptea.experimentalSetup.Laser.amplitude" );

  //initialize detector
  const double
  detector_rad = pt.get<double>( "poptea.experimentalSetup.Detector.radius" );

  const double
  detector_lam = pt.get<double>( "poptea.experimentalSetup.Detector.lambda" );

  //initialize experimental setup object
  const class Laser CO2Laser( power, radius, offset, amplitude );
  const class Detector Emissiondetector( detector_lam, detector_rad );

  const class setup expSetup( CO2Laser, Emissiondetector );

  return expSetup;
}



}
