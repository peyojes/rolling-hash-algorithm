#ifndef HASH_COMPARATOR_H
#define HASH_COMPARATOR_H

#include <vector>

#include "hash_creator.h"

struct Operation {
  enum OperationType { none, add, rm, chng };

  OperationType type;
  size_t base_begin;
  size_t base_end;
  size_t new_file_begin;
  size_t new_file_end;
};

class HashComparator {
 public:
  HashComparator(HashCreator &base, HashCreator &new_file);

  bool isEqual() const;
  std::vector<Operation> getDifferences() const;

 private:
  void addOperation(const Operation &operation);

  std::vector<Operation> diffrences_;
};

#endif  // HASH_COMPARATOR_H
