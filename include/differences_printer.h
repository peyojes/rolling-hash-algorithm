#ifndef DIFFERENCES_PRINTER_H
#define DIFFERENCES_PRINTER_H

#include <vector>
#include <spdlog/spdlog.h>
#include <string>

#include "hash_comparator.h"

class DifferencesPrinter {
 public:
    explicit DifferencesPrinter() {}
    void show(const std::string& base, const std::string& new_file, std::vector<Operation> differences);
};

#endif // DIFFERENCES_PRINTER_H
