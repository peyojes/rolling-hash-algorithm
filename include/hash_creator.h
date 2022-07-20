#ifndef HASH_CREATOR_H
#define HASH_CREATOR_H

#include <string>

class HashCreator {
 public:
   HashCreator(const std::string& content, const size_t window_size);
   bool isNextHash();
   std::size_t getNextHash();
   std::size_t getHash();

 private:
   void calculateHashIfItIsBeginng();

    const size_t window_size_;
    const std::string content_;
    size_t act_begin_ = 0;
    size_t act_hash_ = 0;
};

#endif // HASH_CREATOR_H
