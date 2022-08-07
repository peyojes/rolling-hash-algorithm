#include "input_arguments_checker.h"

#include <gtest/gtest.h>

TEST(InputArgumentsCheckerTests, noArguments_checkParameters_wrongCommand) {
  const char *input_arguments[] = {"rdiff"};
  InputArgumentsChecker checker(1, input_arguments);
  EXPECT_FALSE(checker.IsSignatureCommand());
  EXPECT_FALSE(checker.IsDeltaCommand());
  EXPECT_FALSE(checker.IsInputParametersCorrect());
}

TEST(InputArgumentsCheckerTests, signatureShortCommandWithOneFile_checkSignatureCommand_correctCommand) {
  const char *input_arguments[] = {"rdiff", "-s", "file"};
  InputArgumentsChecker checker(3, input_arguments);
  EXPECT_TRUE(checker.IsSignatureCommand());
  EXPECT_TRUE(checker.IsInputParametersCorrect());
}

TEST(InputArgumentsCheckerTests, signatureLongCommandWithOneFile_checkSignatureCommand_correctCommand) {
  const char *input_arguments[] = {"rdiff", "--signature", "file"};
  InputArgumentsChecker checker(3, input_arguments);
  EXPECT_TRUE(checker.IsSignatureCommand());
  EXPECT_TRUE(checker.IsInputParametersCorrect());
}

TEST(InputArgumentsCheckerTests, onlyFile_checkSignatureCommand_wrongCommand) {
  const char *input_arguments[] = {"rdiff", "file"};
  InputArgumentsChecker checker(2, input_arguments);
  EXPECT_FALSE(checker.IsSignatureCommand());
  EXPECT_FALSE(checker.IsInputParametersCorrect());
}

TEST(InputArgumentsCheckerTests, onlySignatureCommand_checkSignatureCommand_wrongCommand) {
  const char *input_arguments[] = {"rdiff", "--signature"};
  InputArgumentsChecker checker(2, input_arguments);
  EXPECT_FALSE(checker.IsSignatureCommand());
  EXPECT_FALSE(checker.IsInputParametersCorrect());
}

TEST(InputArgumentsCheckerTests, deltaShortCommandWithTwoFiles_checkDeltaCommand_correctCommand) {
  const char *input_arguments[] = {"rdiff", "-d", "file1", "file2"};
  InputArgumentsChecker checker(4, input_arguments);
  EXPECT_TRUE(checker.IsDeltaCommand());
  EXPECT_TRUE(checker.IsInputParametersCorrect());
}

TEST(InputArgumentsCheckerTests, deltaLongCommandWithTwoFiles_checkDeltaCommand_correctCommand) {
  const char *input_arguments[] = {"rdiff", "--delta", "file1", "file2"};
  InputArgumentsChecker checker(4, input_arguments);
  EXPECT_TRUE(checker.IsDeltaCommand());
  EXPECT_TRUE(checker.IsInputParametersCorrect());
}

TEST(InputArgumentsCheckerTests, onlyTwoFiles_checkDeltaCommand_wrongCommand) {
  const char *input_arguments[] = {"rdiff", "file1", "file2"};
  InputArgumentsChecker checker(3, input_arguments);
  EXPECT_FALSE(checker.IsDeltaCommand());
  EXPECT_FALSE(checker.IsInputParametersCorrect());
}

TEST(InputArgumentsCheckerTests, deltaLongCommandWithOneFile_checkDeltaCommand_wrongCommand) {
  const char *input_arguments[] = {"rdiff", "--delta", "file2"};
  InputArgumentsChecker checker(3, input_arguments);
  EXPECT_FALSE(checker.IsDeltaCommand());
  EXPECT_FALSE(checker.IsInputParametersCorrect());
}

TEST(InputArgumentsCheckerTests, deltaLongCommandWithoutFiles_checkDeltaCommand_wrongCommand) {
  const char *input_arguments[] = {"rdiff", "--delta"};
  InputArgumentsChecker checker(2, input_arguments);
  EXPECT_FALSE(checker.IsDeltaCommand());
  EXPECT_FALSE(checker.IsInputParametersCorrect());
}
