#include "binary_search_tree_node.hpp"
#include "gtest/gtest.h"

TEST(BinarySearchTreeNodeTest, create) {
  auto bstNode = std::make_shared<BinarySearchTreeNode<int>>(2);

  EXPECT_EQ(bstNode->value_, 2);
  EXPECT_EQ(bstNode->left_, nullptr);
  EXPECT_EQ(bstNode->right_, nullptr);
}

TEST(BinarySearchTreeNodeTest, insert_empty) {
  auto bstNode = std::make_shared<BinarySearchTreeNode<int>>();
  bstNode->insert(1);

  EXPECT_EQ(bstNode->value_, 1);
  EXPECT_EQ(bstNode->left_, nullptr);
  EXPECT_EQ(bstNode->right_, nullptr);
}

TEST(BinarySearchTreeNodeTest, insert_nodes) {
  auto bstNode = std::make_shared<BinarySearchTreeNode<int>>(2);
  auto insertedNode1 = bstNode->insert(1);

  EXPECT_EQ(insertedNode1->value_, 1);
  EXPECT_EQ(bstNode->toString(), "1,2");
  EXPECT_TRUE(bstNode->contains(1));
  EXPECT_FALSE(bstNode->contains(3));

  auto insertedNode2 = bstNode->insert(3);

  EXPECT_EQ(insertedNode2->value_, 3);
  EXPECT_EQ(bstNode->toString(), "1,2,3");
  EXPECT_TRUE(bstNode->contains(3));
  EXPECT_FALSE(bstNode->contains(4));

  bstNode->insert(7);

  EXPECT_EQ(bstNode->toString(), "1,2,3,7");
  EXPECT_TRUE(bstNode->contains(7));
  EXPECT_FALSE(bstNode->contains(8));

  bstNode->insert(4);

  EXPECT_EQ(bstNode->toString(), "1,2,3,4,7");
  EXPECT_TRUE(bstNode->contains(4));
  EXPECT_FALSE(bstNode->contains(8));

  bstNode->insert(6);

  EXPECT_EQ(bstNode->toString(), "1,2,3,4,6,7");
  EXPECT_TRUE(bstNode->contains(6));
  EXPECT_FALSE(bstNode->contains(8));
}

TEST(BinarySearchTreeNodeTest, insert_duplicates) {
  auto bstNode = std::make_shared<BinarySearchTreeNode<int>>(2);
  bstNode->insert(1);

  EXPECT_EQ(bstNode->toString(), "1,2");
  EXPECT_TRUE(bstNode->contains(1));
  EXPECT_FALSE(bstNode->contains(3));

  bstNode->insert(1);

  EXPECT_EQ(bstNode->toString(), "1,2");
  EXPECT_TRUE(bstNode->contains(1));
  EXPECT_FALSE(bstNode->contains(3));
}

TEST(BinarySearchTreeNodeTest, find_min) {
  auto bstNode = std::make_shared<BinarySearchTreeNode<int>>(10);

  bstNode->insert(20);
  bstNode->insert(30);
  bstNode->insert(5);
  bstNode->insert(40);
  bstNode->insert(1);

  EXPECT_NE(bstNode->findMin(), nullptr);
  EXPECT_EQ(bstNode->findMin()->value_, 1);
}

TEST(BinarySearchTreeNodeTest, meta_info) {
  auto node = std::make_shared<BinarySearchTreeNode<int>>(10);

  node->insert(20);
  auto node1 = node->insert(30);
  node->insert(5);
  node->insert(40);
  auto node2 = node->insert(1);

  node->meta_.set("color", "red");
  node1->meta_.set("color", "black");
  node2->meta_.set("color", "white");

  EXPECT_EQ(*node->meta_.get("color"), "red");

  EXPECT_NE(node->findMin(), nullptr);
  EXPECT_EQ(node->findMin()->value_, 1);
  EXPECT_EQ(*node->findMin()->meta_.get("color"), "white");
  EXPECT_EQ(*node->find(30)->meta_.get("color"), "black");
}

TEST(BinarySearchTreeNodeTest, find) {
  auto node = std::make_shared<BinarySearchTreeNode<int>>(10);

  node->insert(20);
  node->insert(30);
  node->insert(5);
  node->insert(40);
  node->insert(1);

  EXPECT_EQ(node->find(6), nullptr);
  EXPECT_NE(node->find(5), nullptr);
  EXPECT_EQ(node->find(5)->value_, 5);
}

