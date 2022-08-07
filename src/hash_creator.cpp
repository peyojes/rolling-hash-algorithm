#include "hash_creator.h"

#include <math.h>

namespace {
constexpr unsigned int BASE = 11;
}  // namespace

using std::pow;

HashCreator::HashCreator(const std::string &content, const size_t window_size)
    : content_(content), window_size_(window_size) {}

bool HashCreator::isNextHash() { return isNextHash(act_begin_); }

size_t HashCreator::calculateNextHash(size_t act_begin, size_t act_hash) {
  size_t hash = (act_hash - content_.at(act_begin - 1)) / BASE;
  hash += content_.at(act_begin + window_size_ - 1) * pow(BASE, window_size_ - 1);

  return hash;
}

bool HashCreator::isNextHash(size_t act_begin) {
  return !content_.empty() && content_.size() > act_begin + window_size_;
}

std::size_t HashCreator::getNextHash() {
  act_begin_++;
  act_hash_ = calculateNextHash(act_begin_, act_hash_);

  return act_hash_;
}

std::size_t HashCreator::getHash() {
  calculateHashIfItIsBeginng();
  return act_hash_;
}

const size_t HashCreator::getWindowSize() const { return window_size_; }

const bool HashCreator::getFirstPosition(const size_t searching_hash, size_t *position) {
  size_t hash = act_hash_;
  size_t index = act_begin_;
  *position = -1;

  if (hash == 0) {
    hash = getHash();
  }
  while (isNextHash(index)) {
    if (hash == searching_hash) {
      *position = index;
      return true;
    }
    index++;
    hash = calculateNextHash(index, hash);
  }

  if (hash == searching_hash) {
    *position = index;
    return true;
  }
  return false;
}

const size_t HashCreator::getSizeContent() const { return content_.size(); }

void HashCreator::calculateHashIfItIsBeginng() {
  if (0 == act_begin_) {
    size_t hash = 0;
    for (int i = 0; i < act_begin_ + window_size_ && i < content_.size(); i++) {
      hash += content_.at(i) * pow(BASE, i);
    }
    act_hash_ = hash;
  }
}
