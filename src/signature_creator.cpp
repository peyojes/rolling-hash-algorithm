#include "signature_creator.h"

#include <functional>

std::size_t SignatureCreator::getSignature(FileInterface& file) const
{
    std::string line;
    std::size_t hash = 0;
    if (file.isOpen()) {
        while (file.getLine(line)) {
            hash += std::hash<std::string>{}(line);
        }
        file.close();
    }
    return hash;
}
