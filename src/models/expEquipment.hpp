#ifndef EXPEQUIPMENT_HPP_INCLUDED
#define EXPEQUIPMENT_HPP_INCLUDED

namespace expEquipment{

class Detector
{
public:
  double wavelength;
  double radius;

  explicit Detector(const double wavelength_, const double radius_);
  ~Detector(void);
};

class Laser
{
private:
  double area(void) const;
  double IntensityTotal(void) const;
  double IntensitySteady(void) const;
  double IntensityTransient(void) const;
  double offset, amplitude;
  void update(void);
  double l_min, l_max;

public:
  double Qlaser;
  double radius;
  double Is;
  double It;

  size_t L_end;

  std::vector<double> omegas;
  std::vector<double> l_thermal;

  explicit Laser(const double a, const double b, const double c,
                 const double d);

  ~Laser();

  void updateRadius(const double r);
  void updatePower(const double Qpower);
  double thermalSetup(const double lmin_, const double lmax_,
                      const double L_coat, const double kc, const double psic,
                      const size_t L_end_);
  void updateNMeasurements();
};

class setup
{
public:
  class Laser laser;
  struct Detector detector;
  double q_surface;

  explicit setup(struct Laser laser_, struct Detector detector_);
  static class setup loadConfig(const std::string &filename);
  static class setup loadConfigfromXML( const boost::property_tree::ptree pt );
};


}


#endif // EXPEQUIPMENT_HPP_INCLUDED

