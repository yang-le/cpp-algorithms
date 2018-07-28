#include "comparator.hpp"
#include "gtest/gtest.h"

TEST(ComparatorTest, comapre_default) {
  Comparator<int> comparator;
  Comparator<std::string> comparator2;

  EXPECT_TRUE(comparator.equal(0, 0));
  EXPECT_FALSE(comparator.equal(0, 1));
  EXPECT_TRUE(comparator2.equal("a", "a"));
  EXPECT_TRUE(comparator.lessThan(1, 2));
  EXPECT_TRUE(comparator.lessThan(-1, 2));
  EXPECT_TRUE(comparator2.lessThan("a", "b"));
  EXPECT_TRUE(comparator2.lessThan("a", "ab"));
  EXPECT_FALSE(comparator.lessThan(10, 2));
  EXPECT_FALSE(comparator.lessThanOrEqual(10, 2));
  EXPECT_TRUE(comparator.lessThanOrEqual(1, 1));
  EXPECT_TRUE(comparator.lessThanOrEqual(0, 0));
  EXPECT_FALSE(comparator.greaterThan(0, 0));
  EXPECT_TRUE(comparator.greaterThan(10, 0));
  EXPECT_TRUE(comparator.greaterThanOrEqual(10, 0));
  EXPECT_TRUE(comparator.greaterThanOrEqual(10, 10));
  EXPECT_FALSE(comparator.greaterThanOrEqual(0, 10));
}

TEST(ComparatorTest, comapre_custom) {
  Comparator<std::string> comparator(
      [](const std::string &a, const std::string &b) {
        if (a.length() == b.length()) {
          return 0;
        }

        return a.length() < b.length() ? -1 : 1;
      });

  EXPECT_TRUE(comparator.equal("a", "b"));
  EXPECT_FALSE(comparator.equal("a", ""));
  EXPECT_TRUE(comparator.lessThan("b", "aa"));
  EXPECT_FALSE(comparator.greaterThanOrEqual("a", "aa"));
  EXPECT_TRUE(comparator.greaterThanOrEqual("aa", "a"));
  EXPECT_TRUE(comparator.greaterThanOrEqual("a", "a"));

  comparator.reverse();

  EXPECT_TRUE(comparator.equal("a", "b"));
  EXPECT_FALSE(comparator.equal("a", ""));
  EXPECT_FALSE(comparator.lessThan("b", "aa"));
  EXPECT_TRUE(comparator.greaterThanOrEqual("a", "aa"));
  EXPECT_FALSE(comparator.greaterThanOrEqual("aa", "a"));
  EXPECT_TRUE(comparator.greaterThanOrEqual("a", "a"));
}
