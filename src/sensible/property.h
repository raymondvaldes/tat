/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef __tat__property__sensible
#define __tat__property__sensible

#include <iostream>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include "thermal/define/temperature.h"

namespace sensible{
  
  using std::vector;
  using boost::property_tree::ptree;
  using thermal::define::Temperature;
  
class property
{
private:
  static constexpr bool tempDependent = false;
  double Current( const double temperature) const noexcept;
  
  double Projected( const double temperature1, const double temperature2) const noexcept;
  
public:
  double offset;
  double slope;
  
  explicit property(const double offset_,const double slope_) noexcept;
  explicit property(void) noexcept;
  
  double Current(const vector<vector<double>>& T, const size_t n,
                 const size_t j) const noexcept;
  
  double Current(const vector<vector<double>>& T, const size_t n,
                 const size_t j1, const size_t j2) const noexcept;
  
  
  double Current(const Temperature Tprofile, const size_t n,
                 const size_t j) const noexcept;
  
  double Current(const Temperature Tprofile, const size_t n,
                 const size_t j1, const size_t j2) const noexcept;
  
  
  double Projected(const vector< vector<double>>& T,
                   const size_t n, const size_t j) const noexcept;
  
  double Projected(const vector< vector<double>>& T, const size_t n,
                   const size_t j1, const size_t j2) const noexcept;
  
  double Projectedt( const vector< vector<double>>& T,
                     const size_t n, const size_t, const size_t j) const noexcept;
  
  double Projected( const Temperature Tprofile,
                    const size_t n, const size_t j) const noexcept;
  
  double Projected(const Temperature Tprofile, const size_t n,
                   const size_t j1, const size_t j2) const noexcept;
  
  double Projectedt(const Temperature Tprofile,
                    const size_t n, const size_t, const size_t j) const noexcept;
  static property loadConfigfromXMLTree(const ptree pt) noexcept;
};

  
}

#endif /* defined(__tat__property__sensible) */
