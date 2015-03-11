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
#include <iostream>
#include <boost/filesystem.hpp>

#include "tools/interface/filesystem.hpp"
#include "algorithm/string/starts_with.h"
#include "algorithm/string/split.h"

namespace filesystem
{

std::vector< directory > ls( const std::string &path_in ) noexcept;


std::vector< directory > ls( const std::string &path_in ) noexcept
{
  using namespace boost::filesystem;
  path p ( path_in );
  std::vector< directory > output;


  if (!exists(p))
  {
    std::cout << "\nNot found: " << path_in << std::endl;
    return output;
  }

  if( is_directory( p ) )
  {
    directory_iterator end_iter;

    for ( directory_iterator dir_itr(p) ;  dir_itr != end_iter; ++dir_itr )
    {
      try
      {
        if( is_directory( dir_itr->status() ) )
        {
          const boost::filesystem::path temp_dir( dir_itr->path() ) ;
          const directory mytemp ( temp_dir.string() ) ;
          output.push_back( mytemp ) ;
        }
      }
      catch (const boost::filesystem::filesystem_error& ex)
      {
        std::cerr << ex.what() << "\n";
      }
    }
  }
  else // must be a file
  {
    std::cout << "\nFound: " << p << "\n";
  }

  return output;
}


void makeDir( const std::string &rootPath, const std::string &newDirectory ) noexcept
{
  assert( !rootPath.empty()  );
  assert( !newDirectory.empty() );
  
  auto const fullpath = rootPath + "/" + newDirectory ;
  const boost::filesystem::path directory( fullpath ) ;
  
  try {
    boost::filesystem::create_directory( directory ) ;
  } catch (std::exception const& ex) {
    std::cerr << ex.what() << "\n";
    std::cerr << fullpath;
  }
  
  return;
}


directory::directory( const std::string &workingDirectory_ ) noexcept:
  workingDirectory( workingDirectory_ ), myDirectory( workingDirectory_ ){}


void directory::mkdir(const std::string &newDirectory) const
{
  if ( ! boost::filesystem::is_directory( abs( newDirectory ) ) )
  {
    makeDir( workingDirectory , newDirectory ) ;
  }
}

std::string directory::working_directory_string() const noexcept {
  using std::string;
  using std::vector;
  
  using algorithm::string::split;
  
  const string& delimiter = "/";
  auto const folders =  split( pwd(), delimiter  ) ;
  
  auto const last = folders.back();
  
  auto const working_folder_only = !last.empty() ? folders.rbegin()[0]
                                                   : folders.rbegin()[1] ;


  return working_folder_only;
}

bool directory::working_directory_starts_with( const std::string& check ) const noexcept {
  
  BOOST_ASSERT( !check.empty() ) ;
  using std::string;
  using std::vector;
  
  using algorithm::string::starts_with;

  auto const wk_folder = working_directory_string() ;
  auto const pass = starts_with( wk_folder, check ) ;
  return pass;
}

std::string directory::pwd(void) const noexcept
{
  return workingDirectory;
}

std::string directory::abs( const std::string &relativePath) const noexcept
{
  BOOST_ASSERT( !relativePath.empty() ) ;

  auto const fullPath = workingDirectory + "/" + relativePath;

  return fullPath;
}

directory directory::parent_path() const noexcept {

  boost::filesystem::path parentPath = myDirectory.parent_path();
 
   return directory( parentPath.string() ) ;
}



std::vector<directory> directory::ls() const noexcept
{
  return filesystem::ls( pwd() ) ;
}


}
