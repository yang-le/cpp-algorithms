#include "binary_tree_node.hpp"
#include "gtest/gtest.h"

TEST(BinaryTreeNodeTest, create) {
  auto node = std::make_shared<BinaryTreeNode<int>>();

  EXPECT_FALSE(node->valid_);
  EXPECT_EQ(node->left_, nullptr);
  EXPECT_EQ(node->right_, nullptr);

  auto leftNode = std::make_shared<BinaryTreeNode<int>>(1);
  auto rightNode = std::make_shared<BinaryTreeNode<int>>(3);
  auto rootNode = std::make_shared<BinaryTreeNode<int>>(2);

  rootNode->setLeft(leftNode)->setRight(rightNode);

  EXPECT_EQ(rootNode->value_, 2);
  EXPECT_EQ(rootNode->left_->value_, 1);
  EXPECT_EQ(rootNode->right_->value_, 3);
}

TEST(BinaryTreeNodeTest, set_parent) {
  auto leftNode = std::make_shared<BinaryTreeNode<int>>(1);
  auto rightNode = std::make_shared<BinaryTreeNode<int>>(3);
  auto rootNode = std::make_shared<BinaryTreeNode<int>>(2);

  rootNode->setLeft(leftNode)->setRight(rightNode);

  EXPECT_EQ(rootNode->parent_.lock(), nullptr);
  EXPECT_EQ(rootNode->left_->parent_.lock()->value_, 2);
  EXPECT_EQ(rootNode->right_->parent_.lock()->value_, 2);
  EXPECT_EQ(rootNode->right_->parent_.lock(), rootNode);
}

TEST(BinaryTreeNodeTest, traverse) {
  auto leftNode = std::make_shared<BinaryTreeNode<int>>(1);
  auto rightNode = std::make_shared<BinaryTreeNode<int>>(3);
  auto rootNode = std::make_shared<BinaryTreeNode<int>>(2);

  rootNode->setLeft(leftNode)->setRight(rightNode);

  EXPECT_EQ(rootNode->traverseInOrder(), std::vector<int>({1, 2, 3}));
  EXPECT_EQ(rootNode->toString(), "1,2,3");
}

TEST(BinaryTreeNodeTest, remove_child) {
  auto leftNode = std::make_shared<BinaryTreeNode<int>>(1);
  auto rightNode = std::make_shared<BinaryTreeNode<int>>(3);
  auto rootNode = std::make_shared<BinaryTreeNode<int>>(2);

  rootNode->setLeft(leftNode)->setRight(rightNode);

  EXPECT_EQ(rootNode->traverseInOrder(), std::vector<int>({1, 2, 3}));

  EXPECT_TRUE(rootNode->removeChild(rootNode->left_.get()));
  EXPECT_EQ(rootNode->traverseInOrder(), std::vector<int>({2, 3}));

  EXPECT_TRUE(rootNode->removeChild(rootNode->right_.get()));
  EXPECT_EQ(rootNode->traverseInOrder(), std::vector<int>({2}));

  EXPECT_FALSE(rootNode->removeChild(rootNode->right_.get()));
  EXPECT_EQ(rootNode->traverseInOrder(), std::vector<int>({2}));
}

TEST(BinaryTreeNodeTest, replace_child) {
  auto leftNode = std::make_shared<BinaryTreeNode<int>>(1);
  auto rightNode = std::make_shared<BinaryTreeNode<int>>(3);
  auto rootNode = std::make_shared<BinaryTreeNode<int>>(2);

  rootNode->setLeft(leftNode)->setRight(rightNode);

  EXPECT_EQ(rootNode->traverseInOrder(), std::vector<int>({1, 2, 3}));

  auto replacementNode = std::make_shared<BinaryTreeNode<int>>(5);
  rightNode->setRight(replacementNode);

  EXPECT_EQ(rootNode->traverseInOrder(), std::vector<int>({1, 2, 3, 5}));

  EXPECT_TRUE(
      rootNode->replaceChild(rootNode->right_.get(), rootNode->right_->right_));
  EXPECT_EQ(rootNode->right_->value_, 5);
  EXPECT_EQ(rootNode->right_->right_, nullptr);
  EXPECT_EQ(rootNode->traverseInOrder(), std::vector<int>({1, 2, 5}));

  EXPECT_FALSE(
      rootNode->replaceChild(rootNode->right_.get(), rootNode->right_->right_));
  EXPECT_EQ(rootNode->traverseInOrder(), std::vector<int>({1, 2, 5}));

  EXPECT_TRUE(rootNode->replaceChild(rootNode->right_.get(), replacementNode));
  EXPECT_EQ(rootNode->traverseInOrder(), std::vector<int>({1, 2, 5}));

  EXPECT_TRUE(rootNode->replaceChild(rootNode->left_.get(), replacementNode));
  EXPECT_EQ(rootNode->traverseInOrder(), std::vector<int>({5, 2, 5}));

  EXPECT_FALSE(
      rootNode->replaceChild(std::make_shared<BinaryTreeNode<int>>().get(),
                             std::make_shared<BinaryTreeNode<int>>()));
}

