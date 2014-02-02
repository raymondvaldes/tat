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
#include <boost/foreach.hpp>
#include "math/sensitivityAnalysis/estimationInterval.hpp"
#include "thermal/simulations/Numerical_Setup.h"
#include "math/utility.hpp"

namespace math{
  namespace estimation{

unknown::unknown(enum physicalModel::labels::Name name_,
                 const double lower_,
                 const double upper_,
                 const double initialGuess_)
    :name(name_), constraint(lower_, upper_), initialGuess(initialGuess_)
{}

unknown::~unknown(){}

bool unknown::compareName( const unknown& input ) const
{
  return input.label() == label();
}

bool unknown::operator == ( const unknown& input ) const
{
  return compareName(input);
}

bool unknown::operator != ( const unknown& input ) const
{
  return !compareName(input);
}


void unknown::Initialauto(void)
{
  initialGuess = math::average(constraint.lower, constraint.upper);
}

void unknown::Initialset(const double initial)
{
  initialGuess = initial;
}

double unknown::initialVal(void) const
{
  return initialGuess;
}

double unknown::bestfit(void) const
{
  return bestfitval;
}

double unknown::upperBound(void) const
{
  return constraint.upper;
}
double unknown::lowerBound(void) const
{
  return constraint.lower;
}

void unknown::bestfitset(const double input)
{
  bestfitval = input;
}

enum physicalModel::labels::Name unknown::label(void) const
{
  return name.getName();
}

unknown::bounds::bounds( void ){}

unknown::bounds::bounds(const double lower_, const double upper_)
:lower(lower_), upper(upper_){}

void unknown::bestfitIntervalset ( const double min, const double max)
{
  bestfitInterval.lower = min;
  bestfitInterval.upper = max;
}



void unknownList::addUnknown( class estimation::unknown input )
{
  vectorUnknowns.push_back(input);
}


void unknownList::addUnknown(enum physicalModel::labels::Name name,
                             const double lower,
                             const double upper, const double initialGuess)
{
  assert( initialGuess > lower && initialGuess  < upper);

  vectorUnknowns.push_back ( unknown( name, lower, upper, initialGuess ) );
  return;
}

size_t unknownList::size(void) const
{
  return vectorUnknowns.size();
}


std::vector<class unknown> unknownList::operator() (void) const
{
  return vectorUnknowns;
}

void unknownList::operator() (std::vector<class unknown> input)
{
  vectorUnknowns.clear();

  for( auto& val : input )
  {
    vectorUnknowns.push_back(val);
  }

}



class unknown
    unknownList::getParameter( physicalModel::labels::Name label )
{
  class unknown *myReturnPtr = nullptr;

  for( auto& myunKnown : vectorUnknowns)
  {
    if ( myunKnown.label() == label )
    {
        myReturnPtr = &myunKnown;
    }
  }

  class unknown myReturn(*myReturnPtr);
  delete myReturnPtr;


  return myReturn;
}

unknownList::unknownList(){}
unknownList::unknownList( std::vector<class estimation::unknown> input )
  :vectorUnknowns(input)
{}

class unknownList unknownList::
        loadConfigfromXML(const boost::property_tree::ptree pt)
{
  using boost::property_tree::ptree;
  class unknownList unknownListObj;

  // Iterate over 'unknown' branches
  class physicalModel::labels labels;
  BOOST_FOREACH( const ptree::value_type &v,
                 pt.get_child( "unknownParameters" ) )
  {
    //retrieve subtree
    const ptree& child = v.second;

    //access members of subtree
    const std::string nameLabel = child.get< std::string >( "label" );
    const enum physicalModel::labels::Name
        mylabel = labels.nameMap.right.at(nameLabel);

    const double myMin = child.get<double>( "min" );
    const double myMax = child.get<double>( "max" );
    const double initialGuess = child.get<double> ("initialGuess");
    unknownListObj.addUnknown(mylabel, myMin, myMax, initialGuess);
  }
  return unknownListObj;
}




unknownList::~unknownList(){}



settings::~settings(void){}

struct settings settings::
    loadConfigfromXML(const boost::property_tree::ptree pt)
{
    //initialize parameter estimation settings
    const double ftol     = pt.get<double>( "ftol" );
    const double xtol     = pt.get<double>( "xtol" );
    const double gtol     = pt.get<double>( "gtol" );
    const size_t maxfev   = pt.get<size_t>( "maxfev" );
    const double epsfcn   = pt.get<double>( "epsfcn" );
    const double factor   = pt.get<double>( "factor" );
    const int mode        = pt.get<int>( "mode" );
    const int nprint      = pt.get<int>( "nprint" );

    class estimation::settings
    ParaEstSetting(ftol, xtol, gtol, maxfev, epsfcn, factor, mode, nprint);

    return ParaEstSetting;
}

settings::settings( const double ftol_, const double xtol_, const double gtol_,
                     const size_t maxfev_, const double epsfcn_,
                     const double factor_, const size_t mode_,
                     const size_t nprint_ )
  :ftol(ftol_), xtol(xtol_), gtol(gtol_), maxfev(maxfev_), epsfcn(epsfcn_),
    factor(factor_), mode(mode_), nprint(nprint_){}




  }
}
