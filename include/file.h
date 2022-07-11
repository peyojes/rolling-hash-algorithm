#ifndef FILE_H
#define FILE_H

#include "file_interface.h"

#include <fstream>

class File: public FileInterface {
 public:
    File(const char* path);
    virtual bool isOpen() override;
    virtual bool getLine(std::string& line) override;
    virtual void close() override;
    virtual void startsFromBegin() override;
 private:
    std::ifstream file;
};

#endif // FILE_H
