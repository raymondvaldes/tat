#ifndef FILESYSTEM_HPP_INCLUDED
#define FILESYSTEM_HPP_INCLUDED

namespace filesystem
{

void makeDir(const std::string rootPath, const std::string newDirectory);
std::string workingDir(void);


class directory
{
private:
  const std::string workingDirectory = workingDir();

public:
  directory(void);
  ~directory(void);

  void mkdir(const std::string newDirectory) const;
  std::string pwd(void) const;
  std::string workingDir(void) const;
};

}

#endif // FILESYSTEM_HPP_INCLUDED
