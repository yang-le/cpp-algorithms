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

#include "stack.hpp"
#include "gtest/gtest.h"

TEST(StackTest, create_empty) {
  Stack<int> stack;

  EXPECT_EQ(stack.toString(), "");
}

TEST(StackTest, push_value) {
  Stack<int> stack;

  stack.push(1);
  stack.push(2);

  EXPECT_EQ(stack.toString(), "1,2");
}

TEST(StackTest, push_pop_objects) {
  Stack<std::pair<std::string, std::string>> stack;

  stack.push(std::make_pair("test1", "key1"));
  stack.push(std::make_pair("test2", "key2"));

  std::string result =
      stack.toString([](const std::pair<std::string, std::string>& pair) {
        return pair.second + ":" + pair.first;
      });

  EXPECT_EQ(result, "key1:test1,key2:test2");
  EXPECT_EQ(stack.pop().first, "test2");
  EXPECT_EQ(stack.pop().first, "test1");
}

TEST(StackTest, peak) {
  Stack<int> stack;

  EXPECT_EQ(stack.peek(), nullptr);

  stack.push(1);
  stack.push(2);

  EXPECT_EQ(*stack.peek(), 2);
  EXPECT_EQ(*stack.peek(), 2);
}

TEST(StackTest, is_empty) {
  Stack<int> stack;

  EXPECT_TRUE(stack.isEmpty());

  stack.push(1);

  EXPECT_FALSE(stack.isEmpty());
}

TEST(StackTest, pop) {
  Stack<int> stack;

  stack.push(1);
  stack.push(2);

  EXPECT_EQ(stack.pop(), 2);
  EXPECT_EQ(stack.pop(), 1);
  // EXPECT_EQ(stack.pop(), nullptr);
  EXPECT_TRUE(stack.isEmpty());
}

TEST(StackTest, to_array) {
  Stack<int> stack;

  EXPECT_EQ(stack.peek(), nullptr);

  stack.push(1);
  stack.push(2);
  stack.push(3);

  EXPECT_EQ(stack.toArray(), std::vector<int>({3, 2, 1}));
}
