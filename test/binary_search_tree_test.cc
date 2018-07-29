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

#include "binary_search_tree.hpp"
#include "gtest/gtest.h"

TEST(BinarySearchTreeTest, create) {
  auto bst = std::make_shared<BinarySearchTree<int>>();

  EXPECT_NE(bst, nullptr);
  EXPECT_NE(bst->root_, nullptr);
  EXPECT_EQ(bst->root_->left_, nullptr);
  EXPECT_EQ(bst->root_->right_, nullptr);
}

TEST(BinarySearchTreeTest, insert) {
  auto bst = std::make_shared<BinarySearchTree<int>>();

  auto insertedNode1 = bst->insert(10);
  auto insertedNode2 = bst->insert(20);
  bst->insert(5);

  EXPECT_EQ(bst->toString(), "5,10,20");
  EXPECT_EQ(insertedNode1->value_, 10);
  EXPECT_EQ(insertedNode2->value_, 20);
}

TEST(BinarySearchTreeTest, contains) {
  auto bst = std::make_shared<BinarySearchTree<int>>();

  bst->insert(10);
  bst->insert(20);
  bst->insert(5);

  EXPECT_TRUE(bst->contains(20));
  EXPECT_FALSE(bst->contains(40));
}

TEST(BinarySearchTreeTest, remove) {
  auto bst = std::make_shared<BinarySearchTree<int>>();

  bst->insert(10);
  bst->insert(20);
  bst->insert(5);

  EXPECT_EQ(bst->toString(), "5,10,20");

  auto removed1 = bst->remove(5);
  EXPECT_EQ(bst->toString(), "10,20");
  EXPECT_TRUE(removed1);

  auto removed2 = bst->remove(20);
  EXPECT_EQ(bst->toString(), "10");
  EXPECT_TRUE(removed2);
}

namespace BinarySearchTreeTest {
struct Obj {
  friend std::ostream &operator<<(std::ostream &out, const Obj &obj) {
    out << obj.key_;
    return out;
  }

  bool operator==(const Obj &rhs) const {
    return (key_ == rhs.key_) && (value_ == rhs.value_);
  }

  bool operator<(const Obj &rhs) const { return value_ < rhs.value_; }

  std::string key_;
  int value_;
};
}  // namespace BinarySearchTreeTest

TEST(BinarySearchTreeTest, insert_object) {
  using BinarySearchTreeTest::Obj;

  Obj obj1({"obj1", 1});
  Obj obj2({"obj2", 2});
  Obj obj3({"obj3", 3});

  auto bst =
      std::make_shared<BinarySearchTree<Obj>>([](const Obj &a, const Obj &b) {
        if (a.key_ == b.key_) {
          return 0;
        }

        return a.value_ < b.value_ ? -1 : 1;
      });

  bst->insert(obj2);
  bst->insert(obj3);
  bst->insert(obj1);

  EXPECT_EQ(bst->toString(), "obj1,obj2,obj3");
}

TEST(BinarySearchTreeTest, traversed_to_sorted_array) {
  auto bst = std::make_shared<BinarySearchTree<int>>();

  bst->insert(10);
  bst->insert(-10);
  bst->insert(20);
  bst->insert(-20);
  bst->insert(25);
  bst->insert(6);

  EXPECT_EQ(bst->toString(), "-20,-10,6,10,20,25");
  EXPECT_EQ(bst->root_->height(), 2);

  bst->insert(4);

  EXPECT_EQ(bst->toString(), "-20,-10,4,6,10,20,25");
  EXPECT_EQ(bst->root_->height(), 3);
}
