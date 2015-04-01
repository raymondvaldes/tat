/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#include <exception>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <ios>

#include "math/estimation/parameterestimation.hpp"

#include "thermal/model/one_dim/numerical_2011/Numerical_Setup.h"
#include "math/utility.hpp"


namespace math{
  namespace estimation{

unknown::unknown(enum thermal::model::labels::Name name_,
                 const double lower_,
                 const double upper_,
                 const double initialGuess_) noexcept
    :name(name_), constraint(lower_, upper_), initialGuess(initialGuess_),
    bestfitval(initialGuess_), bestfitInterval(0,0)
{}

unknown::~unknown() noexcept {}

bool unknown::compareName( const unknown& input ) const noexcept
{
  return input.label() == label();
}

bool unknown::operator == ( const unknown& input ) const noexcept
{
  return compareName(input);
}

bool unknown::operator != ( const unknown& input ) const noexcept
{
  return !compareName(input);
}


double unknown::bestfitIntervalSpread( void ) const noexcept
{
  return  (bestfitInterval.upper - bestfitInterval.lower) / bestfitval;
}


void unknown::Initialset(const double initial) noexcept
{
  initialGuess = initial;
}

double unknown::initialVal(void) const noexcept
{
  return initialGuess;
}

double unknown::bestfit(void) const noexcept
{
  return bestfitval;
}

double unknown::upperBound(void) const noexcept
{
  return constraint.upper;
}
double unknown::lowerBound(void) const noexcept
{
  return constraint.lower;
}

void unknown::bestfitset(const double input) noexcept
{
  bestfitval = input;
}

enum thermal::model::labels::Name unknown::label(void) const noexcept
{
  return name.getName();
}

thermal::model::labels unknown::getLabel ( void ) const noexcept
{
  return name;
}



unknown::bounds::bounds( void ) noexcept{}

unknown::bounds::bounds(const double lower_, const double upper_) noexcept
:lower(lower_), upper(upper_){}

void unknown::bestfitIntervalset ( const double min, const double max) noexcept
{
  bestfitInterval.lower = min;
  bestfitInterval.upper = max;
}



void unknownList::addUnknown( const class estimation::unknown &input ) noexcept
{
  vectorUnknowns.push_back(input);
}


void unknownList::addUnknown(enum thermal::model::labels::Name name,
                             const double lower,
                             const double upper, const double initialGuess) noexcept
{
  using std::abs;
  const double tol = 1e-12;
  double myInitialGuess = initialGuess;
  if ( abs( initialGuess - upper) < tol )
    {myInitialGuess = upper - tol;}

  if ( abs( initialGuess - lower) < tol )
    {myInitialGuess = lower + tol;}

  BOOST_ASSERT( myInitialGuess > lower && myInitialGuess  < upper);

  vectorUnknowns.push_back ( unknown( name, lower, upper, myInitialGuess ) );
  return;
}

size_t unknownList::size(void) const noexcept
{
  return vectorUnknowns.size();
}


std::vector<class unknown> unknownList::operator() (void) const noexcept
{
  return vectorUnknowns;
}

void unknownList::operator() ( const std::vector< class unknown > &input ) noexcept
{
  vectorUnknowns.clear();

  for( auto const& val : input )
  {
    addUnknown( val ) ;
  }
}

std::vector< enum labels::Name > unknownList::get_enum_list( void ) noexcept {

  std::vector<enum labels::Name> output;
  
  for( auto& val : vectorUnknowns )
    output.push_back( val.label() ) ;
  
  return output;
}


unknownList::unknownList() noexcept{}
unknownList::unknownList( std::vector< estimation::unknown> input ) noexcept
  :vectorUnknowns(input)
{}


unknownList unknownList::
        loadConfigfromXML(const boost::property_tree::ptree pt) noexcept
{
  using boost::property_tree::ptree;
  unknownList unknownListObj;

  // Iterate over 'unknown' branches
  thermal::model::labels labels;
  for( const ptree::value_type &v : pt.get_child( "unknownParameters" ) )
  {
    //retrieve subtree
    const ptree& child = v.second;

    //access members of subtree
    const std::string nameLabel = child.get< std::string >( "label" );
    enum thermal::model::labels::Name mylabel;
    try
    {
      mylabel = labels.nameMap.right.at(nameLabel);
    }
    catch( std::exception& e )
    {
      std::cerr << "Error with unknownParameters label in poptea.xml config\n";
      exit(1);
    }

    const double myMin = child.get<double>( "min" );
    const double myMax = child.get<double>( "max" );
    const double initialGuess = child.get<double> ("initialGuess");
    unknownListObj.addUnknown(mylabel, myMin, myMax, initialGuess);
  }
  return unknownListObj;
}

std::string
unknownList::prettyPrint( void ) noexcept
{
  std::ostringstream output ;

  output << "*-----------------------------------------*\n";
  output << "| parameter estimate intervals:           |\n";
  output << "|-----------------------------------------|\n";
  output << "| min       bestfit    max      error(%)  |\n";

  output.setf( std::ios::fixed, std::ios::floatfield ) ;
  output << std::setprecision(3) ;
  for( const math::estimation::unknown & val : vectorUnknowns )
  {
    output << "| "
              << std::setw(10) << std::left << val.bestfitInterval.lower
              << std::setw(10) << std::left << val.bestfit()
              << std::setw(10) << std::left << val.bestfitInterval.upper
              << std::setw(10) << std::left << 100*val.bestfitIntervalSpread()
              << "|\n";
  }
  output << "*-----------------------------------------*\n";

  return output.str() ;
}

unknownList::~unknownList() noexcept{}


  }
}
