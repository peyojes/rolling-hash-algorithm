#include <gtest/gtest.h>

#include "hash_comparator.h"

namespace {
const size_t WINDOW_SIZE = 4;
} // namespace

TEST(HashComparatorTest, theSomeHashCreators_compare_equal) {
    const std::string content = "Content of file";
    HashCreator base(content, WINDOW_SIZE), new_file(content, WINDOW_SIZE);
    HashComparator hash_comparator(base, new_file);

    EXPECT_TRUE(hash_comparator.isEqual());
}

TEST(HashComparatorTest, notTheSomeHashCreatorBaseIsLonger_compare_notEqual) {
    const std::string base_content = "Content of base file";
    const std::string new_file_content = "Content of base";
    HashCreator base(base_content, WINDOW_SIZE), new_file(new_file_content, WINDOW_SIZE);
    HashComparator hash_comparator(base, new_file);

    EXPECT_FALSE(hash_comparator.isEqual());
}

TEST(HashComparatorTest, notTheSomeHashCreatorBaseIsShorted_compare_notEqual) {
    const std::string base_content = "Content of base file";
    const std::string new_file_content = "Content of base file with another word";
    HashCreator base(base_content, WINDOW_SIZE), new_file(new_file_content, WINDOW_SIZE);
    HashComparator hash_comparator(base, new_file);

    EXPECT_FALSE(hash_comparator.isEqual());
}

TEST(HashComparatorTest, notTheSomeNewFileWithoutOneWord_compare_notEqual) {
    const std::string base_content = "Content of base file";
    const std::string new_file_content = "Content of file";
    HashCreator base(base_content, WINDOW_SIZE), new_file(new_file_content, WINDOW_SIZE);
    HashComparator hash_comparator(base, new_file);

    EXPECT_FALSE(hash_comparator.isEqual());
}

TEST(HashComparatorTest, theSomeHashCreators_compare_noDiffernce) {
    const std::string content = "Content of file";
    HashCreator base(content, WINDOW_SIZE), new_file(content, WINDOW_SIZE);
    HashComparator hash_comparator(base, new_file);
    EXPECT_TRUE(hash_comparator.getDifferences().empty());
}

bool operator==(const Operation& lhs, const Operation& rhs)
{
    return lhs.type == rhs.type
        && lhs.base_begin == rhs.base_begin
        && lhs.base_end == rhs.base_end
        && lhs.new_file_begin == rhs.new_file_begin
        && lhs.new_file_end == rhs.new_file_end;
}

std::string translate(const OperationType& type) {
    switch (type) {
    case OperationType::add :return "add";
    case OperationType::chng :return "chg";
    case OperationType::rm :return "rm";
    default: return "none";
    }
}

std::ostream& operator<<(std::ostream& os, const Operation o) {
  return os << "operation: " << translate(o.type) << " {" << o.base_begin << ", " << o.base_end << ", "
            << o.new_file_begin << ", " << o.new_file_end << "}" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const std::vector<Operation> operations) {
    for (const auto& o: operations) {
        os << o;
    }

    return os;
}

TEST(HashComparatorTest, notTheSomeHashCreatorBaseIsLonger_compare_removedLastWord) {
    const std::string base_content = "Content of base file";
    const std::string new_file_content = "Content of base";
    HashCreator base(base_content, WINDOW_SIZE), new_file(new_file_content, WINDOW_SIZE);
    HashComparator hash_comparator(base, new_file);
    Operation expected_operation{OperationType::rm, 15, 20, 0, 0};
    EXPECT_EQ(hash_comparator.getDifferences().front().type, expected_operation.type);
    EXPECT_EQ(hash_comparator.getDifferences().front().base_begin, expected_operation.base_begin);
    EXPECT_EQ(hash_comparator.getDifferences().front().base_end, expected_operation.base_end);
    EXPECT_EQ(hash_comparator.getDifferences().front().new_file_begin, expected_operation.new_file_end);
    EXPECT_EQ(hash_comparator.getDifferences().front().new_file_end, expected_operation.new_file_end);
}

TEST(HashComparatorTest, notTheSomeHashCreatorBaseIsLonger_compare_removedWordInMiddle) {
    const std::string base_content = "Content of base file";
    const std::string new_file_content = "Content of file";
    HashCreator base(base_content, WINDOW_SIZE), new_file(new_file_content, WINDOW_SIZE);
    HashComparator hash_comparator(base, new_file);
    Operation expected_operation{OperationType::rm, 11, 15, 0, 0};
    EXPECT_EQ(hash_comparator.getDifferences().front().type, expected_operation.type);
    EXPECT_EQ(hash_comparator.getDifferences().front().base_begin, expected_operation.base_begin);
    EXPECT_EQ(hash_comparator.getDifferences().front().base_end, expected_operation.base_end);
    EXPECT_EQ(hash_comparator.getDifferences().front().new_file_begin, expected_operation.new_file_end);
    EXPECT_EQ(hash_comparator.getDifferences().front().new_file_end, expected_operation.new_file_end);
}

