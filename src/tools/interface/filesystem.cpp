/*----------------------------------------------------------------------------*\
  ========                |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||   	  		        |
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
#include <boost/filesystem.hpp>

#include "tools/interface/filesystem.hpp"

namespace filesystem
{

void makeDir(const std::string rootPath, const std::string newDirectory)
{
  
  const std::string fullpath = rootPath + "/" + newDirectory ;
  const boost::filesystem::path directory( fullpath ) ;
  
  try {
    boost::filesystem::create_directory( directory ) ;
  } catch (std::exception const& ex) {
    std::cerr << ex.what() << "\n";
    std::cerr << fullpath;
  }
  
  return;
}


directory::directory(const std::string workingDirectory_):
  workingDirectory( workingDirectory_ )
{}

directory::~directory(void){}
void directory::mkdir(const std::string newDirectory) const
{
  if ( ! boost::filesystem::is_directory( abs( newDirectory ) ) )
  {

    makeDir( workingDirectory , newDirectory ) ;
  }


}

std::string directory::pwd(void) const
{
  return workingDirectory;
}

std::string directory::abs(const std::string relativePath) const
{
  return workingDirectory + "/" + relativePath;
}


}
