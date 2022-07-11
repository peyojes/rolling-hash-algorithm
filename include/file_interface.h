#ifndef FILE_INTERFACE_H
#define FILE_INTERFACE_H
#include <string>

struct FileInterface
{
    virtual bool isOpen() = 0;
    virtual bool getLine(std::string& line) = 0;
    virtual void close() = 0;
    virtual void startsFromBegin() = 0;
};

#endif // FILE_INTERFACE_H
