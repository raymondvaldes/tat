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
#ifndef PHYSICALMODEL_HPP
#define PHYSICALMODEL_HPP

#include <boost/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap/list_of.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/assign/list_inserter.hpp>
#include <boost/property_tree/ptree.hpp>

//#include "numSimulations/Numerical_PhaseOfEmission.h"

class property
{
private:
    static constexpr bool tempDependent = false;
    double Current(const double temperature) const;

    double Projected(const double temperature1, const double temperature2)const;

public:
    double offset;
    double slope;

    explicit property(const double offset_,const double slope_);
    explicit property(void);

    double Current(const std::vector<std::vector<double>>& T, const size_t n,
                   const size_t j) const;

    double Current(const std::vector<std::vector<double>>& T, const size_t n,
                   const size_t j1, const size_t j2) const;


    double Current(const class Temperature Tprofile, const size_t n,
                   const size_t j) const;

    double Current(const class Temperature Tprofile, const size_t n,
                   const size_t j1, const size_t j2) const;


    double Projected(const std::vector<std::vector<double>>& T,
                               const size_t n, const size_t j) const;

    double Projected(const std::vector<std::vector<double>>& T, const size_t n,
                     const size_t j1, const size_t j2) const;

    double Projectedt(const std::vector<std::vector<double>>& T,
                      const size_t n, const size_t, const size_t j) const;

    double Projected(const class Temperature Tprofile,
                               const size_t n, const size_t j) const;

    double Projected(const class Temperature Tprofile, const size_t n,
                     const size_t j1, const size_t j2) const;

    double Projectedt(const class Temperature Tprofile,
                                const size_t n, const size_t, const size_t j)
                                const;
    static class property
        loadConfigfromXMLTree(const boost::property_tree::ptree pt);


};

namespace physicalModel
{

class labels
{
public:
  enum class Name: uint8_t
  {
    gammaEff,
    asub,
    E1,
    R1,
    lambda
  };

  typedef boost::bimap< enum Name , std::string > NameBiTYPE;
  const NameBiTYPE nameMap =
      boost::assign::list_of < NameBiTYPE::relation >
   ( Name::gammaEff , "gammaEff")
   ( Name::asub     , "asub")
   ( Name::E1       , "E1")
   ( Name::R1       , "R1")
   ( Name::lambda   , "lambda");

  explicit labels(void);
  explicit labels(const enum Name name_);
  Name getName(void) const;

private:
  enum Name name;
};

class temperatureScale
{
public:
    double tolerance;
    double referance;
    double base;
    double rear;

    explicit temperatureScale(const double tolerance_,const double referance_,
                              const double base_, const double rear_);
    static struct temperatureScale
        loadConfigfromXML( const boost::property_tree::ptree pt );
    ~temperatureScale( void );
    void load(const std::string &filename);
    void save(const std::string &filename);
};

class radiativeSysProp
{
public:
    double R0;
    double R1;
    double Emit1;
    explicit radiativeSysProp(const double R0_, const double R1_,
                              const double Emit1_);
    static class radiativeSysProp
        loadConfig( const boost::property_tree::ptree pt );
    void load(const std::string &filename);
    void save(const std::string &filename);
    ~radiativeSysProp(void);
};

class layer
{
public:
    class property kthermal;
    class property psithermal;
    double depth;
    double lambda;
    double c = 1;

    double opticalPenetration(void) const;
    double thermalDiffusivity(void) const;
    double thermalEffusivity(void) const;

    explicit layer( const class property kthermal_,
                    const class property psithermal_,
                    const double depth_, const double lambda_);
    ~layer(void);
    static class layer
      loadConfigfromXMLTree( const boost::property_tree::ptree pt );
};

class TBCsystem
{
public:
    class layer coating;
    class layer substrate;
    class temperatureScale Temp;
    class radiativeSysProp optical;
    double radius;
    double Rtc;
    double gamma;
    double a_sub;

    explicit TBCsystem( const class layer coating_,
                        const class layer substrate_,
                        const struct temperatureScale Temp_,
                        const struct radiativeSysProp optical_,
                        const double radius_);
    ~TBCsystem(void);

    void updateVal(const enum labels::Name mylabel , const double val);
    double returnVal( const enum labels::Name mylabel ) const;

    static class TBCsystem loadConfig(const boost::property_tree::ptree pt);

    double gammaEval(void) const ;
    double a_subEval(void) const;
    void updateCoat(void);
};

}
#endif // PHYSICALMODEL_HPP
