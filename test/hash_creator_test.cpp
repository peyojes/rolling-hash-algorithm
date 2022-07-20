#include <gtest/gtest.h>
#include <math.h>

#include "hash_creator.h"

const size_t WINDOW_SIZE = 4;
const size_t BASE = 11;

using std::pow;

TEST(HashCreatorTest, emptyContent_isNextHash_faile) {
    HashCreator hash_creator("", WINDOW_SIZE);
    EXPECT_FALSE(hash_creator.isNextHash());
    EXPECT_EQ(hash_creator.getHash(), 0);
}

TEST(HashCreatorTest, notFullDataForWindowSize_isNextHash_false) {
    HashCreator hash_creator("012", WINDOW_SIZE);
    EXPECT_FALSE(hash_creator.isNextHash());
    size_t expected_hash = 48 + 49*pow(BASE, 1) + 50*pow(BASE, 2);
    EXPECT_EQ(hash_creator.getHash(), expected_hash);
}

TEST(HashCreatorTest, oneElementMoreThanWindowSize_isNextHash_true) {
    HashCreator hash_creator("01234567890", WINDOW_SIZE);
    EXPECT_TRUE(hash_creator.isNextHash());
}

TEST(HashCreatorTest, oneElementMoreThanWindowSize_2xisNextHashAndGetNextHash_allCorrect) {
    HashCreator hash_creator("01234", WINDOW_SIZE);

    EXPECT_TRUE(hash_creator.getHash());
    size_t expected_hash = 48 + 49*pow(BASE, 1) + 50*pow(BASE, 2)+ 51*pow(BASE,3);
    EXPECT_TRUE(hash_creator.isNextHash());
    EXPECT_EQ(hash_creator.getNextHash(), expected_hash);

    expected_hash = 49 + 50*pow(BASE, 1)+ 51*pow(BASE,2) + 52*pow(BASE,3);
    EXPECT_EQ(hash_creator.getNextHash(), expected_hash);

    EXPECT_FALSE(hash_creator.isNextHash());
}

TEST(HashCreatorTest, fullWindow_getHashFirstCall_calculateFirstHash) {
    HashCreator hash_creator("0123", WINDOW_SIZE);

    size_t expected_hash = 48 + 49*pow(BASE, 1) + 50*pow(BASE, 2)+ 51*pow(BASE,3);
    EXPECT_FALSE(hash_creator.isNextHash());
    EXPECT_EQ(hash_creator.getHash(), expected_hash);
}
