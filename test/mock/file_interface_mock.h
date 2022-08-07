#ifndef FILE_INTERFACE_MOCK_H
#define FILE_INTERFACE_MOCK_H
#include <gmock/gmock.h>

#include "file_interface.h"

class FileMock : public FileInterface {
 public:
  ~FileMock() {}
  MOCK_METHOD(bool, isOpen, (), (override));
  MOCK_METHOD(bool, getLine, (std::string & line), (override));
  MOCK_METHOD(void, close, (), (override));
  MOCK_METHOD(bool, isExists, (), (override));
  MOCK_METHOD(std::string, getContent, (), (override));
};

#endif  // FILE_INTERFACE_MOCK_H
