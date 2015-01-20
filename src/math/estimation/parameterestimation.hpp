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
#include <boost/property_tree/ptree.hpp>
#include "thermal/model/labels.h"

namespace math{
  namespace estimation{

    using thermal::model::labels;
    
class unknown
{
private:
  struct bounds
  {
    double lower;
    double upper;
    bounds( void ) noexcept;
    bounds( const double lower_, const double  upper_ ) noexcept;
  };
  struct labels name;
  const struct bounds constraint;
  double initialGuess;
  double bestfitval;

public:
  unknown( enum labels::Name name_,
           const double lower_,
           const double upper_,
           const double initialGuess_) noexcept;
  ~unknown() noexcept;

  struct bounds bestfitInterval;

  /// return values
  double bestfit( void ) const noexcept;
  double upperBound( void ) const noexcept;
  double lowerBound( void ) const noexcept;
  double initialVal( void ) const noexcept;

  /// set values with inputs
  void bestfitset( const double input ) noexcept;
  void Initialset( const double input ) noexcept;
  void bestfitIntervalset ( const double min, const double max) noexcept;
  double bestfitIntervalSpread( void ) const noexcept;

  /// labels
  enum labels::Name label( void ) const noexcept;
  labels getLabel ( void ) const noexcept;

  bool compareName( const unknown& input ) const noexcept;
  bool operator == ( const unknown& input ) const noexcept;
  bool operator != ( const unknown& input ) const noexcept;
};

class unknownList
{
public:
  std::vector< estimation::unknown> vectorUnknowns;

  std::vector< estimation::unknown> operator() (void) const noexcept;
  void operator() ( const std::vector<class unknown> &input )noexcept;

  void addUnknown( labels::Name name,
                   const double lower, const double upper,
                   const double initialGuess ) noexcept;
  void addUnknown(const unknown &input ) noexcept;

  size_t size(void) const noexcept;

  unknownList() noexcept;
  unknownList( std::vector< estimation::unknown> input ) noexcept;

  static unknownList
      loadConfigfromXML( const boost::property_tree::ptree pt ) noexcept;
  ~unknownList() noexcept;

  std::string prettyPrint(void) noexcept;
  std::vector< enum labels::Name > get_enum_list( void ) noexcept;
  
};




  }
}


#endif // estimation_HPP
