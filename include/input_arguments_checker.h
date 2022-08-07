#ifndef INPUTARGUMENTSCHECKER_H
#define INPUTARGUMENTSCHECKER_H

class InputArgumentsChecker {
 public:
  InputArgumentsChecker(const int argc, const char **argv);
  bool IsSignatureCommand() const;
  bool IsDeltaCommand() const;
  bool IsInputParametersCorrect() const;

 private:
  bool is_signuture_command_;
  bool is_delta_command_;
};

#endif  // INPUTARGUMENTSCHECKER_H
