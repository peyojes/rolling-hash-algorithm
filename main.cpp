#include <iostream>

#include <spdlog/spdlog.h>

#include "differences_printer.h"
#include "file.h"
#include "hash_creator.h"
#include "hash_comparator.h"
#include "input_arguments_checker.h"
#include "signature_creator.h"

using std::cout;
using std::endl;
using std::to_string;


namespace  {
constexpr size_t WINDOW_SIZE = 4;
}

int main(int argc, const char** argv) {

    spdlog::set_pattern("[%l] %v");

    InputArgumentsChecker inputArgumentChecker(argc, argv);

    if (!inputArgumentChecker.IsInputParametersCorrect()) {
      spdlog::warn("Wrong input parameters");
      spdlog::info("Usage: {} [OPTION] <base> <new_file>", argv[0]);
      spdlog::info("Options:");
      spdlog::info("    -d, --delta      create delta from <base> and <new_file>");
      spdlog::info("    -s, --signature  create siganture for <base>");

      return 0;
    }

    if (inputArgumentChecker.IsSignatureCommand()) {
      const char* file_path = argv[2];
      File file(file_path);

      if (!file.isExists()) {
          spdlog::error("{} doesn't exists. Can not create signature", file_path);
          return 0;
      }

      SignatureCreator signatureCreator;
      spdlog::info("Signature: {}", to_string(signatureCreator.getSignature(file)));
    }

    if (inputArgumentChecker.IsDeltaCommand()) {
      spdlog::info("Start delta command");
      const char* base_file_path = argv[2];
      const char* new_file_path = argv[3];


      File base_file(base_file_path);
      File new_file(new_file_path);
      const auto base_content = base_file.getContent();
      const auto new_file_content = new_file.getContent();
      HashCreator base_creator(base_content, WINDOW_SIZE);
      HashCreator new_file_creator(new_file_content, WINDOW_SIZE);

      HashComparator comparator(base_creator, new_file_creator);

      DifferencesPrinter printer;
      printer.show(base_content, new_file_content, comparator.getDifferences());
    }

    return 0;
}
