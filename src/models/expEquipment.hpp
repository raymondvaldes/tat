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
#ifndef EXPEQUIPMENT_HPP_INCLUDED
#define EXPEQUIPMENT_HPP_INCLUDED

#include <boost/property_tree/xml_parser.hpp>


namespace equipment{

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

  double l_min, l_max; ///MUST REMOVE

public:
  double Qlaser;
  double radius;
  double Is;
  double It;

  size_t L_end;     ///MUST REMOVE

  std::vector<double> omegas; ///MUST REMOVE
  std::vector<double> l_thermal;  ///MUST REMOVE

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
  static class setup loadConfigfromXML( const boost::property_tree::ptree pt );
};


}


#endif // EXPEQUIPMENT_HPP_INCLUDED

