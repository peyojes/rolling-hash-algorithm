#include "signature_creator.h"

#include <gtest/gtest.h>

#include <numeric>
#include <vector>

#include "mock/file_interface_mock.h"

using ::testing::_;
using ::testing::DoAll;
using ::testing::InSequence;
using ::testing::Return;
using ::testing::SetArgReferee;

TEST(SignatureCreatorTest, fileCanNotBeOpen_getSignature_return0) {
  FileMock file;
  SignatureCreator signatureCreator;
  EXPECT_CALL(file, isOpen()).WillOnce(Return(false));

  EXPECT_EQ(signatureCreator.getSignature(file), 0);
}

TEST(SignatureCreatorTest, fileWithOneLine_getSignature_hashOfOneLine) {
  FileMock file;
  SignatureCreator signatureCreator;

  std::string first_line{"first line"};
  EXPECT_CALL(file, isOpen()).WillOnce(Return(true));
  EXPECT_CALL(file, close()).Times(1);

  InSequence s;
  EXPECT_CALL(file, getLine(_)).WillOnce(DoAll(SetArgReferee<0>(first_line), Return(true)));
  EXPECT_CALL(file, getLine(_)).WillOnce(Return(false));

  const auto expected_hash = std::hash<std::string>{}(first_line);
  EXPECT_EQ(signatureCreator.getSignature(file), expected_hash);
}

TEST(SignatureCreatorTest, fileWithThreeLines_getSignature_hashOfThreeLines) {
  FileMock file;
  SignatureCreator signatureCreator;

  std::vector<std::string> lines{"first line", "second line", "three line"};
  EXPECT_CALL(file, isOpen()).WillOnce(Return(true));
  EXPECT_CALL(file, close()).Times(1);

  InSequence s;
  EXPECT_CALL(file, getLine(_)).WillOnce(DoAll(SetArgReferee<0>(lines[0]), Return(true)));
  EXPECT_CALL(file, getLine(_)).WillOnce(DoAll(SetArgReferee<0>(lines[1]), Return(true)));
  EXPECT_CALL(file, getLine(_)).WillOnce(DoAll(SetArgReferee<0>(lines[2]), Return(true)));
  EXPECT_CALL(file, getLine(_)).WillOnce(Return(false));

  std::size_t expected_hash = 0;
  std::for_each(lines.begin(), lines.end(),
                [&expected_hash](const std::string& line) { expected_hash += std::hash<std::string>{}(line); });

  EXPECT_EQ(signatureCreator.getSignature(file), expected_hash);
}
