#ifndef HASH_COMPARATOR_H
#define HASH_COMPARATOR_H

#include <vector>

#include "hash_creator.h"

enum OperationType {
    none,
    add,
    rm,
    chng
};

struct Operation {
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

    void chechIfIsEqual(HashCreator &base, HashCreator &new_file);

    bool is_equal_;
    std::vector<Operation> diffrences_;
};

#endif // HASH_COMPARATOR_H
