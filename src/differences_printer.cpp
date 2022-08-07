#include "differences_printer.h"

#include "hash_comparator.h"

void DifferencesPrinter::show(const std::string &base, const std::string &new_file,
                              std::vector<Operation> differences) {
  spdlog::set_pattern("%v");

  for (const auto &diff : differences) {
    switch (diff.type) {
      case Operation::OperationType::add: {
        spdlog::info("add to base at position {} with content `{}`", diff.base_begin,
                     new_file.substr(diff.new_file_begin, diff.new_file_end - diff.new_file_begin));
        break;
      }
      case Operation::OperationType::rm: {
        spdlog::info("remove from base at position from {} to {} with content `{}`", diff.base_begin, diff.base_end,
                     base.substr(diff.base_begin, diff.base_end - diff.base_begin));
        break;
      }
      case Operation::OperationType::chng: {
        spdlog::info(
            "change from base at position from {} to {} with base content `{}`"
            " to new file at position from {} to {} with new content `{}`",
            diff.base_begin, diff.base_end, base.substr(diff.base_begin, diff.base_end - diff.base_begin + 1),
            diff.new_file_begin, diff.new_file_end,
            new_file.substr(diff.new_file_begin, diff.new_file_end - diff.new_file_begin + 1));
        break;
      }
      default:
        spdlog::error("Not found type for difference");
    }
  }

  spdlog::set_pattern("[%l] %v");
}
