/*----------------------------------------------------------------------------*\
  ========                      |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||                         |
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
#include "thermal/emission/noise.hpp"
#include "math/utility.hpp"

namespace thermal{
  namespace emission{


ExpNoiseSetting::ExpNoiseSetting( const double a1_, const double b1_,
                                  const bool d1_, const bool d2_,
                                  const int s1_, const double noiseRandom_):
    a(a1_), b(b1_), noiseRandom(noiseRandom_), d1(d1_), d2(d2_), s1(s1_)
{}

std::vector<double>
addNoise( const std::vector<double> &emissionNominal_,
          const std::vector<double> &lthermal,
          const thermal::emission::ExpNoiseSetting &para )

{
  const double lmin = lthermal.front();
  const double lmax = lthermal.back();
  const double a = para.a;
  const double b = para.b;
  const bool d1 = para.d1;
  const bool d2 = para.d2;
  const int s1 = para.s1;
  const double noiseRandom = para.noiseRandom;

  if( (a < 0) || (b < 1) || (b > M_PI) )
  {
     std::cerr << "parameters (a,b) out of range"; exit(-99);
  }

  std::vector<double> output(emissionNominal_);
  for( size_t i=0 ; i < lthermal.size() ; ++i )
  {
    constexpr double c = 0.5;
    const double
        lthermalPercentile = math::percentilelog10( lmin, lmax, lthermal[i] );

    ///Determine biased noise
    const double cotbc = tan( M_PI_2 - ( b * c ) );
    double noiseBias = -a * cotbc * tan( b * ( c - lthermalPercentile ) );

  if(!d2) { noiseBias = std::fabs(noiseBias); }
    if(!d1) { noiseBias *= -1; }

    switch(s1)
    {
      case -1:
          if( lthermalPercentile > 0.5 ) { noiseBias = 0; }
          break;
      case 0:
          break;
      case 1:
          if( lthermalPercentile < 0.5 ) { noiseBias = 0; }
          break;
      default:
          std::cout << "\n\nerror in symmetry options\n\n"; exit(-1);
    }

    ///Determine random noise
    const double noiseRandomGen = math::x_normal(0, noiseRandom);

    output[i] += M_PI_2 * noiseBias;
    output[i] += M_PI_2 * noiseRandomGen;
  }
  return output;
}



ExpNoiseSetting
ExpNoiseSetting::initializeObj( const boost::property_tree::ptree pt )
{
  //initialize parameter estimation settings
  const double a1_     = pt.get<double>( "bias-noise" );
  const double b1_     = pt.get<double>( "stretching-parameter" );
  const bool d1_     = pt.get<int>( "positive" );
  const bool d2_   = pt.get<int>( "monotonic" );
  const int s1_   = pt.get<int>( "bias-side" );
  const double noiseRandom_   = pt.get<double>( "random-noise" );

  const ExpNoiseSetting output( a1_, b1_, d1_, d2_, s1_, noiseRandom_ ) ;

  return output;
}


ExpNoiseSetting
ExpNoiseSetting::loadExpNoiseFile( const class filesystem::directory dir )
{
  const std::string filename = "EmissionNoise.xml";
  const std::string absPath = dir.abs( filename );
  boost::property_tree::ptree pt;
  try
  {
    boost::property_tree::read_xml( absPath , pt);
  }
  catch (std::exception& e)
  {
    std::cout << "file " << absPath << " not found! See --help\n";
    exit(-2);
  }

  //pass child to settings object
  using boost::property_tree::ptree;
  const std::string conjunto = "simulated-emission." ;
  const ptree ptchild1 = pt.get_child( conjunto + "settings");


  return initializeObj( ptchild1 ) ;
}









}}
