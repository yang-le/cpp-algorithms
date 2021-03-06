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

#pragma once

#include <algorithm>
#include <memory>
#include <string>
#include <vector>
#include "hash_table.hpp"

template <typename T>
class BinaryTreeNode : public std::enable_shared_from_this<BinaryTreeNode<T>> {
 public:
  BinaryTreeNode()
      : left_(nullptr),
        right_(nullptr),
        parent_(),
        valid_(false),
        node_comparator_(Comparator<const BinaryTreeNode *>()) {}

  explicit BinaryTreeNode(const T &value)
      : left_(nullptr),
        right_(nullptr),
        parent_(),
        value_(value),
        valid_(true),
        node_comparator_(Comparator<const BinaryTreeNode *>()) {}

  int leftHeight() const {
    auto left = left_;
    return left ? left->height() + 1 : 0;
  }

  int rightHeight() const {
    auto right = right_;
    return right ? right->height() + 1 : 0;
  }

  int height() const { return std::max(leftHeight(), rightHeight()); }

  int balanceFactor() const { return leftHeight() - rightHeight(); }

  std::shared_ptr<BinaryTreeNode> uncle() const {
    // Check if current node has parent.
    auto parent = parent_.lock();
    if (!parent) {
      return nullptr;
    }

    // Check if current node has grand-parent.
    auto grad_parent = parent->parent_.lock();
    if (!grad_parent) {
      return nullptr;
    }

    // Check if grand-parent has two children.
    if (!grad_parent->left_ || !grad_parent->right_) {
      return nullptr;
    }

    // So for now we know that current node has grand-parent and this
    // grand-parent has two children. Let's find out who is the uncle.
    if (node_comparator_.equal(parent.get(), grad_parent->left_.get())) {
      // Right one is an uncle.
      return grad_parent->right_;
    }

    // Left one is an uncle.
    return grad_parent->left_;
  }

  BinaryTreeNode &setValue(const T &value) {
    value_ = value;
    valid_ = true;

    return *this;
  }

  BinaryTreeNode &setLeft(std::shared_ptr<BinaryTreeNode> node) {
    // Reset parent for left node since it is going to be detached.
    if (left_) {
      left_->parent_.reset();
    }

    // Attach new node to the left.
    left_ = node;

    // Make current node to be a parent for new left one.
    if (left_) {
      left_->parent_ = this->shared_from_this();
    }

    return *this;
  }

  BinaryTreeNode &setRight(std::shared_ptr<BinaryTreeNode> node) {
    // Reset parent for right node since it is going to be detached.
    if (right_) {
      right_->parent_.reset();
    }

    // Attach new node to the right.
    right_ = node;

    // Make current node to be a parent for new right one.
    if (right_) {
      right_->parent_ = this->shared_from_this();
    }

    return *this;
  }

  bool removeChild(BinaryTreeNode *nodeToRemove) {
    if (left_ && node_comparator_.equal(left_.get(), nodeToRemove)) {
      left_.reset();
      return true;
    }

    if (right_ && node_comparator_.equal(right_.get(), nodeToRemove)) {
      right_.reset();
      return true;
    }

    return false;
  }

  bool replaceChild(BinaryTreeNode *nodeToReplace,
                    std::shared_ptr<BinaryTreeNode> replacementNode) {
    if (!nodeToReplace || !replacementNode) {
      return false;
    }

    if (left_ && node_comparator_.equal(left_.get(), nodeToReplace)) {
      left_ = replacementNode;
      return true;
    }

    if (right_ && node_comparator_.equal(right_.get(), nodeToReplace)) {
      right_ = replacementNode;
      return true;
    }

    return false;
  }

  static void copyNode(const BinaryTreeNode &sourceNode,
                       BinaryTreeNode *targetNode) {
    targetNode->setValue(sourceNode.value_);
    targetNode->setLeft(sourceNode.left_);
    targetNode->setRight(sourceNode.right_);
  }

  std::vector<T> traverseInOrder() const {
    std::vector<T> traverse;

    // Add left node.
    if (left_) {
      for (auto elem : left_->traverseInOrder()) {
        traverse.push_back(elem);
      }
    }

    // Add root.
    if (valid_) {
      traverse.push_back(value_);
    }

    // Add right node.
    if (right_) {
      for (auto elem : right_->traverseInOrder()) {
        traverse.push_back(elem);
      }
    }

    return traverse;
  }

  std::string toString() const {
    std::vector<T> nodes = traverseInOrder();
    std::string ret = std::accumulate(nodes.begin(), nodes.end(), std::string(),
                                      [](const std::string &a, const T &b) {
                                        std::stringstream ss;
                                        ss << a << "," << b;
                                        return ss.str();
                                      });

    return ret.length() ? ret.substr(1) : ret;
  }

 public:
  bool operator==(const BinaryTreeNode &rhs) const {
    return rhs.value_ == value_;
  }
  bool operator<(const BinaryTreeNode &rhs) const {
    return rhs.value_ < value_;
  }

 public:
  std::shared_ptr<BinaryTreeNode> left_;
  std::shared_ptr<BinaryTreeNode> right_;
  std::weak_ptr<BinaryTreeNode> parent_;
  T value_;
  bool valid_;
  Comparator<const BinaryTreeNode *> node_comparator_;
  HashTable<std::string> meta_;
};
