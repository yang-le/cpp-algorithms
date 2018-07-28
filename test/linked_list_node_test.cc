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

#include "linked_list_node.hpp"
#include <tuple>
#include "gtest/gtest.h"

TEST(LinkedListNodeTest, create_with_value) {
  LinkedListNode<int> node(1);

  EXPECT_EQ(node.value_, 1);
  EXPECT_EQ(node.next_, nullptr);
}

TEST(LinkedListNodeTest, create_with_object) {
  auto obj = std::make_pair(1, "test");

  LinkedListNode<std::pair<int, std::string>> node(obj);

  EXPECT_EQ(node.value_.first, obj.first);
  EXPECT_EQ(node.value_.second, obj.second);
  EXPECT_EQ(node.next_, nullptr);
}

TEST(LinkedListNodeTest, link) {
  auto node2 = std::make_shared<LinkedListNode<int>>(2);
  auto node1 = std::make_shared<LinkedListNode<int>>(1, node2);

  EXPECT_NE(node1->next_, nullptr);
  EXPECT_EQ(node2->next_, nullptr);
  EXPECT_EQ(node1->value_, 1);
  EXPECT_EQ(node1->next_->value_, 2);
}

TEST(LinkedListNodeTest, to_string) {
  LinkedListNode<int> node(1);

  EXPECT_EQ(node.toString(), "1");

  node.value_ = 2;
  EXPECT_EQ(node.toString(), "2");
}

TEST(LinkedListNodeTest, to_string_with_custom_stringifier) {
  auto obj = std::make_pair(1, "test");

  LinkedListNode<std::pair<int, std::string>> node(obj);

  std::string result =
      node.toString([](const std::pair<int, std::string>& obj) {
        return std::string("first: ") + std::to_string(obj.first) +
               std::string(", second: ") + obj.second;
      });

  EXPECT_EQ(result, "first: 1, second: test");
}