TEST(BinarySearchTreeNodeTest, remove_leaf) {
  auto bstRootNode = std::make_shared<BinarySearchTreeNode<int>>();

  bstRootNode->insert(10);
  bstRootNode->insert(20);
  bstRootNode->insert(5);

  EXPECT_EQ(bstRootNode->toString(), "5,10,20");

  auto removed1 = bstRootNode->remove(5);
  EXPECT_EQ(bstRootNode->toString(), "10,20");
  EXPECT_TRUE(removed1);

  auto removed2 = bstRootNode->remove(20);
  EXPECT_EQ(bstRootNode->toString(), "10");
  EXPECT_TRUE(removed2);
}

TEST(BinarySearchTreeNodeTest, remove_one_child) {
  auto bstRootNode = std::make_shared<BinarySearchTreeNode<int>>();

  bstRootNode->insert(10);
  bstRootNode->insert(20);
  bstRootNode->insert(5);
  bstRootNode->insert(30);

  EXPECT_EQ(bstRootNode->toString(), "5,10,20,30");

  bstRootNode->remove(20);
  EXPECT_EQ(bstRootNode->toString(), "5,10,30");

  bstRootNode->insert(1);
  EXPECT_EQ(bstRootNode->toString(), "1,5,10,30");

  bstRootNode->remove(5);
  EXPECT_EQ(bstRootNode->toString(), "1,10,30");
}

TEST(BinarySearchTreeNodeTest, remove_two_children) {
  auto bstRootNode = std::make_shared<BinarySearchTreeNode<int>>();

  bstRootNode->insert(10);
  bstRootNode->insert(20);
  bstRootNode->insert(5);
  bstRootNode->insert(30);
  bstRootNode->insert(15);
  bstRootNode->insert(25);

  EXPECT_EQ(bstRootNode->toString(), "5,10,15,20,25,30");
  EXPECT_EQ(bstRootNode->find(20)->left_->value_, 15);
  EXPECT_EQ(bstRootNode->find(20)->right_->value_, 30);

  bstRootNode->remove(20);
  EXPECT_EQ(bstRootNode->toString(), "5,10,15,25,30");

  bstRootNode->remove(15);
  EXPECT_EQ(bstRootNode->toString(), "5,10,25,30");

  bstRootNode->remove(10);
  EXPECT_EQ(bstRootNode->toString(), "5,25,30");
  EXPECT_EQ(bstRootNode->value_, 25);

  bstRootNode->remove(25);
  EXPECT_EQ(bstRootNode->toString(), "5,30");

  bstRootNode->remove(5);
  EXPECT_EQ(bstRootNode->toString(), "30");
}

TEST(BinarySearchTreeNodeTest, remove_no_parent) {
  auto bstRootNode = std::make_shared<BinarySearchTreeNode<int>>();
  EXPECT_EQ(bstRootNode->toString(), "");

  bstRootNode->insert(1);
  bstRootNode->insert(2);
  EXPECT_EQ(bstRootNode->toString(), "1,2");

  bstRootNode->remove(1);
  EXPECT_EQ(bstRootNode->toString(), "2");

  bstRootNode->remove(2);
  EXPECT_EQ(bstRootNode->toString(), "");
}

TEST(BinarySearchTreeNodeTest, remove_not_exist) {
  auto bstRootNode = std::make_shared<BinarySearchTreeNode<int>>();

  bstRootNode->insert(10);
  bstRootNode->insert(20);

  EXPECT_THROW(bstRootNode->remove(30),
               BinarySearchTreeNode<int>::ItemNotFoundException);
}

namespace BinarySearchTreeNodeTest {
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
}  // namespace BinarySearchTreeNodeTest

TEST(BinarySearchTreeNodeTest, object_as_node_values) {
  using BinarySearchTreeNodeTest::Obj;

  Obj obj1({"obj1", 1});
  Obj obj2({"obj2", 2});
  Obj obj3({"obj3", 3});

  auto bstNode = std::make_shared<BinarySearchTreeNode<Obj>>(
      obj2, [](const Obj &a, const Obj &b) {
        if (a.key_ == b.key_) {
          return 0;
        }

        return a.value_ < b.value_ ? -1 : 1;
      });

  bstNode->insert(obj1);

  EXPECT_EQ(bstNode->toString(), "obj1,obj2");
  EXPECT_TRUE(bstNode->contains(obj1));
  EXPECT_FALSE(bstNode->contains(obj3));

  bstNode->insert(obj3);

  EXPECT_EQ(bstNode->toString(), "obj1,obj2,obj3");
  EXPECT_TRUE(bstNode->contains(obj3));

  EXPECT_EQ(bstNode->findMin()->value_, obj1);
}

TEST(BinarySearchTreeNodeTest, abandon_removed_node) {
  auto rootNode =
      std::make_shared<BinarySearchTreeNode<std::string>>(std::string("foo"));
  rootNode->insert("bar");
  auto childNode = rootNode->find("bar");
  rootNode->remove("bar");

  // EXPECT_EQ(childNode->parent_.lock(), nullptr);
}
