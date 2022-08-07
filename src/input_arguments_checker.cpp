#include "input_arguments_checker.h"

#include <string_view>

InputArgumentsChecker::InputArgumentsChecker(const int argc, const char **argv) {
  using namespace std::literals;
  if (argc == 1) return;

  if ((argv[1] == "-d"sv || argv[1] == "--delta"sv) && argc == 4) {
    is_delta_command_ = true;
  }

  if ((argv[1] == "-s"sv || argv[1] == "--signature"sv) && argc == 3) {
    is_signuture_command_ = true;
  }
}

bool InputArgumentsChecker::IsSignatureCommand() const { return is_signuture_command_; }

bool InputArgumentsChecker::IsDeltaCommand() const { return is_delta_command_; }

bool InputArgumentsChecker::IsInputParametersCorrect() const { return is_delta_command_ || is_signuture_command_; }
