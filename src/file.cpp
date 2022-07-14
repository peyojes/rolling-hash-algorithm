#include "file.h"

#include <filesystem>
#include <fstream>

using std::filesystem::exists;

File::File(const char *path): file_(path), file_name_(path)
{
}

bool File::isOpen()
{
    return file_.is_open();
}

bool File::getLine(std::string& line)
{
    return getline(file_, line).operator bool();
}

void File::close()
{
    file_.close();
}

void File::startsFromBegin()
{
    file_.clear();
    file_.seekg(0, std::ios::beg);
}

bool File::isExists()
{
    return exists(file_name_);
}