// dodanie testu do backToBeginng in HashCreator



TEST(HashComparatorTest, notTheSomeHashCreatorBaseIsShorted_compare_removedFirstPart) {
    const std::string base_content = "Content of base file";
    const std::string new_file_content = "of base file";
    HashCreator base(base_content, WINDOW_SIZE), new_file(new_file_content, WINDOW_SIZE);
    HashComparator hash_comparator(base, new_file);

    Operation expected_operation{OperationType::rm, 0, 7, 0, 0};
    EXPECT_EQ(hash_comparator.getDifferences().front().type, expected_operation.type);
    EXPECT_EQ(hash_comparator.getDifferences().front().base_begin, expected_operation.base_begin);
    EXPECT_EQ(hash_comparator.getDifferences().front().base_end, expected_operation.base_end);
    EXPECT_EQ(hash_comparator.getDifferences().front().new_file_begin, expected_operation.new_file_end);
    EXPECT_EQ(hash_comparator.getDifferences().front().new_file_end, expected_operation.new_file_end);
}

TEST(HashComparatorTest, notTheSomeBaseNotHaveOneWord_compare_addOneWordInMiddle) {
    const std::string base_content = "Content of file";
    const std::string new_file_content = "Content of base file";
    HashCreator base(base_content, WINDOW_SIZE), new_file(new_file_content, WINDOW_SIZE);
    HashComparator hash_comparator(base, new_file);

    EXPECT_FALSE(hash_comparator.isEqual());
    Operation expected_operation{OperationType::add, 11, 11, 11, 15};
    EXPECT_EQ(hash_comparator.getDifferences().front().type, expected_operation.type);
    EXPECT_EQ(hash_comparator.getDifferences().front().base_begin, expected_operation.base_begin);
    EXPECT_EQ(hash_comparator.getDifferences().front().base_end, expected_operation.base_end);
    EXPECT_EQ(hash_comparator.getDifferences().front().new_file_begin, expected_operation.new_file_begin);
    EXPECT_EQ(hash_comparator.getDifferences().front().new_file_end, expected_operation.new_file_end);
}

TEST(HashComparatorTest, notTheSomeBaseNotHaveOneWord_compare_addOneWordAtBeginning) {
    const std::string base_content = "Content of file";
    const std::string new_file_content = "New Content of file";
    HashCreator base(base_content, WINDOW_SIZE), new_file(new_file_content, WINDOW_SIZE);
    HashComparator hash_comparator(base, new_file);

    EXPECT_FALSE(hash_comparator.isEqual());
    Operation expected_operation{OperationType::add, 0, 0, 0, 3};
    EXPECT_EQ(hash_comparator.getDifferences().front().type, expected_operation.type);
    EXPECT_EQ(hash_comparator.getDifferences().front().base_begin, expected_operation.base_begin);
    EXPECT_EQ(hash_comparator.getDifferences().front().base_end, expected_operation.base_end);
    EXPECT_EQ(hash_comparator.getDifferences().front().new_file_begin, expected_operation.new_file_begin);
    EXPECT_EQ(hash_comparator.getDifferences().front().new_file_end, expected_operation.new_file_end);
}

TEST(HashComparatorTest, notTheSomeBaseNotHaveOneWord_compare_addOneWordAtTheEnd) {
    const std::string base_content = "Content of file";
    const std::string new_file_content = "Content of file which";
    HashCreator base(base_content, WINDOW_SIZE), new_file(new_file_content, WINDOW_SIZE);
    HashComparator hash_comparator(base, new_file);

    EXPECT_FALSE(hash_comparator.isEqual());
    Operation expected_operation{OperationType::add, 15, 15, 15, 20};
    EXPECT_EQ(hash_comparator.getDifferences().front().type, expected_operation.type);
    EXPECT_EQ(hash_comparator.getDifferences().front().base_begin, expected_operation.base_begin);
    EXPECT_EQ(hash_comparator.getDifferences().front().base_end, expected_operation.base_end);
    EXPECT_EQ(hash_comparator.getDifferences().front().new_file_begin, expected_operation.new_file_begin);
    EXPECT_EQ(hash_comparator.getDifferences().front().new_file_end, expected_operation.new_file_end);
}

