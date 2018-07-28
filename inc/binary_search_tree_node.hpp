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

#include <memory>
#include "binary_tree_node.hpp"
#include "comparator.hpp"

template <typename T>
class BinarySearchTreeNode : public BinaryTreeNode<T> {
 public:
  explicit BinarySearchTreeNode(
      typename Comparator<T>::compare_func_t compare = nullptr)
      : BinaryTreeNode<T>(),
        compare_(compare),
        value_comparator_(Comparator<T>(compare)) {}

  BinarySearchTreeNode(const T &value,
                       typename Comparator<T>::compare_func_t compare = nullptr)
      : BinaryTreeNode<T>(value),
        compare_(compare),
        value_comparator_(Comparator<T>(compare)) {}

  BinarySearchTreeNode *insert(const T &value) {
    if (!this->valid_) {
      this->setValue(value);
      return this;
    }

    if (this->value_comparator_.lessThan(value, this->value_)) {
      // Insert to the left.
      auto left = this->left_;
      if (left) {
        return std::static_pointer_cast<BinarySearchTreeNode>(left)->insert(
            value);
      }

      auto newNode = std::make_shared<BinarySearchTreeNode>(value, compare_);
      this->setLeft(newNode);

      return newNode.get();
    }

    if (this->value_comparator_.greaterThan(value, this->value_)) {
      // Insert to the right.
      auto right = this->right_;
      if (right) {
        return std::static_pointer_cast<BinarySearchTreeNode>(right)->insert(
            value);
      }

      auto newNode = std::make_shared<BinarySearchTreeNode>(value, compare_);
      this->setRight(newNode);

      return newNode.get();
    }

    return this;
  }

  BinarySearchTreeNode *find(const T &value) {
    // Check the root.
    if (this->value_comparator_.equal(this->value_, value)) {
      return this;
    }

    auto left = this->left_;
    if (this->value_comparator_.lessThan(value, this->value_) && left) {
      // Check left nodes.
      return std::static_pointer_cast<BinarySearchTreeNode>(left)->find(value);
    }

    auto right = this->right_;
    if (this->value_comparator_.greaterThan(value, this->value_) && right) {
      // Check right nodes.
      return std::static_pointer_cast<BinarySearchTreeNode>(right)->find(value);
    }

    return nullptr;
  }

  bool contains(const T &value) { return !!find(value); }

  bool remove(const T &value) {
    auto nodeToRemove = find(value);

    if (!nodeToRemove) {
      throw ItemNotFoundException();
    }

    // const { parent } = nodeToRemove;
    auto parent = nodeToRemove->parent_.lock();

    if (!nodeToRemove->left_ && !nodeToRemove->right_) {
      // Node is a leaf and thus has no children.
      if (parent) {
        // Node has a parent. Just remove the pointer to this node from the
        // parent.
        parent->removeChild(nodeToRemove);
      } else {
        // Node has no parent. Just erase current node value.
        nodeToRemove->valid_ = false;
      }
    } else if (nodeToRemove->left_ && nodeToRemove->right_) {
      // Node has two children.
      // Find the next biggest value (minimum value in the right branch)
      // and replace current value node with that next biggest value.
      auto nextBiggerNode =
          std::static_pointer_cast<BinarySearchTreeNode>(nodeToRemove->right_)
              ->findMin();
      if (!this->node_comparator_.equal(nextBiggerNode,
                                        nodeToRemove->right_.get())) {
        auto value = nextBiggerNode->value_;
        remove(value);
        nodeToRemove->setValue(value);
      } else {
        // In case if next right value is the next bigger one and it doesn't
        // have left child then just replace node that is going to be deleted
        // with the right node.
        nodeToRemove->setValue(nodeToRemove->right_->value_);
        nodeToRemove->setRight(nodeToRemove->right_->right_);
      }
    } else {
      // Node has only one child.
      // Make this child to be a direct child of current node's parent.
      /** @var BinarySearchTreeNode */
      auto childNode =
          nodeToRemove->left_ ? nodeToRemove->left_ : nodeToRemove->right_;

      if (parent) {
        parent->replaceChild(nodeToRemove, childNode);
      } else {
        BinaryTreeNode<T>::copyNode(*childNode, nodeToRemove);
      }
    }

    // Clear the parent of removed node.
    // nodeToRemove->parent_.reset();

    return true;
  }

  BinarySearchTreeNode *findMin() {
    if (!this->left_) {
      return this;
    }

    return std::static_pointer_cast<BinarySearchTreeNode>(this->left_)
        ->findMin();
  }

 public:
  typename Comparator<T>::compare_func_t compare_;
  Comparator<T> value_comparator_;

 public:
  class ItemNotFoundException : public std::exception {};
};
