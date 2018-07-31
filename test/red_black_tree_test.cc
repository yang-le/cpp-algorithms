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
  auto tree = std::make_shared<RedBlackTree<int>>();

  auto firstInsertedNode = tree->insert(10);

  EXPECT_TRUE(tree->isNodeColored(*firstInsertedNode));
  EXPECT_TRUE(tree->isNodeBlack(*firstInsertedNode));
  EXPECT_FALSE(tree->isNodeRed(*firstInsertedNode));

  EXPECT_EQ(tree->toString(), "10");
  EXPECT_EQ(tree->root_->height(), 0);
}
