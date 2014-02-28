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
    double lower;
    double upper;
    bounds( void ) ;
    bounds( const double lower_, const double  upper_ ) ;
  };
  struct physicalModel::labels name;
  const struct bounds constraint;
  double initialGuess;
  double bestfitval;

  void Initialauto( void ) ;

public:
  unknown( enum physicalModel::labels::Name name_,
           const double lower_,
           const double upper_,
           const double initialGuess_) ;
  ~unknown();

  struct bounds bestfitInterval;
  double bestfit( void ) const ;
  double upperBound( void ) const ;
  double lowerBound( void ) const ;
  double initialVal( void ) const ;

  void bestfitset( const double input ) ;
  void Initialset( const double input ) ;
  void bestfitIntervalset ( const double min, const double max);
  double bestfitIntervalSpread( void ) const;

  enum physicalModel::labels::Name label( void ) const ;
  physicalModel::labels getLabel ( void ) const;

  bool compareName( const unknown& input ) const ;
  bool operator == ( const unknown& input ) const ;
  bool operator != ( const unknown& input ) const ;
};

class unknownList
{
public:
  std::vector< estimation::unknown> vectorUnknowns;

  std::vector< estimation::unknown> operator() (void) const;
  void operator() ( const std::vector<class unknown> &input );

  void addUnknown( physicalModel::labels::Name name,
                   const double lower, const double upper,
                   const double initialGuess);
  void addUnknown(const unknown &input );

  size_t size(void) const;

  unknownList();
  unknownList( std::vector<class estimation::unknown> input )  ;

  static unknownList
      loadConfigfromXML( const boost::property_tree::ptree pt ) ;
  ~unknownList() ;

  std::string prettyPrint(void) ;
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
