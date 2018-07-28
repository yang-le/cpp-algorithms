// MIT License

// Copyright (c) 2018 Yang Le

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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
