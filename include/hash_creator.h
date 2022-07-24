#ifndef HASH_CREATOR_H
#define HASH_CREATOR_H

#include <string>

class HashCreator {
 public:
   HashCreator(const std::string& content, const size_t window_size);
   bool isNextHash();
   std::size_t getNextHash();
   std::size_t getHash();
   void backToBeginng();
   const size_t getWindowSize() const;
   const bool getFirstPosition(const size_t searching_hash, size_t *position);
   const size_t getSizeContent() const;

 private:
   void calculateHashIfItIsBeginng();
   size_t calculateNextHash(size_t act_begin, size_t act_hash);
   bool isNextHash(size_t act_begin);

    const size_t window_size_;
    const std::string content_;
    size_t act_begin_ = 0;
    size_t act_hash_ = 0;
};

#endif // HASH_CREATOR_H
