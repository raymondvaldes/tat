//
//  main.cpp
//  tat-tdd
//
//  Created by Raymond Valdes on 12/22/14.
//  Copyright (c) 2014 Raymond Valdes. All rights reserved.
//

#include <iostream>
#include <string>

int main(int argc, const char * argv[]) noexcept
{
  using std::string;

  {
    auto tatTest = string("/tmp/tat-test.dst/usr/local/bin/tat-test");
    tatTest += " --log_level=warning";
    tatTest += " --show_progress=yes";
    tatTest += " --build_info";
    system( tatTest.data() );
  }
  
  {
    using std::cout;
    cout << "\n";
    cout << "******************************************************";
    cout << "\n";
  }
  
  {
    auto tatApp = string("/tmp/tat-app.dst/Users/raymondvaldes/usr/bin/tat-app");
    tatApp += " --run /Users/raymondvaldes/Dropbox/investigations/develop";
    tatApp += " --sample APS";
    tatApp += " --investigation twoColorPyrometery";
    system( tatApp.data() ) ;
  }
  
  return 0;
}