TEST(BinaryTreeNodeTest, height) {
  auto root = std::make_shared<BinaryTreeNode<int>>(1);
  auto left = std::make_shared<BinaryTreeNode<int>>(3);
  auto right = std::make_shared<BinaryTreeNode<int>>(2);
  auto grandLeft = std::make_shared<BinaryTreeNode<int>>(5);
  auto grandRight = std::make_shared<BinaryTreeNode<int>>(6);
  auto grandGrandLeft = std::make_shared<BinaryTreeNode<int>>(7);

  EXPECT_EQ(root->height(), 0);
  EXPECT_EQ(root->balanceFactor(), 0);

  root->setLeft(left)->setRight(right);

  EXPECT_EQ(root->height(), 1);
  EXPECT_EQ(left->height(), 0);
  EXPECT_EQ(root->balanceFactor(), 0);

  left->setLeft(grandLeft)->setRight(grandRight);

  EXPECT_EQ(root->height(), 2);
  EXPECT_EQ(left->height(), 1);
  EXPECT_EQ(grandLeft->height(), 0);
  EXPECT_EQ(grandRight->height(), 0);
  EXPECT_EQ(root->balanceFactor(), 1);

  grandLeft->setLeft(grandGrandLeft);

  EXPECT_EQ(root->height(), 3);
  EXPECT_EQ(left->height(), 2);
  EXPECT_EQ(grandLeft->height(), 1);
  EXPECT_EQ(grandRight->height(), 0);
  EXPECT_EQ(grandGrandLeft->height(), 0);
  EXPECT_EQ(root->balanceFactor(), 2);
}

TEST(BinaryTreeNodeTest, height_from_right) {
  auto root = std::make_shared<BinaryTreeNode<int>>(1);
  auto right = std::make_shared<BinaryTreeNode<int>>(2);

  root->setRight(right);

  EXPECT_EQ(root->height(), 1);
  EXPECT_EQ(right->height(), 0);
  EXPECT_EQ(root->balanceFactor(), -1);
}

TEST(BinaryTreeNodeTest, null_node) {
  auto leftNode = std::make_shared<BinaryTreeNode<int>>(1);
  auto rightNode = std::make_shared<BinaryTreeNode<int>>(3);
  auto root = std::make_shared<BinaryTreeNode<int>>(2);

  root->setLeft(leftNode)->setRight(rightNode);

  EXPECT_EQ(root->left_->value_, 1);
  EXPECT_EQ(root->right_->value_, 3);

  root->setLeft(nullptr);
  root->setRight(nullptr);

  EXPECT_EQ(root->left_, nullptr);
  EXPECT_EQ(root->right_, nullptr);
}

namespace BinaryTreeNodeTest {
struct Obj {
  friend std::ostream& operator<<(std::ostream& out, const Obj& obj) {
    out << obj.key;
    return out;
  }

  bool operator==(const Obj& rhs) const { return key == rhs.key; }

  bool operator<(const Obj& rhs) const { return key < rhs.key; }

  std::string key;
};
}  // namespace BinaryTreeNodeTest

