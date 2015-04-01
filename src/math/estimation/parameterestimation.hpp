/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
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
  labels name;
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