TEST(HashComparatorTest, notTheSomeFirstWordMismatchBaseShorted_compare_changeAtTheBeginning) {
    const std::string base_content = "Content of file";
    const std::string new_file_content = "Information of file";
    HashCreator base(base_content, WINDOW_SIZE), new_file(new_file_content, WINDOW_SIZE);
    HashComparator hash_comparator(base, new_file);

    EXPECT_FALSE(hash_comparator.isEqual());
    Operation expected_operation{OperationType::chng, 0, 6, 0, 10};
    EXPECT_EQ(hash_comparator.getDifferences().size(), 1);
    EXPECT_EQ(hash_comparator.getDifferences().front().type, expected_operation.type);
    EXPECT_EQ(hash_comparator.getDifferences().front().base_begin, expected_operation.base_begin);
    EXPECT_EQ(hash_comparator.getDifferences().front().base_end, expected_operation.base_end);
    EXPECT_EQ(hash_comparator.getDifferences().front().new_file_begin, expected_operation.new_file_begin);
    EXPECT_EQ(hash_comparator.getDifferences().front().new_file_end, expected_operation.new_file_end);
}

TEST(HashComparatorTest, nnotTheSomeFirstWordMismatchBaseLonger_compare_changeAtTheBeginning) {
    const std::string base_content = "Information of file";
    const std::string new_file_content = "Content of file which";
    HashCreator base(base_content, WINDOW_SIZE), new_file(new_file_content, WINDOW_SIZE);
    HashComparator hash_comparator(base, new_file);

    EXPECT_FALSE(hash_comparator.isEqual());
    Operation expected_operation{OperationType::chng, 0, 10, 0, 6};
    EXPECT_EQ(hash_comparator.getDifferences().front().type, expected_operation.type);
    EXPECT_EQ(hash_comparator.getDifferences().front().base_begin, expected_operation.base_begin);
    EXPECT_EQ(hash_comparator.getDifferences().front().base_end, expected_operation.base_end);
    EXPECT_EQ(hash_comparator.getDifferences().front().new_file_begin, expected_operation.new_file_begin);
    EXPECT_EQ(hash_comparator.getDifferences().front().new_file_end, expected_operation.new_file_end);
}

TEST(HashComparatorTest, notTheSomeFirstWordMismatchBaseShorted_compare_changeInTheMiddle) {
    const std::string base_content = "Content of file";
    const std::string new_file_content = "Content from file";
    HashCreator base(base_content, WINDOW_SIZE), new_file(new_file_content, WINDOW_SIZE);
    HashComparator hash_comparator(base, new_file);

    EXPECT_FALSE(hash_comparator.isEqual());
    Operation expected_operation{OperationType::chng, 8, 9, 8, 11};
    EXPECT_EQ(hash_comparator.getDifferences().front().type, expected_operation.type);
    EXPECT_EQ(hash_comparator.getDifferences().front().base_begin, expected_operation.base_begin);
    EXPECT_EQ(hash_comparator.getDifferences().front().base_end, expected_operation.base_end);
    EXPECT_EQ(hash_comparator.getDifferences().front().new_file_begin, expected_operation.new_file_begin);
    EXPECT_EQ(hash_comparator.getDifferences().front().new_file_end, expected_operation.new_file_end);
}

TEST(HashComparatorTest, notTheSomeFirstWordMismatchBaseShorted_compare_changeInTheMiddle2) {
    const std::string base_content = "Content ofo file";
    const std::string new_file_content = "Content from file";
    HashCreator base(base_content, WINDOW_SIZE), new_file(new_file_content, WINDOW_SIZE);
    HashComparator hash_comparator(base, new_file);

    EXPECT_FALSE(hash_comparator.isEqual());
    Operation expected_operation{OperationType::chng, 8, 10, 8, 11};
    EXPECT_EQ(hash_comparator.getDifferences().front().type, expected_operation.type);
    EXPECT_EQ(hash_comparator.getDifferences().front().base_begin, expected_operation.base_begin);
    EXPECT_EQ(hash_comparator.getDifferences().front().base_end, expected_operation.base_end);
    EXPECT_EQ(hash_comparator.getDifferences().front().new_file_begin, expected_operation.new_file_begin);
    EXPECT_EQ(hash_comparator.getDifferences().front().new_file_end, expected_operation.new_file_end);
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
        << "Result:\n" << result << "Expect:\n" << params.expected << std::endl
        << "base: \t\t" << params.base << "\nnew file: \t" << params.new_file << std::endl;
               ;


    EXPECT_EQ(result.front(), params.expected)
            << "base: \t\t" << params.base << "\nnew file: \t" << params.new_file << std::endl;
}

HashComparatorParam make(
        const std::string& base,
        const std::string& new_file,
        const size_t exp_numb_of_oper,
        const Operation& operation) {
    return HashComparatorParam{base, new_file, exp_numb_of_oper, operation};
}

INSTANTIATE_TEST_SUITE_P(FindDiffernce, HashComparatorTestParam,
    testing::Values(
        make("Content of file memory", "Content from file memory", 1, {OperationType::chng, 8, 9, 8, 11}),
        make("Content of file", "Content from file", 1, {OperationType::chng, 8, 9, 8, 11}),
        make("Content of file", "Content of directory", 1, {OperationType::chng, 11, 14, 11, 19}),
        make("Content of directory", "Content of file", 1, {OperationType::chng, 11, 19, 11, 14})
    ));
