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

#ifndef __tat__random__
#define __tat__random__


namespace math{

double genWseed( const double x_min, const double x_max, const unsigned seed ) noexcept;

double x_ini( const double x_min, const double x_max ) noexcept;

int xINTrandom( const int xmin, const int xmax ) noexcept;

double x_normal( const double Xmean, const double Xstddev,
                 const unsigned seed1 ) noexcept;

double x_normal( const double Xmean, const double Xstddev ) noexcept;

double x_bias( const double Xmean, const double Xstddev ) noexcept;

double random_in_logspace( const double start, const double end ) noexcept;

double random_0_to_1() noexcept;

}

#endif /* defined(__tat__random__) */
