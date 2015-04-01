/*----------------------------------------------------------------------------*\
 ========                 |
    || 	   T Thermal      | TAT: Thermal Analysis Toolbox
    ||  	 A Analysis     |
    || 	   T Toolbox    	| Copyright (C) 2013 Raymond Valdes
    ||   	  	          	|
\*----------------------------------------------------------------------------*/
#ifndef FILESYSTEM_HPP_INCLUDED
#define FILESYSTEM_HPP_INCLUDED

#include <vector>
#include <string>
#include <boost/filesystem/path.hpp>

namespace filesystem {

using boost::filesystem::path;


void makeDir
(
  std::string const & rootPath,
  std::string const & newDirectory
) noexcept;

class directory {

private:
  const std::string workingDirectory;
  
  const boost::filesystem::path myDirectory;
  
public:
  explicit directory( std::string const & workingDirectory_ ) noexcept;

  auto abs( std::string const & relativePath) const noexcept
  -> std::string;
  
  auto mkdir( std::string const & newDirectory) const
  -> void;
  
  auto pwd( void ) const noexcept
  -> std::string;
  
  auto ls( void ) const noexcept
  -> std::vector<directory>;
  
  auto ls_files( std::string const & extension  ) const noexcept
  -> std::vector< filesystem::path >;
  
  auto parent_path( void ) const noexcept
  -> directory;

  auto path( void) const noexcept -> filesystem::path ;
  
  auto filePath( std::string const &  filename ) const noexcept -> filesystem::path ;
  
  
  auto working_directory_string( void ) const noexcept
  -> std::string;

  auto working_directory_starts_with( std::string const & starts) const noexcept
  -> bool;
} ;

} // namespace filesystem

#endif // FILESYSTEM_HPP_INCLUDED
