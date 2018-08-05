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

#include "red_black_tree.hpp"
#include "gtest/gtest.h"

TEST(RedBlackTreeTest, color_first_node_black) {
  auto tree = RedBlackTree<int>();

  auto& firstInsertedNode = tree.insert(10);

  EXPECT_TRUE(tree.isNodeColored(firstInsertedNode));
  EXPECT_TRUE(tree.isNodeBlack(firstInsertedNode));
  EXPECT_FALSE(tree.isNodeRed(firstInsertedNode));

  EXPECT_EQ(tree.toString(), "10");
  EXPECT_EQ(tree.root_->height(), 0);
}

TEST(RedBlackTreeTest, color_new_leaf_red) {
  auto tree = RedBlackTree<int>();

  auto& firstInsertedNode = tree.insert(10);
  auto& secondInsertedNode = tree.insert(15);
  auto& thirdInsertedNode = tree.insert(5);

  EXPECT_TRUE(tree.isNodeBlack(firstInsertedNode));
  EXPECT_TRUE(tree.isNodeRed(secondInsertedNode));
  EXPECT_TRUE(tree.isNodeRed(thirdInsertedNode));

  EXPECT_EQ(tree.toString(), "5,10,15");
  EXPECT_EQ(tree.root_->height(), 1);
}

TEST(RedBlackTreeTest, balance) {
  auto tree = RedBlackTree<int>();

  tree.insert(5);
  tree.insert(10);
  tree.insert(15);
  tree.insert(20);
  tree.insert(25);
  tree.insert(30);

  EXPECT_EQ(tree.toString(), "5,10,15,20,25,30");
  EXPECT_EQ(tree.root_->height(), 3);
}

TEST(RedBlackTreeTest, balance_when_parent_is_black) {
  auto tree = RedBlackTree<int>();

  auto& node1 = tree.insert(10);

  EXPECT_TRUE(tree.isNodeBlack(node1));

  auto& node2 = tree.insert(-10);

  EXPECT_TRUE(tree.isNodeBlack(node1));
  EXPECT_TRUE(tree.isNodeRed(node2));

  auto& node3 = tree.insert(20);

  EXPECT_TRUE(tree.isNodeBlack(node1));
  EXPECT_TRUE(tree.isNodeRed(node2));
  EXPECT_TRUE(tree.isNodeRed(node3));

  auto& node4 = tree.insert(-20);

  EXPECT_TRUE(tree.isNodeBlack(node1));
  EXPECT_TRUE(tree.isNodeBlack(node2));
  EXPECT_TRUE(tree.isNodeBlack(node3));
  EXPECT_TRUE(tree.isNodeRed(node4));

  auto& node5 = tree.insert(25);

  EXPECT_TRUE(tree.isNodeBlack(node1));
  EXPECT_TRUE(tree.isNodeBlack(node2));
  EXPECT_TRUE(tree.isNodeBlack(node3));
  EXPECT_TRUE(tree.isNodeRed(node4));
  EXPECT_TRUE(tree.isNodeRed(node5));

  auto& node6 = tree.insert(6);

  EXPECT_TRUE(tree.isNodeBlack(node1));
  EXPECT_TRUE(tree.isNodeBlack(node2));
  EXPECT_TRUE(tree.isNodeBlack(node3));
  EXPECT_TRUE(tree.isNodeRed(node4));
  EXPECT_TRUE(tree.isNodeRed(node5));
  EXPECT_TRUE(tree.isNodeRed(node6));

  EXPECT_EQ(tree.toString(), "-20,-10,6,10,20,25");
  EXPECT_EQ(tree.root_->height(), 2);

  auto& node7 = tree.insert(4);

  EXPECT_EQ(tree.root_->left_->value_, node2.value_);

  EXPECT_EQ(tree.toString(), "-20,-10,4,6,10,20,25");
  EXPECT_EQ(tree.root_->height(), 3);

  EXPECT_TRUE(tree.isNodeBlack(node1));
  EXPECT_TRUE(tree.isNodeRed(node2));
  EXPECT_TRUE(tree.isNodeBlack(node3));
  EXPECT_TRUE(tree.isNodeBlack(node4));
  EXPECT_TRUE(tree.isNodeBlack(node4));
  EXPECT_TRUE(tree.isNodeRed(node5));
  EXPECT_TRUE(tree.isNodeBlack(node6));
  EXPECT_TRUE(tree.isNodeRed(node7));
}

TEST(RedBlackTreeTest, balance_when_uncle_is_black) {
  auto tree = RedBlackTree<int>();

  auto& node1 = tree.insert(10);
  auto& node2 = tree.insert(-10);
  auto& node3 = tree.insert(20);
  auto& node4 = tree.insert(-20);
  auto& node5 = tree.insert(6);
  auto& node6 = tree.insert(15);
  auto& node7 = tree.insert(25);
  auto& node8 = tree.insert(2);
  auto& node9 = tree.insert(8);

  EXPECT_EQ(tree.toString(), "-20,-10,2,6,8,10,15,20,25");
  EXPECT_EQ(tree.root_->height(), 3);

  EXPECT_TRUE(tree.isNodeBlack(node1));
  EXPECT_TRUE(tree.isNodeRed(node2));
  EXPECT_TRUE(tree.isNodeBlack(node3));
  EXPECT_TRUE(tree.isNodeBlack(node4));
  EXPECT_TRUE(tree.isNodeBlack(node5));
  EXPECT_TRUE(tree.isNodeRed(node6));
  EXPECT_TRUE(tree.isNodeRed(node7));
  EXPECT_TRUE(tree.isNodeRed(node8));
  EXPECT_TRUE(tree.isNodeRed(node9));

  auto& node10 = tree.insert(4);

  EXPECT_EQ(tree.toString(), "-20,-10,2,4,6,8,10,15,20,25");
  EXPECT_EQ(tree.root_->height(), 3);

  EXPECT_EQ(tree.root_->value_, node5.value_);

  EXPECT_TRUE(tree.isNodeBlack(node5));
  EXPECT_TRUE(tree.isNodeRed(node1));
  EXPECT_TRUE(tree.isNodeRed(node2));
  EXPECT_TRUE(tree.isNodeRed(node10));
  EXPECT_TRUE(tree.isNodeRed(node6));
  EXPECT_TRUE(tree.isNodeRed(node7));
  EXPECT_TRUE(tree.isNodeBlack(node4));
  EXPECT_TRUE(tree.isNodeBlack(node8));
  EXPECT_TRUE(tree.isNodeBlack(node9));
  EXPECT_TRUE(tree.isNodeBlack(node3));
}
