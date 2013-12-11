#include "../Header.h"

namespace expEquipment{

Detector::Detector(const double wavelength_, const double radius_)
    :wavelength(wavelength_), radius(radius_)
{}

Detector::Detector(const std::string &filename)
{
  load(filename);
}

void Detector::load(const std::string &filename)
{
  // Create empty property tree object
  using boost::property_tree::ptree;
  ptree pt;

  read_xml(filename, pt);

  radius = pt.get<double>( "Detector.radius" );
  wavelength = pt.get<double>( "Detector.lambda" );
}

void Detector::save(const std::string &filename)
{
  using boost::property_tree::ptree;
  ptree pt;

  pt.put<double>( "Detector.radius", radius );
  pt.put<double>( "Detector.lambda", wavelength );

  write_xml(filename, pt);
}

Detector::~Detector(void){}

Laser::Laser(const double a, const double b, const double c, const double d):
             offset(c), amplitude(d), Qlaser(a), radius(b)
{
    update();
}

Laser::Laser(const std::string &filename)
{
    load(filename);
    update();
}

void Laser::load(const std::string &filename)
{
  // Create empty property tree object
  using boost::property_tree::ptree;
  ptree pt;

  read_xml(filename, pt);

  Qlaser = pt.get<double>( "Laser.power" );
  radius = pt.get<double>( "Laser.radius" );
  offset = pt.get<double>( "Laser.offset" );
  amplitude = pt.get<double>( "Laser.amplitude" );

}

void Laser::save(const std::string &filename)
{
  using boost::property_tree::ptree;
  ptree pt;

  pt.put<double>( "Laser.power", Qlaser );
  pt.put<double>( "Laser.radius", radius );
  pt.put<double>( "Laser.offset", offset );
  pt.get<double>( "Laser.amplitude", amplitude);

  write_xml(filename, pt);
}



void Laser::update(void)
{
    Is = IntensitySteady();
    It = IntensityTransient();
}

void Laser::updateRadius(const double r)
{
    radius = r;
    update();
}

void Laser::updatePower(const double Qpower)
{
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
                           const double psic, const double L_end_)
{
  l_min = lmin_;
  l_max = lmax_;
  /* I need to create a function that determines the number of measurements
  necessary to satisfy L_end_ which is the minimum  number of measurements per
  decade. Once I determine the number of measurements I need then I can use
  the ::rangelog10 function to populate the range.*/

  constexpr size_t box = 7;
  const double rangeLim[box] = {1e-3, 1e-2, 1e-1, 1e0, 1e1, 1e2, 1e3};

  /*check to verify inputs*/
  if(l_min < rangeLim[0] || l_max > rangeLim[box-1])
  {
    std::cout << "error in Laser::thermalSetup" << "\n";
    exit(-1);
  }

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

  std::cout << "this is the size.." << L_end <<"\n\n";


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
