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

#include "linked_list.hpp"
#include "gtest/gtest.h"

TEST(LinkedListTest, create_empty) {
  LinkedList<int> list;

  EXPECT_EQ(list.toString(), "");
}

TEST(LinkedListTest, append) {
  LinkedList<int> list;

  EXPECT_EQ(list.head_, nullptr);
  EXPECT_EQ(list.tail_, nullptr);

  list.append(1);
  list.append(2);

  EXPECT_EQ(list.toString(), "1,2");
}

TEST(LinkedListTest, prepend) {
  LinkedList<int> list;

  list.prepend(2);
  EXPECT_EQ(list.head_->toString(), "2");
  EXPECT_EQ(list.tail_->toString(), "2");

  list.append(1);
  list.prepend(3);

  EXPECT_EQ(list.toString(), "3,2,1");
}

TEST(LinkedListTest, remove_by_value) {
  LinkedList<int> list;

  EXPECT_EQ(list.remove(5), nullptr);

  list.append(1);
  list.append(1);
  list.append(2);
  list.append(3);
  list.append(3);
  list.append(3);
  list.append(4);
  list.append(5);

  EXPECT_EQ(list.head_->toString(), "1");
  EXPECT_EQ(list.tail_->toString(), "5");

  auto deletedNode = list.remove(3);
  EXPECT_EQ(deletedNode->value_, 3);
  EXPECT_EQ(list.toString(), "1,1,2,4,5");

  list.remove(3);
  EXPECT_EQ(list.toString(), "1,1,2,4,5");

  list.remove(1);
  EXPECT_EQ(list.toString(), "2,4,5");

  EXPECT_EQ(list.head_->toString(), "2");
  EXPECT_EQ(list.tail_->toString(), "5");

  list.remove(5);
  EXPECT_EQ(list.toString(), "2,4");

  EXPECT_EQ(list.head_->toString(), "2");
  EXPECT_EQ(list.tail_->toString(), "4");

  list.remove(4);
  EXPECT_EQ(list.toString(), "2");

  EXPECT_EQ(list.head_->toString(), "2");
  EXPECT_EQ(list.tail_->toString(), "2");

  list.remove(2);
  EXPECT_EQ(list.toString(), "");
}

TEST(LinkedListTest, delete_tail) {
  LinkedList<int> list;

  list.append(1);
  list.append(2);
  list.append(3);

  EXPECT_EQ(list.head_->toString(), "1");
  EXPECT_EQ(list.tail_->toString(), "3");

  auto deletedNode1 = list.deleteTail();

  EXPECT_EQ(deletedNode1->value_, 3);
  EXPECT_EQ(list.toString(), "1,2");
  EXPECT_EQ(list.head_->toString(), "1");
  EXPECT_EQ(list.tail_->toString(), "2");

  auto deletedNode2 = list.deleteTail();

  EXPECT_EQ(deletedNode2->value_, 2);
  EXPECT_EQ(list.toString(), "1");
  EXPECT_EQ(list.head_->toString(), "1");
  EXPECT_EQ(list.tail_->toString(), "1");

  auto deletedNode3 = list.deleteTail();

  EXPECT_EQ(deletedNode3->value_, 1);
  EXPECT_EQ(list.toString(), "");
  EXPECT_EQ(list.head_, nullptr);
  EXPECT_EQ(list.tail_, nullptr);
}

TEST(LinkedListTest, delete_head) {
  LinkedList<int> list;

  EXPECT_EQ(list.deleteHead(), nullptr);

  list.append(1);
  list.append(2);

  EXPECT_EQ(list.head_->toString(), "1");
  EXPECT_EQ(list.tail_->toString(), "2");

  auto deletedNode1 = list.deleteHead();

  EXPECT_EQ(deletedNode1->value_, 1);
  EXPECT_EQ(list.toString(), "2");
  EXPECT_EQ(list.head_->toString(), "2");
  EXPECT_EQ(list.tail_->toString(), "2");

  auto deletedNode2 = list.deleteHead();

  EXPECT_EQ(deletedNode2->value_, 2);
  EXPECT_EQ(list.toString(), "");
  EXPECT_EQ(list.head_, nullptr);
  EXPECT_EQ(list.tail_, nullptr);
}

TEST(LinkedListTest, to_string) {
  LinkedList<std::pair<int, std::string>> list;

  auto nodeValue1 = std::make_pair(1, "key1");
  auto nodeValue2 = std::make_pair(2, "key2");

  list.append(nodeValue1).prepend(nodeValue2);

  std::string result =
      list.toString([](const std::pair<int, std::string>& pair) {
        return pair.second + ":" + std::to_string(pair.first);
      });

  EXPECT_EQ(result, "key2:2,key1:1");
}

TEST(LinkedListTest, find_by_value) {
  LinkedList<int> list;

  EXPECT_EQ(list.find(5), nullptr);

  list.append(1);
  EXPECT_NE(list.find(1), nullptr);

  list.append(2).append(3);

  auto node = list.find(2);

  EXPECT_EQ(node->value_, 2);
  EXPECT_EQ(list.find(5), nullptr);
}

TEST(LinkedListTest, find_by_callback) {
  LinkedList<std::pair<int, std::string>> list;

  list.append(std::make_pair(1, "test1"))
      .append(std::make_pair(2, "test2"))
      .append(std::make_pair(3, "test3"));

  auto node = list.find([](const std::pair<int, std::string>& pair) {
    return pair.second == "test2";
  });

  EXPECT_NE(node, nullptr);
  EXPECT_EQ(node->value_.first, 2);
  EXPECT_EQ(node->value_.second, "test2");

  auto result = list.find([](const std::pair<int, std::string>& pair) {
    return pair.second == "test5";
  });

  EXPECT_EQ(result, nullptr);
}

TEST(LinkedListTest, find_by_custom_compare) {
  LinkedList<std::pair<int, std::string>> list(
      [](const std::pair<int, std::string>& a,
         const std::pair<int, std::string>& b) {
        if (a.second == b.second) return 0;

        return a.second < b.second ? -1 : 1;
      });

  list.append(std::make_pair(1, "test1"))
      .append(std::make_pair(2, "test2"))
      .append(std::make_pair(3, "test3"));

  auto node = list.find(std::make_pair(2, std::string("test2")));

  EXPECT_NE(node, nullptr);
  EXPECT_EQ(node->value_.first, 2);
  EXPECT_EQ(node->value_.second, "test2");
  EXPECT_EQ(list.find(std::make_pair(2, std::string("test5"))), nullptr);
}
