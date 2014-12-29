/*----------------------------------------------------------------------------*\
  ========                |
     || 	 T Thermal      | TAT: Thermal Analysis Toolbox
     ||  	 A Analysis     |
     || 	 T Toolbox    	| Copyright (C) 2013 Raymond Valdes
     ||                   |
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
#ifndef FILESYSTEM_HPP_INCLUDED
#define FILESYSTEM_HPP_INCLUDED

#include <vector>
#include <string>
#include "boost/filesystem/path.hpp"
#include "tools/interface/filesystem.hpp"

namespace filesystem
{

void makeDir(const std::string &rootPath, const std::string &newDirectory) noexcept;



class directory {
private:
  const std::string workingDirectory;
  const boost::filesystem::path myDirectory;
  
public:
  explicit directory(const std::string &workingDirectory_) noexcept;
  ~directory(void) noexcept;

  std::string abs(const std::string &relativePath) const noexcept;
  void mkdir(const std::string &newDirectory) const;
  std::string pwd(void) const noexcept;
  std::vector<directory> ls() const noexcept;
  
  directory parent_path() const noexcept;
  std::string working_directory() const noexcept;
  std::string working_directory_string() const noexcept;

  
  bool working_directory_starts_with( const std::string& starts) const noexcept;
} ;

std::vector< directory > ls( const std::string &path_in ) noexcept;



}

#endif // FILESYSTEM_HPP_INCLUDED
