#include "file.h"

#include <filesystem>
#include <fstream>

using std::filesystem::exists;

File::File(const char* path) : file_(path), file_name_(path) {}

bool File::isOpen() { return file_.is_open(); }

bool File::getLine(std::string& line) { return getline(file_, line).operator bool(); }

void File::close() { file_.close(); }

bool File::isExists() { return exists(file_name_); }

std::string File::getContent() {
  std::string content((std::istreambuf_iterator<char>(file_)), std::istreambuf_iterator<char>());
  return content;
}
