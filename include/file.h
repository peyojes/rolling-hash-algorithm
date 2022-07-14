#ifndef FILE_H
#define FILE_H

#include "file_interface.h"

#include <fstream>

class File: public FileInterface {
 public:
    File(const char* path);
    ~File() {}
    virtual bool isOpen() override;
    virtual bool getLine(std::string& line) override;
    virtual void close() override;
    virtual void startsFromBegin() override;
    virtual bool isExists() override;
 private:
    std::ifstream file_;
    const char* file_name_;
};

#endif // FILE_H
