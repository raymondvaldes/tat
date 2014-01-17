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
#ifndef PARAMETERESTIMATION_HPP
#define PARAMETERESTIMATION_HPP

#include "models/physicalmodel.hpp"

namespace parameterEstimation{

class unknown
{
private:
  struct bounds
  {
    const double lower;
    const double upper;
    bounds(const double lower_, const double  upper_);
  };
  struct physicalModel::labels name;
  struct bounds constraint;
  double initialGuess;
  double bestfitval;

public:
  explicit unknown(enum physicalModel::labels::Name name_,
          const double lower_,
          const double upper_);
  explicit unknown(enum physicalModel::labels::Name name_,
          const double lower_,
          const double upper_,
          const double initialGuess_);

  void bestfitset(const double input);
  double bestfit(void);
  double upperBound(void);
  double lowerBound(void);
  void Initialauto(void);
  void Initialset(const double input);
  double initialVal(void);


  enum physicalModel::labels::Name label(void);

};

class unknownList
{
private:
  size_t N;

public:
  std::vector<class unknown> vectorUnknowns;
  void addUnknown(physicalModel::labels::Name name,
                  const double lower,
                  const double upper);
  size_t Nsize(void);
  void NAssign(size_t xInput);


  static class unknownList
      loadConfigfromXML(const boost::property_tree::ptree pt);
  ~unknownList();
};

class settings
{       
public:
  double ftol;
  double xtol;
  double gtol;
  size_t maxfev;
  double epsfcn;
  double factor;
  size_t mode;
  size_t nprint;

  static struct settings loadConfigfromXML(const boost::property_tree::ptree pt);
  ~settings(void);
  explicit settings( const double ftol_, const double xtol_, const double gtol_,
                     const size_t maxfev_, const double epsfcn_,
                     const double factor_, const size_t mode_,
                     const size_t nprint_ );
};

class LMA_workingArrays
{
public:
  std::vector<double> fjac;
  std::vector<double> predicted;
  std::vector<double> fvec;
  std::vector<double> emissionExperimental;
  std::vector<double> emissionNominal;
  std::vector<double> emissionCurrent;

  double MSE, MSEinitial, MSETol, fvecTotal;

  ~LMA_workingArrays(void);
  void updateArraySize(const size_t Lend_, const size_t N);
  void deleteArray(void);
};


class LMA
{
public:
  class LMA_workingArrays LMA_workspace;
  struct settings Settings;
  class unknownList unknownParameters;

  explicit LMA(const struct settings Settings_,
      const class unknownList unknownParameters);
  ~LMA(void);
};

class settings loadConfig(const std::string &filename);


}

struct parameter_constraints
{
  double R0_min;
  double R0_max;

  double R1_min ;
  double R1_max ;

  double E_sigma_min ;
  double E_sigma_max ;

  double lambda_min ;
  double lambda_max ;

  double gamma_min ;
  double gamma_max ;

  double a_sub_min ;
  double a_sub_max ;

  double Lcoat_min ;
  double Lcoat_max ;
};



#endif // PARAMETERESTIMATION_HPP
