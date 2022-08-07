#ifndef FILE_H
#define FILE_H

#include <fstream>

#include "file_interface.h"

class File : public FileInterface {
 public:
  File(const char* path);
  ~File() {}
  virtual bool isOpen() override;
  virtual bool getLine(std::string& line) override;
  virtual void close() override;
  virtual bool isExists() override;
  virtual std::string getContent() override;

 private:
  std::ifstream file_;
  const char* file_name_;
};

#endif  // FILE_H
