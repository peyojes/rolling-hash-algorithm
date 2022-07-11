#include "file.h"

#include <fstream>

File::File(const char *path): file(path)
{
}

bool File::isOpen()
{
    return file.is_open();
}

bool File::getLine(std::string& line)
{
    return getline(file, line).operator bool();
}

void File::close()
{
    file.close();
}

void File::startsFromBegin()
{
    file.clear();
    file.seekg(0, std::ios::beg);
}
