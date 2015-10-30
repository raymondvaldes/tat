/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/

#ifndef PROGRAMOPTIONS_HPP
#define PROGRAMOPTIONS_HPP

#include <utility>
#include <string>
#include <sstream>

namespace tools{
namespace programoptions{

class MainArguments{

private:
    const int argc;
    const char **argv;
    mutable bool run = false ;
    mutable std::string path;
    mutable std::string sampleName;
    mutable std::string investigationName;

    bool help( void ) const noexcept;
    bool version( void ) const noexcept;
    bool build( void ) const noexcept;
    void loadOptions( void ) const noexcept;

public:
     MainArguments( const int argc_in, const char **argv_in ) noexcept;

    bool run_analysis( void ) const noexcept;
    std::string run_directory( void ) const noexcept;
    std::string run_samples( void ) const noexcept;
    std::string run_investigationName( void ) const noexcept;
};


}}
#endif // PROGRAMOPTIONS_HPP
