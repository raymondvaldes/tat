#ifndef FILESYSTEM_HPP_INCLUDED
#define FILESYSTEM_HPP_INCLUDED

namespace filesystem
{

void makeDir(const std::string rootPath, const std::string newDirectory);

class directory
{
private:
  const std::string workingDirectory;

public:
  explicit directory(const std::string workingDirectory_);
  ~directory(void);

  std::string abs(const std::string relativePath) const;
  void mkdir(const std::string newDirectory) const;
  std::string pwd(void) const;
};

}

#endif // FILESYSTEM_HPP_INCLUDED
