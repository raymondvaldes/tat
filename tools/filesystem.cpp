#include "../Header.h"

namespace filesystem
{


void makeDir(const std::string rootPath, const std::string newDirectory)
{
    boost::filesystem::path directory(rootPath + newDirectory);
    boost::filesystem::create_directory(directory);
    return;
}

std::string workingDir(void)
{
    boost::filesystem::path pProgram( boost::filesystem::current_path() );
    std::string dir = pProgram.parent_path().string();

    const std::string workingDirectory= dir + "/";
    std::cout << "working directory: " <<  workingDirectory << "\n";

    return workingDirectory;
}

}
