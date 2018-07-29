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

#include "avl_tree.hpp"
#include "gtest/gtest.h"

TEST(AvlTreeNodeTest, simple_left_left) {
  auto tree = std::make_shared<AvlTree<int>>();

  tree->insert(4);
  tree->insert(3);
  tree->insert(2);

  EXPECT_EQ(tree->toString(), "2,3,4");
  EXPECT_EQ(tree->root_->value_, 3);
  EXPECT_EQ(tree->root_->height(), 1);

  tree->insert(1);

  EXPECT_EQ(tree->toString(), "1,2,3,4");
  EXPECT_EQ(tree->root_->value_, 3);
  EXPECT_EQ(tree->root_->height(), 2);

  tree->insert(0);

  EXPECT_EQ(tree->toString(), "0,1,2,3,4");
  EXPECT_EQ(tree->root_->value_, 3);
  EXPECT_EQ(tree->root_->left_->value_, 1);
  EXPECT_EQ(tree->root_->height(), 2);
}

TEST(AvlTreeNodeTest, complex_left_left) {
  auto tree = std::make_shared<AvlTree<int>>();

  tree->insert(30);
  tree->insert(20);
  tree->insert(40);
  tree->insert(10);

  EXPECT_EQ(tree->root_->value_, 30);
  EXPECT_EQ(tree->root_->height(), 2);
  EXPECT_EQ(tree->toString(), "10,20,30,40");

  tree->insert(25);
  EXPECT_EQ(tree->root_->value_, 30);
  EXPECT_EQ(tree->root_->height(), 2);
  EXPECT_EQ(tree->toString(), "10,20,25,30,40");

  tree->insert(5);
  EXPECT_EQ(tree->root_->value_, 20);
  EXPECT_EQ(tree->root_->height(), 2);
  EXPECT_EQ(tree->toString(), "5,10,20,25,30,40");
}

TEST(AvlTreeNodeTest, simple_right_right) {
  auto tree = std::make_shared<AvlTree<int>>();

  tree->insert(2);
  tree->insert(3);
  tree->insert(4);

  EXPECT_EQ(tree->toString(), "2,3,4");
  EXPECT_EQ(tree->root_->value_, 3);
  EXPECT_EQ(tree->root_->height(), 1);

  tree->insert(5);

  EXPECT_EQ(tree->toString(), "2,3,4,5");
  EXPECT_EQ(tree->root_->value_, 3);
  EXPECT_EQ(tree->root_->height(), 2);

  tree->insert(6);

  EXPECT_EQ(tree->toString(), "2,3,4,5,6");
  EXPECT_EQ(tree->root_->value_, 3);
  EXPECT_EQ(tree->root_->right_->value_, 5);
  EXPECT_EQ(tree->root_->height(), 2);
}

TEST(AvlTreeNodeTest, complex_right_right) {
  auto tree = std::make_shared<AvlTree<int>>();

  tree->insert(30);
  tree->insert(20);
  tree->insert(40);
  tree->insert(50);

  EXPECT_EQ(tree->root_->value_, 30);
  EXPECT_EQ(tree->root_->height(), 2);
  EXPECT_EQ(tree->toString(), "20,30,40,50");

  tree->insert(35);
  EXPECT_EQ(tree->root_->value_, 30);
  EXPECT_EQ(tree->root_->height(), 2);
  EXPECT_EQ(tree->toString(), "20,30,35,40,50");

  tree->insert(55);
  EXPECT_EQ(tree->root_->value_, 40);
  EXPECT_EQ(tree->root_->height(), 2);
  EXPECT_EQ(tree->toString(), "20,30,35,40,50,55");
}

TEST(AvlTreeNodeTest, left_right) {
  auto tree = std::make_shared<AvlTree<int>>();

  tree->insert(30);
  tree->insert(20);
  tree->insert(25);

  EXPECT_EQ(tree->root_->height(), 1);
  EXPECT_EQ(tree->root_->value_, 25);
  EXPECT_EQ(tree->toString(), "20,25,30");
}

TEST(AvlTreeNodeTest, right_left) {
  auto tree = std::make_shared<AvlTree<int>>();

  tree->insert(30);
  tree->insert(40);
  tree->insert(35);

  EXPECT_EQ(tree->root_->height(), 1);
  EXPECT_EQ(tree->root_->value_, 35);
  EXPECT_EQ(tree->toString(), "30,35,40");
}

