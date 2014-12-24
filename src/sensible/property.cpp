/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
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

#include "sensible/property.h"
#include "math/utility.hpp"

namespace sensible{
  
  
double property::Current(const double temperature) const
{
  if(!tempDependent) return offset;
  
  double
  currT = temperature;
  currT *= slope;
  currT += offset;
  
  return currT;
}

double property::Projected(const double temperature1, const double temperature2)
const
{
  if(!tempDependent) return offset;
  
  double
  projT = temperature1;
  projT -= temperature2;
  projT *= slope;
  projT += Current(temperature1) ;
  
  return projT;
}

double property::Current(const std::vector<std::vector<double>>& T, const size_t n,
                         const size_t j) const
{
  if(!tempDependent) return offset;
  
  return offset + slope * T[n][j];
}

double property::Current(const std::vector<std::vector<double>>& T, const size_t n,
                         const size_t j1, const size_t j2) const
{
  if(!tempDependent) return offset;
  
  using math::mean;
  return mean( Current( T[n][j1] ) , Current( T[n][j2] ) );
}


double property::Current(const class Temperature Tprofile, const size_t n,
                         const size_t j) const
{
  if(!tempDependent) return offset;
  
  return offset + slope * Tprofile.eval(n,j);
}

double property::Current(const class Temperature Tprofile, const size_t n,
                         const size_t j1, const size_t j2) const
{
  if(!tempDependent) return offset;
  using math::mean;

  return mean( Current( Tprofile.eval(n, j1 ) ) ,
                    Current( Tprofile.eval(n,j2  ) ) );
}


double property::Projected(const std::vector<std::vector<double>>& T,
                           const size_t n, const size_t j) const
{
  if(!tempDependent) return offset;
  
  if( n == 0 ) return Current( T[n][j] );
  
  
  return Current(T[n][j]) + slope * (T[n][j] - T[n-1][j]);
}

double property::Projected(const std::vector<std::vector<double>>& T, const size_t n,
                           const size_t j1, const size_t j2)
const
{
  if(!tempDependent) return offset;
  using math::mean;

  if( n == 0 )
  {
    return mean( Current(  T[n][j1] ) , Current( T[n][j2] ) );
  }
  
  return mean( Projected(T, n, j1), Projected(T, n, j2) );
}

double property::Projectedt(const std::vector<std::vector<double>>& T,
                            const size_t n,const size_t /*n1*/, const size_t j)
const
{
  if(!tempDependent) return offset;
  using math::mean;

  return mean( Current(T, n, j) ,  Projected(T, n, j));
}

double property::Projected(const class Temperature Tprofile,
                           const size_t n, const size_t j) const
{
  if(!tempDependent) return offset;
  
  if( n == 0 ) return Current( Tprofile.eval(n,j) );
  
  
  return Current(Tprofile.eval(n,j)) + slope * (Tprofile.eval(n,j) -
                                                Tprofile.eval(n-1,j));
}

double property::Projected(const class Temperature Tprofile, const size_t n,
                           const size_t j1, const size_t j2)
const
{
  if(!tempDependent) return offset;
  using math::mean;

  if( n == 0 )
  {
    return mean( Current(  Tprofile.eval(n,j1) ) ,
                      Current( Tprofile.eval(n,j2) ) );
  }
  
  return mean( Projected(Tprofile, n, j1), Projected(Tprofile, n, j2) );
}

double property::Projectedt(const class Temperature Tprofile,
                            const size_t n,const size_t /*n1*/, const size_t j)
const
{
  if(!tempDependent) return offset;
  using math::mean;

  return mean( Current(Tprofile, n, j) ,  Projected(Tprofile, n, j));
}

property::property(const double offset_,const double slope_) noexcept
: offset(offset_), slope(slope_)
{}

property::property(void) noexcept{}

class property
property::loadConfigfromXMLTree(const boost::property_tree::ptree pt) noexcept
{
  const double offset_ = pt.get<double>( "offset" );
  const double slope_ = pt.get<double>( "slope" );
  return property(offset_, slope_);
}


  
  
}