TEST(BinaryTreeNodeTest, create_with_object) {
  using BinaryTreeNodeTest::Obj;

  Obj obj1 = {"object_1"};
  Obj obj2 = {"object_2"};

  auto node1 = std::make_shared<BinaryTreeNode<Obj>>(obj1);
  auto node2 = std::make_shared<BinaryTreeNode<Obj>>(obj2);

  node1->setLeft(node2);

  EXPECT_EQ(node1->value_, obj1);
  EXPECT_EQ(node2->value_, obj2);
  EXPECT_EQ(node1->left_->value_, obj2);

  node1->removeChild(node1->left_.get());

  EXPECT_EQ(node1->value_, obj1);
  EXPECT_EQ(node2->value_, obj2);
  EXPECT_EQ(node1->left_, nullptr);

  EXPECT_EQ(node1->toString(), "object_1");
  EXPECT_EQ(node2->toString(), "object_2");
}

TEST(BinaryTreeNodeTest, attach_meta_information) {
  auto redNode = std::make_shared<BinaryTreeNode<int>>(1);
  auto blackNode = std::make_shared<BinaryTreeNode<int>>(2);

  redNode->meta_.set("color", "red");
  blackNode->meta_.set("color", "black");

  EXPECT_EQ(*redNode->meta_.get("color"), "red");
  EXPECT_EQ(*blackNode->meta_.get("color"), "black");
}

TEST(BinaryTreeNodeTest, right_uncle) {
  auto grandParent =
      std::make_shared<BinaryTreeNode<std::string>>("grand-parent");
  auto parent = std::make_shared<BinaryTreeNode<std::string>>("parent");
  auto uncle = std::make_shared<BinaryTreeNode<std::string>>("uncle");
  auto child = std::make_shared<BinaryTreeNode<std::string>>("child");

  EXPECT_EQ(grandParent->uncle(), nullptr);
  EXPECT_EQ(parent->uncle(), nullptr);

  grandParent->setLeft(parent);

  EXPECT_EQ(parent->uncle(), nullptr);
  EXPECT_EQ(child->uncle(), nullptr);

  parent->setLeft(child);

  EXPECT_EQ(child->uncle(), nullptr);

  grandParent->setRight(uncle);

  EXPECT_EQ(parent->uncle(), nullptr);
  EXPECT_NE(child->uncle(), nullptr);
  EXPECT_EQ(child->uncle(), uncle);
}

TEST(BinaryTreeNodeTest, left_uncle) {
  auto grandParent =
      std::make_shared<BinaryTreeNode<std::string>>("grand-parent");
  auto parent = std::make_shared<BinaryTreeNode<std::string>>("parent");
  auto uncle = std::make_shared<BinaryTreeNode<std::string>>("uncle");
  auto child = std::make_shared<BinaryTreeNode<std::string>>("child");

  EXPECT_EQ(grandParent->uncle(), nullptr);
  EXPECT_EQ(parent->uncle(), nullptr);

  grandParent->setRight(parent);

  EXPECT_EQ(parent->uncle(), nullptr);
  EXPECT_EQ(child->uncle(), nullptr);

  parent->setRight(child);

  EXPECT_EQ(child->uncle(), nullptr);

  grandParent->setLeft(uncle);

  EXPECT_EQ(parent->uncle(), nullptr);
  EXPECT_NE(child->uncle(), nullptr);
  EXPECT_EQ(child->uncle(), uncle);
}

TEST(BinaryTreeNodeTest, set_value) {
  BinaryTreeNode<std::string> node("initial_value");

  EXPECT_EQ(node.value_, "initial_value");

  node.setValue("new_value");

  EXPECT_EQ(node.value_, "new_value");
}

TEST(BinaryTreeNodeTest, copy_node) {
  auto root = std::make_shared<BinaryTreeNode<std::string>>("root");
  auto left = std::make_shared<BinaryTreeNode<std::string>>("left");
  auto right = std::make_shared<BinaryTreeNode<std::string>>("right");

  root->setLeft(left)->setRight(right);

  EXPECT_EQ(root->toString(), "left,root,right");

  auto newRoot = std::make_shared<BinaryTreeNode<std::string>>("new_root");
  auto newLeft = std::make_shared<BinaryTreeNode<std::string>>("new_left");
  auto newRight = std::make_shared<BinaryTreeNode<std::string>>("new_right");

  newRoot->setLeft(newLeft)->setRight(newRight);

  EXPECT_EQ(newRoot->toString(), "new_left,new_root,new_right");

  BinaryTreeNode<std::string>::copyNode(*root, *newRoot);

  EXPECT_EQ(root->toString(), "left,root,right");
  EXPECT_EQ(newRoot->toString(), "left,root,right");
}
