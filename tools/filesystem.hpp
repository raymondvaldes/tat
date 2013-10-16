#ifndef FILESYSTEM_HPP_INCLUDED
#define FILESYSTEM_HPP_INCLUDED

namespace filesystem
{

void makeDir(const std::string rootPath, const std::string newDirectory);
std::string workingDir(void);

}

#endif // FILESYSTEM_HPP_INCLUDED
