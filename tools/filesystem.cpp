#include "../Header.h"

namespace filesystem
{


void makeDir(const std::string rootPath, const std::string newDirectory)
{
    boost::filesystem::path directory(rootPath + newDirectory);
    boost::filesystem::create_directory(directory);
    return;
}

directory::directory(void){}
directory::~directory(void){}
void directory::mkdir(const std::string newDirectory) const
{
  makeDir(workingDirectory,newDirectory);
}

std::string directory::pwd(void) const
{
  return workingDirectory;
}

std::string directory::workingDir(void) const
{
    //Report back the working library in as a std::string

    const boost::filesystem::path pProgram( boost::filesystem::current_path() );
    std::string workingDirectory = pProgram.parent_path().string();

    workingDirectory= workingDirectory + "/";
    std::cout << "working directory: " <<  workingDirectory << "\n\n";

    return workingDirectory;
}

}
