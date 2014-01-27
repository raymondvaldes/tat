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
#ifndef estimation_HPP
#define estimation_HPP

#include <vector>
#include "models/physicalmodel.hpp"

namespace math{
  namespace estimation{

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
  unknown(enum physicalModel::labels::Name name_,
          const double lower_,
          const double upper_,
          const double initialGuess_);

  void bestfitset(const double input);

  double bestfit(void) const;
  double upperBound(void) const;
  double lowerBound(void) const;
  double initialVal(void) const;

  void Initialauto(void);
  void Initialset(const double input);

  enum physicalModel::labels::Name label(void) const;

};

class unknownList
{
private:
//  size_t N;

public:
  std::vector<class estimation::unknown> vectorUnknowns;

  void addUnknown( physicalModel::labels::Name name,
                   const double lower, const double upper,
                   const double initialGuess);
  size_t Nsize(void) const;

  static class unknownList
      loadConfigfromXML( const boost::property_tree::ptree pt ) ;
  class unknown getParameter( physicalModel::labels::Name label );



  ~unknownList() ;
};






//class settings loadConfig(const std::string &filename);

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
  const size_t factorMax = 10;
  const size_t factorScale = 5;

  static struct settings loadConfigfromXML( const boost::property_tree::ptree pt );
  ~settings(void);
  explicit settings( const double ftol_, const double xtol_, const double gtol_,
                     const size_t maxfev_, const double epsfcn_,
                     const double factor_, const size_t mode_,
                     const size_t nprint_ );
};






  }
}


#endif // estimation_HPP
