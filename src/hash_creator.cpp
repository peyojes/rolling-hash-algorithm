#include "hash_creator.h"

#include <math.h>
#include <iostream>

namespace {
constexpr unsigned int BASE = 11;
} // namespace

using std::pow;

HashCreator::HashCreator(const std::string &content, const size_t window_size)
    : content_(content), window_size_(window_size)
{
}

bool HashCreator::isNextHash()
{
    return !content_.empty() && content_.size() > act_begin_ + window_size_;
}

std::size_t HashCreator::getNextHash()
{

    calculateHashIfItIsBeginng();

    if (act_begin_ > 0) {
        size_t hash = (act_hash_ - content_.at(act_begin_ - 1)) / BASE;
        hash += content_.at(act_begin_ + window_size_ - 1) * pow(BASE, window_size_ - 1);
        act_hash_ = hash;
    }
    act_begin_++;

    return act_hash_;
}

std::size_t HashCreator::getHash()
{
    calculateHashIfItIsBeginng();
    return act_hash_;
}

void HashCreator::calculateHashIfItIsBeginng()
{
    if (0 == act_begin_) {
        size_t hash = 0;
        for (int i = 0; i < act_begin_ + window_size_ && i < content_.size(); i++) {
            hash += content_.at(i) * pow(BASE, i);
        }
        act_hash_ = hash;
    }
}

