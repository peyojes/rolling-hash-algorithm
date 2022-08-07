#include "hash_comparator.h"

#include <gtest/gtest.h>

namespace {

const size_t WINDOW_SIZE = 4;

constexpr auto add = Operation::OperationType::add;
constexpr auto rm = Operation::OperationType::rm;
constexpr auto chng = Operation::OperationType::chng;
}  // namespace

TEST(HashComparatorTest, theSomeHashCreators_compare_equal) {
  const std::string content = "Content of file";
  HashCreator base(content, WINDOW_SIZE), new_file(content, WINDOW_SIZE);
  HashComparator hash_comparator(base, new_file);

  EXPECT_TRUE(hash_comparator.isEqual());
  EXPECT_TRUE(hash_comparator.getDifferences().empty());
}

bool operator==(const Operation& lhs, const Operation& rhs) {
  return lhs.type == rhs.type && lhs.base_begin == rhs.base_begin && lhs.base_end == rhs.base_end &&
         lhs.new_file_begin == rhs.new_file_begin && lhs.new_file_end == rhs.new_file_end;
}

std::string translate(const Operation::OperationType& type) {
  switch (type) {
    case add:
      return "add";
    case chng:
      return "chg";
    case rm:
      return "rm";
    default:
      return "none";
  }
}

std::ostream& operator<<(std::ostream& os, const Operation o) {
  return os << "operation: " << translate(o.type) << " {" << o.base_begin << ", " << o.base_end << ", "
            << o.new_file_begin << ", " << o.new_file_end << "}" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const std::vector<Operation> operations) {
  for (const auto& o : operations) {
    os << o;
  }

  return os;
}

struct HashComparatorParam {
  const std::string base;
  const std::string new_file;
  const size_t expected_number_of_operation;
  const Operation expected;
};

class HashComparatorTestParam : public testing::TestWithParam<HashComparatorParam> {};

TEST_P(HashComparatorTestParam, compare) {
  const auto params = GetParam();

  HashCreator base(params.base, WINDOW_SIZE), new_file(params.new_file, WINDOW_SIZE);
  HashComparator hash_comparator(base, new_file);

  const auto result = hash_comparator.getDifferences();
  EXPECT_FALSE(hash_comparator.isEqual());
  EXPECT_EQ(result.size(), params.expected_number_of_operation)
      << "Result:\n"
      << result << "Expect:\n"
      << params.expected << std::endl
      << "base: \t\t" << params.base << "\nnew file: \t" << params.new_file << std::endl;

  EXPECT_EQ(result.front(), params.expected)
      << "base: \t\t" << params.base << "\nnew file: \t" << params.new_file << std::endl;
}

HashComparatorParam make(const std::string& base, const std::string& new_file, const size_t exp_numb_of_oper,
                         const Operation& operation) {
  return HashComparatorParam{base, new_file, exp_numb_of_oper, operation};
}

INSTANTIATE_TEST_SUITE_P(FindDiffernce, HashComparatorTestParam,
                         testing::Values(make("Content of base file", "Content of base", 1, {rm, 15, 20, 0, 0}),
                                         make("Content of base file", "Content of file", 1, {rm, 11, 15, 0, 0}),
                                         make("Content of base file", "of base file", 1, {rm, 0, 7, 0, 0}),
                                         make("Content of file", "Content of base file", 1, {add, 11, 11, 11, 15}),
                                         make("Content of file", "New Content of file", 1, {add, 0, 0, 0, 3}),
                                         make("Content of file", "Content of file which", 1, {add, 14, 14, 15, 20}),
                                         make("Content of file", "Information of file", 1, {chng, 0, 6, 0, 10}),
                                         make("Information of file", "Content of file", 1, {chng, 0, 10, 0, 6}),
                                         make("Content ofo file", "Content from file", 1, {chng, 8, 10, 8, 11}),
                                         make("Content of file", "Content from file", 1, {chng, 8, 9, 8, 11}),
                                         make("Content of file", "Content of directory", 1, {chng, 11, 14, 11, 19}),
                                         make("Content of directory", "Content of file", 1, {chng, 11, 19, 11, 14})));
