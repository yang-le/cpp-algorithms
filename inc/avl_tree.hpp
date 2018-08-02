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
#include "binary_search_tree.hpp"

template <typename T>
class AvlTree : public BinarySearchTree<T> {
 public:
  BinarySearchTreeNode<T>& insert(const T& value) {
    auto& result = BinarySearchTree<T>::insert(value);

    auto currentNode = std::static_pointer_cast<BinarySearchTreeNode<T>>(
        result.shared_from_this());

    while (currentNode) {
      balance(currentNode);

      currentNode = std::static_pointer_cast<BinarySearchTreeNode<T>>(
          currentNode->parent_.lock());
    }

    return result;
  }

  bool remove(const T& value) { throw MethodNotImplementedException(); }

 private:
  void balance(std::shared_ptr<BinarySearchTreeNode<T>> node) {
    // If balance factor is not OK then try to balance the node->
    if (node->balanceFactor() > 1) {
      // Left rotation.
      if (node->left_->balanceFactor() > 0) {
        // Left-Left rotation
        rotateLeftLeft(node);
      } else if (node->left_->balanceFactor() < 0) {
        // Left-Right rotation.
        rotateLeftRight(node);
      }
    } else if (node->balanceFactor() < -1) {
      // Right rotation.
      if (node->right_->balanceFactor() < 0) {
        // Right-Right rotation
        rotateRightRight(node);
      } else if (node->right_->balanceFactor() > 0) {
        // Right-Left rotation.
        rotateRightLeft(node);
      }
    }
  }

  void rotateLeftLeft(std::shared_ptr<BinarySearchTreeNode<T>> rootNode) {
    // Detach left node from root node
    auto leftNode = rootNode->left_;
    rootNode->setLeft(nullptr);

    // Make left node to be a child of rootNode's parent.
    auto parent = rootNode->parent_.lock();
    if (parent) {
      parent->setLeft(leftNode);
    } else if (rootNode == this->root_) {
      // If root node is root then make left node to be a new root.
      this->root_ = std::static_pointer_cast<BinarySearchTreeNode<T>>(leftNode);
    }

    // If left node has a right child then detach it and
    // attach it as a left child for rootNode
    if (leftNode->right_) {
      rootNode->setLeft(leftNode->right_);
    }

    // Attach rootNode to the right of leftNode
    leftNode->setRight(rootNode);
  }

  void rotateLeftRight(std::shared_ptr<BinarySearchTreeNode<T>> rootNode) {
    // Detach left node from rootNode since it is going to be replaced.
    auto leftNode = rootNode->left_;
    rootNode->setLeft(nullptr);

    // Detach right node from leftNode
    auto leftRightNode = leftNode->right_;
    leftNode->setRight(nullptr);

    // Preserve leftRightNode's left subtree.
    if (leftRightNode->left_) {
      leftNode->setRight(leftRightNode->left_);
      leftRightNode->setLeft(nullptr);
    }

    // Attach leftRightNode to the rootNode
    rootNode->setLeft(leftRightNode);

    // Attach leftNode as left node for leftRight node
    leftRightNode->setLeft(leftNode);

    // Do left-left rotation.
    rotateLeftLeft(rootNode);
  }

  void rotateRightLeft(std::shared_ptr<BinarySearchTreeNode<T>> rootNode) {
    // Detach right node from rootNode since it is going to be replaced.
    auto rightNode = rootNode->right_;
    rootNode->setRight(nullptr);

    // Detach left node from rightNode
    auto rightLeftNode = rightNode->left_;
    rightNode->setLeft(nullptr);

    if (rightLeftNode->right_) {
      rightNode->setLeft(rightLeftNode->right_);
      rightLeftNode->setRight(nullptr);
    }

    // Attach rightLeftNode to the rootNode
    rootNode->setRight(rightLeftNode);

    // Attach rightNode as right node for rightLeft node
    rightLeftNode->setRight(rightNode);

    // Do right-right rotation.
    rotateRightRight(rootNode);
  }

  void rotateRightRight(std::shared_ptr<BinarySearchTreeNode<T>> rootNode) {
    // Detach right node from root node
    auto rightNode = rootNode->right_;
    rootNode->setRight(nullptr);

    // Make right node to be a child of rootNode's parent.
    auto parent = rootNode->parent_.lock();
    if (parent) {
      parent->setRight(rightNode);
    } else if (rootNode == this->root_) {
      // If root node is root then make right node to be a new root.
      this->root_ =
          std::static_pointer_cast<BinarySearchTreeNode<T>>(rightNode);
    }

    // If right node has a left child then detach it and
    // attach it as a right child for rootNode
    if (rightNode->left_) {
      rootNode->setRight(rightNode->left_);
    }

    // Attach rootNode to the left of rightNode
    rightNode->setLeft(rootNode);
  }

 public:
  class MethodNotImplementedException : public std::exception {};
};