TEST(AvlTreeNodeTest, balance_case_1) {
  // @see: https://www.youtube.com/watch?v=rbg7Qf8GkQ4&t=839s
  auto tree = std::make_shared<AvlTree<int>>();

  tree->insert(1);
  tree->insert(2);
  tree->insert(3);

  EXPECT_EQ(tree->root_->value_, 2);
  EXPECT_EQ(tree->root_->height(), 1);
  EXPECT_EQ(tree->toString(), "1,2,3");

  tree->insert(6);

  EXPECT_EQ(tree->root_->value_, 2);
  EXPECT_EQ(tree->root_->height(), 2);
  EXPECT_EQ(tree->toString(), "1,2,3,6");

  tree->insert(15);

  EXPECT_EQ(tree->root_->value_, 2);
  EXPECT_EQ(tree->root_->height(), 2);
  EXPECT_EQ(tree->toString(), "1,2,3,6,15");

  tree->insert(-2);

  EXPECT_EQ(tree->root_->value_, 2);
  EXPECT_EQ(tree->root_->height(), 2);
  EXPECT_EQ(tree->toString(), "-2,1,2,3,6,15");

  tree->insert(-5);

  EXPECT_EQ(tree->root_->value_, 2);
  EXPECT_EQ(tree->root_->height(), 2);
  EXPECT_EQ(tree->toString(), "-5,-2,1,2,3,6,15");

  tree->insert(-8);

  EXPECT_EQ(tree->root_->value_, 2);
  EXPECT_EQ(tree->root_->height(), 3);
  EXPECT_EQ(tree->toString(), "-8,-5,-2,1,2,3,6,15");
}

TEST(AvlTreeNodeTest, balance_case_2) {
  // @see https://www.youtube.com/watch?v=7m94k2Qhg68
  auto tree = std::make_shared<AvlTree<int>>();

  tree->insert(43);
  tree->insert(18);
  tree->insert(22);
  tree->insert(9);
  tree->insert(21);
  tree->insert(6);

  EXPECT_EQ(tree->root_->value_, 18);
  EXPECT_EQ(tree->root_->height(), 2);
  EXPECT_EQ(tree->toString(), "6,9,18,21,22,43");

  tree->insert(8);

  EXPECT_EQ(tree->root_->value_, 18);
  EXPECT_EQ(tree->root_->height(), 2);
  EXPECT_EQ(tree->toString(), "6,8,9,18,21,22,43");
}

TEST(AvlTreeNodeTest,
     do_left_right_rotation_and_keeping_left_right_node_safe_1) {
  auto tree = std::make_shared<AvlTree<int>>();

  tree->insert(30);
  tree->insert(15);
  tree->insert(40);
  tree->insert(10);
  tree->insert(18);
  tree->insert(35);
  tree->insert(45);
  tree->insert(5);
  tree->insert(12);

  EXPECT_EQ(tree->toString(), "5,10,12,15,18,30,35,40,45");
  EXPECT_EQ(tree->root_->height(), 3);

  tree->insert(11);

  EXPECT_EQ(tree->toString(), "5,10,11,12,15,18,30,35,40,45");
  EXPECT_EQ(tree->root_->height(), 3);
}

TEST(AvlTreeNodeTest,
     do_left_right_rotation_and_keeping_left_right_node_safe_2) {
  auto tree = std::make_shared<AvlTree<int>>();

  tree->insert(30);
  tree->insert(15);
  tree->insert(40);
  tree->insert(10);
  tree->insert(18);
  tree->insert(35);
  tree->insert(45);
  tree->insert(42);
  tree->insert(47);

  EXPECT_EQ(tree->toString(), "10,15,18,30,35,40,42,45,47");
  EXPECT_EQ(tree->root_->height(), 3);

  tree->insert(43);

  EXPECT_EQ(tree->toString(), "10,15,18,30,35,40,42,43,45,47");
  EXPECT_EQ(tree->root_->height(), 3);
}

TEST(AvlTreeNodeTest, remove) {
  auto tree = std::make_shared<AvlTree<int>>();

  EXPECT_THROW(tree->remove(1), AvlTree<int>::MethodNotImplementedException);
}
