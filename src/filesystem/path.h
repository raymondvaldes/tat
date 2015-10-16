//
//  path.h
//  tat
//
//  Created by Raymond Valdes on 1/14/15.
//  Copyright (c) 2015 Raymond Valdes. All rights reserved.
//

#ifndef __tat__path_011415_
#define __tat__path_011415_

#include <boost/filesystem.hpp>

namespace filesystem {
 
    typedef boost::filesystem::path path;
  
  
  using boost::filesystem::create_directory;
  using boost::filesystem::is_directory;
  using boost::filesystem::is_regular_file;


}
#endif /* defined(__tat__path__) */
