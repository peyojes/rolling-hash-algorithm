#include <hash_comparator.h>

#include <iostream>

HashComparator::HashComparator(HashCreator &base, HashCreator &new_file)
{
    chechIfIsEqual(base, new_file);
    base.backToBeginng();
    new_file.backToBeginng();

    size_t base_index = 0;
    size_t new_file_index = 0;
    int shift = 0;
    size_t base_begin = 0;
    size_t window_size = base.getWindowSize();
    auto base_hash = base.getHash();
    auto new_file_hash = new_file.getHash();
    bool isFirstTime = true;

    while (base.isNextHash()) {
        std::cout << "base index " << base_index << " new file index " << new_file_index << " base hash " << base_hash << " shift "<< shift << std::endl;
        if (!new_file.isNextHash()) { // remove last word
            diffrences_.push_back({OperationType::rm, base_index + window_size, base.getSizeContent(), 0, 0});
            break;
        }
        if (base_hash != new_file_hash) {
            size_t position = 0;
            size_t base_begin = base_index;
            size_t base_shift = 1;
            while (base.isNextHash() && !new_file.getFirstPosition(base_hash, &position)) {
                base_index++;
                std::cout << "base_index in getFirstPostion " << base_index << std::endl;
                base_hash = base.getNextHash();
                base_shift++;
            }

            if (position == -1) {
                std::cout << "not found" << std::endl;
                std::cout << "base " << base_index << " base begin " << base_begin << " base shift " << base_shift << " new file " << new_file_index << " position "<< position << " shift " << shift << std::endl;
                diffrences_.push_back({OperationType::chng, base_begin + window_size - 1, base.getSizeContent() -1 , new_file_index + window_size - 1, new_file.getSizeContent() - 1});
                return;
            }

            std::cout << "base index " << base_index << " position " << position << std::endl;

            if (base_index + shift < position) {
                if (isFirstTime) {
                    if (position == 0 || base_index == 0) {
                        diffrences_.push_back(
                                    {OperationType::add, base_index, base_index, base_index, position - 1});
                        for (int it = 0; it < position && new_file.isNextHash(); it ++) {
                            new_file_hash = new_file.getNextHash();
                            new_file_index++;
                            std::cout << "in for " << it << " new file hash " << new_file_hash<< std::endl;
                        }
                    } else {
                        diffrences_.push_back({OperationType::chng, 0, base_index - 1, 0, position - 1});
                        shift += position - base_index;
                        for (int it = 0; it < position && new_file.isNextHash(); it ++) {
                            new_file_hash = new_file.getNextHash();
                            new_file_index++;
                            std::cout << "chang for " << it << " new file hash " << new_file_hash<< std::endl;
                        }
                    }

                }
                else {
                    std::cout << "base " << base_index << " base begin " << base_begin << " base shift " << base_shift << " new file " << new_file_index << " position "<< position << " shift " << shift << std::endl;
                    if (base_index != position && base_shift != window_size - 1) {
                        std::cout << "change in the middle\n";
                        diffrences_.push_back(
                            {OperationType::chng, base_begin + window_size - 1, base_index - 1, new_file_index + window_size - 1, position - 1});
                        shift += base_shift - window_size;
                        for (int it = new_file_index; it < position; it++) {
                            new_file_hash = new_file.getNextHash();
                            new_file_index++;
                            std::cout << "chang for " << it << " new file hash " << new_file_hash<< std::endl;
                        }
                    } else {
                        std::cout << "Else\n";
                        diffrences_.push_back({OperationType::add, base_index + 1, base_index + 1, base_index + 1, position});
                    }
                }
            }

            if (base_index > position) {
                if (isFirstTime) {
                    if (position == 0) {
                        diffrences_.push_back({OperationType::rm, base_begin, base_index - 1, 0, 0});

                    } else {
                        diffrences_.push_back({OperationType::chng, 0, base_index - 1, 0, position - 1});
                        shift += position - base_index;
                    }
                    std::cout << "changed 1\n";
                }
                else
                    diffrences_.push_back({OperationType::rm, base_begin + window_size - 1, base_index, 0, 0});
            }
        }

//        std::cout << "end main while base index " << base_index << " base hash " << base_hash << std::endl;
        isFirstTime = false;
        base_index++;
        new_file_index++;
        base_hash = base.getNextHash();
        new_file_hash =new_file.getNextHash();
    }

    if (new_file.isNextHash()) {
        std::cout << "dupa 3\n";
        const size_t position = base_index + window_size;
        diffrences_.push_back({OperationType::add, position, position, position, new_file.getSizeContent() - 1});
    }

}

void HashComparator::chechIfIsEqual(HashCreator &base, HashCreator &new_file)
{
    is_equal_ = true;

    auto base_hash = base.getHash();
    auto new_file_hash = new_file.getHash();

    while (base.isNextHash()) {
//        std::cout << "Base " << base.isNextHash() << " new_file " << new_file.isNextHash() << " base hash " << base_hash << " new_file hash " << new_file_hash <<std::endl;
        if (base_hash != new_file_hash || !new_file.isNextHash()) {
            is_equal_ = false;
            break;
        }

        base_hash = base.getNextHash();
        new_file_hash = new_file.getNextHash();
    }

    if (new_file.isNextHash()) {
        is_equal_ = false;
    }
}

bool HashComparator::isEqual() const
{
    return is_equal_;
}

std::vector<Operation> HashComparator::getDifferences() const
{
    return diffrences_;
}

