#include <hash_comparator.h>
#include <spdlog/spdlog.h>

constexpr auto add = Operation::OperationType::add;
constexpr auto rm = Operation::OperationType::rm;
constexpr auto chng = Operation::OperationType::chng;

using spdlog::debug;

namespace {

void searchFirstEqualHash(size_t *base_index, size_t *position, HashCreator &new_file, HashCreator &base,
                          size_t *base_shift, size_t *base_hash) {
  while (base.isNextHash() && !new_file.getFirstPosition(*base_hash, position)) {
    (*base_index)++;
    *base_hash = base.getNextHash();
    (*base_shift)++;
  }
}

bool isAddAtTheEnd(HashCreator &hash_creator) { return hash_creator.isNextHash(); }

bool isRemoveLastPart(HashCreator &hash_creator) { return !hash_creator.isNextHash(); }

bool isNotFoundHash(const size_t position) { return position == -1; }

bool isBaseAfterNewFile(const size_t base_index, const int shift, const size_t position) {
  return base_index + shift < position;
}

bool isBaseBeforeNewFile(const size_t base_index, const size_t position) { return base_index > position; }

bool isAddAtBeginning(const size_t position, const size_t base_index) { return position == 0 || base_index == 0; }

bool isChangeInTheMiddle(const size_t base_index, const size_t position, const size_t base_shift,
                         const size_t window_size) {
  return base_index != position && base_shift != window_size - 1;
}

bool isAtBeginnig(const size_t position) { return position == 0; }

void move(HashCreator &new_file, const size_t position, size_t *new_file_index, size_t *new_file_hash, int begin = 0) {
  for (int it = begin; it < position && new_file.isNextHash(); it++) {
    *new_file_hash = new_file.getNextHash();
    (*new_file_index)++;
  }
}

}  // namespace

HashComparator::HashComparator(HashCreator &base, HashCreator &new_file) {
  size_t base_index = 0;
  size_t new_file_index = 0;
  int shift = 0;
  size_t window_size = base.getWindowSize();
  auto base_hash = base.getHash();
  auto new_file_hash = new_file.getHash();
  bool isFirstTime = true;

  while (base.isNextHash()) {
    debug("base index {} new file index {} base hash {} shift {}", base_index, new_file_index, base_hash, shift);
    if (isRemoveLastPart(new_file)) {
      addOperation({rm, base_index + window_size, base.getSizeContent(), 0, 0});
      break;
    }
    if (base_hash != new_file_hash) {
      size_t position = 0;
      size_t base_begin = base_index;
      size_t base_shift = 1;

      searchFirstEqualHash(&base_index, &position, new_file, base, &base_shift, &base_hash);

      if (isNotFoundHash(position)) {
        debug("Hash is not found");
        addOperation({chng, base_begin + window_size - 1, base.getSizeContent() - 1, new_file_index + window_size - 1,
                      new_file.getSizeContent() - 1});
        return;
      }

      if (isBaseAfterNewFile(base_index, shift, position)) {
        debug("base is after new file, position {}", position);
        if (isFirstTime) {
          if (isAddAtBeginning(position, base_index)) {
            addOperation({add, base_index, base_index, base_index, position - 1});
          } else {
            addOperation({chng, 0, base_index - 1, 0, position - 1});
            shift += position - base_index;
          }
          move(new_file, position, &new_file_index, &new_file_hash);

        } else {
          if (isChangeInTheMiddle(base_index, position, base_shift, window_size)) {
            debug("change in the middle");
            addOperation(
                {chng, base_begin + window_size - 1, base_index - 1, new_file_index + window_size - 1, position - 1});
            shift += base_shift - window_size;

          } else {
            addOperation({add, base_index + 1, base_index + 1, base_index + 1, position});
          }
          debug("shift {} position {}", shift, position);
          move(new_file, position, &new_file_index, &new_file_hash, new_file_index);
        }
      }

      if (isBaseBeforeNewFile(base_index, position)) {
        if (isFirstTime) {
          if (isAtBeginnig(position)) {
            addOperation({rm, base_begin, base_index - 1, 0, 0});
          } else {
            addOperation({chng, 0, base_index - 1, 0, position - 1});
            shift += position - base_index;
            move(new_file, position, &new_file_index, &new_file_hash);
          }
        } else {
          debug("Remove from middle");
          addOperation({rm, base_begin + window_size - 1, base_index, 0, 0});
          move(new_file, position, &new_file_index, &new_file_hash, new_file_index);
        }
      }
    }

    isFirstTime = false;
    base_index++;
    new_file_index++;
    base_hash = base.getNextHash();
    new_file_hash = new_file.getNextHash();
  }

  if (isAddAtTheEnd(new_file)) {
    size_t position = base_index + window_size + shift;
    if (shift != 0) {
      position--;
    }
    debug("It is added at the end position {}", position);
    addOperation({add, base.getSizeContent() - 1, base.getSizeContent() - 1, position, new_file.getSizeContent() - 1});
  }
}

bool HashComparator::isEqual() const { return diffrences_.empty(); }

std::vector<Operation> HashComparator::getDifferences() const { return diffrences_; }

void HashComparator::addOperation(const Operation &operation) { diffrences_.push_back(operation); }
