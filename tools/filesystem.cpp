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
    const boost::filesystem::path pProgram( boost::filesystem::current_path() );
    std::string workingDirectory = pProgram.parent_path().string();
    workingDirectory= workingDirectory + "/";
    std::cout << "working directory: " <<  workingDirectory << "\n\n";

    return workingDirectory;
}

}
