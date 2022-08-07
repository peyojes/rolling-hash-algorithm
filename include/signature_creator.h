#ifndef SIGNATURE_CREATOR_H
#define SIGNATURE_CREATOR_H

#include "file_interface.h"

class SignatureCreator {
 public:
  SignatureCreator(){};
  std::size_t getSignature(FileInterface &file) const;
};

#endif  // SIGNATURE_CREATOR_H
