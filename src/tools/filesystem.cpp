#include "../Header.h"

namespace filesystem
{

void makeDir(const std::string rootPath, const std::string newDirectory)
{
    boost::filesystem::path directory(rootPath + "/" +newDirectory);
    boost::filesystem::create_directory(directory);
    return;
}

directory::directory(const std::string workingDirectory_):
  workingDirectory(workingDirectory_){}

directory::~directory(void){}
void directory::mkdir(const std::string newDirectory) const
{
  makeDir(workingDirectory,newDirectory);
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
