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
#include <string>
#include "binary_search_tree.hpp"

template <typename T>
class RedBlackTree : public BinarySearchTree<T> {
 public:
  const std::string RED = "red";
  const std::string BLACK = "black";
  const std::string COLOR = "color";

 public:
  BinaryTreeNode<T>& insert(const T& value) {
    auto& result = BinarySearchTree<T>::insert(value);

    auto insertNode = result.shared_from_this();

    if (insertNode == this->root_) {
      makeNodeBlack(insertNode);
    } else {
      makeNodeRed(insertNode);
    }

    balance(insertNode);

    return result;
  }

  bool remove(const T& value) { throw MethodNotImplementedException(); }

  bool isNodeRed(const BinaryTreeNode<T>& node) const {
    return *node.meta_.get(COLOR) == RED;
  }

  bool isNodeBlack(const BinaryTreeNode<T>& node) const {
    return BLACK == *node.meta_.get(COLOR);
  }

  bool isNodeColored(const BinaryTreeNode<T>& node) const {
    return isNodeRed(node) || isNodeBlack(node);
  }

 private:
  void balance(std::shared_ptr<BinaryTreeNode<T>> node) {
    // If it is a root node then nothing to balance here.
    if (node == this->root_) {
      return;
    }

    // If the parent is black then done. Nothing to balance here.
    auto parent = node->parent_.lock();
    if (isNodeBlack(*parent)) {
      return;
    }

    decltype(parent) grandParent = nullptr;
    if (parent) {
      grandParent = parent->parent_.lock();
    }

    auto uncle = node->uncle();
    if (uncle && isNodeRed(*uncle)) {
      // If node has red uncle then we need to do RECOLORING.

      // Recolor parent and uncle to black.
      makeNodeBlack(uncle);
      makeNodeBlack(parent);

      if (grandParent != this->root_) {
        // Recolor grand-parent to red if it is not root.
        makeNodeRed(grandParent);
      } else {
        // If grand-parent is black root don't do anything.
        // Since root already has two black sibling that we've just recolored.
        return;
      }

      // Now do further checking for recolored grand-parent.
      balance(grandParent);
    } else if (!uncle || isNodeBlack(*uncle)) {
      // If node uncle is black or absent then we need to do ROTATIONS.

      if (grandParent) {
        // Grand parent that we will receive after rotations.
        decltype(parent) newGrandParent;

        if (grandParent->left_ == parent) {
          // Left case.
          if (parent->left_ == node) {
            // Left-left case.
            newGrandParent = leftLeftRotation(grandParent);
          } else {
            // Left-right case.
            newGrandParent = leftRightRotation(grandParent);
          }
        } else {
          // Right case.
          if (parent->right_ == node) {
            // Right-right case.
            newGrandParent = rightRightRotation(grandParent);
          } else {
            // Right-left case.
            newGrandParent = rightLeftRotation(grandParent);
          }
        }

        // Set newGrandParent as a root if it doesn't have parent.
        if (newGrandParent && newGrandParent->parent_.lock() == nullptr) {
          this->root_ = std::static_pointer_cast<BinarySearchTreeNode<T>>(
              newGrandParent->shared_from_this());

          // Recolor root into black.
          makeNodeBlack(this->root_);
        }

        // Check if new grand parent don't violate red-black-tree rules.
        balance(newGrandParent);
      }
    }
  }

  std::shared_ptr<BinaryTreeNode<T>> leftLeftRotation(
      std::shared_ptr<BinaryTreeNode<T>> grandParentNode) {
    // Memorize the parent of grand-parent node.
    auto grandGrandParent = grandParentNode->parent_.lock();

    // Check what type of sibling is our grandParentNode is (left or right).
    bool grandParentNodeIsLeft = false;
    if (grandGrandParent) {
      grandParentNodeIsLeft = (grandGrandParent->left_ == grandParentNode);
    }

    // Memorize grandParentNode's left node.
    auto parentNode = grandParentNode->left_;

    // Memorize parent's right node since we're going to transfer it to
    // grand parent's left subtree.
    auto parentRightNode = parentNode->right_;

    // Make grandParentNode to be right child of parentNode.
    parentNode->setRight(grandParentNode);

    // Move child's right subtree to grandParentNode's left subtree.
    grandParentNode->setLeft(parentRightNode);

    // Put parentNode node in place of grandParentNode.
    if (grandGrandParent) {
      if (grandParentNodeIsLeft) {
        grandGrandParent->setLeft(parentNode);
      } else {
        grandGrandParent->setRight(parentNode);
      }
    } else {
      // Make parent node a root
      parentNode->parent_.reset();
    }

    // Swap colors of granParent and parent nodes.
    swapNodeColors(parentNode, grandParentNode);

    // Return new root node.
    return parentNode;
  }

  std::shared_ptr<BinaryTreeNode<T>> leftRightRotation(
      std::shared_ptr<BinaryTreeNode<T>> grandParentNode) {
    // Memorize left and left-right nodes.
    auto parentNode = grandParentNode->left_;
    auto childNode = parentNode->right_;

    // We need to memorize child left node to prevent losing
    // left child subtree. Later it will be re-assigned to
    // parent's right sub-tree.
    auto childLeftNode = childNode->left_;

    // Make parentNode to be a left child of childNode node.
    childNode->setLeft(parentNode);

    // Move child's left subtree to parent's right subtree.
    parentNode->setRight(childLeftNode);

    // Put left-right node in place of left node.
    grandParentNode->setLeft(childNode);

    // Now we're ready to do left-left rotation.
    return leftLeftRotation(grandParentNode);
  }

  std::shared_ptr<BinaryTreeNode<T>> rightRightRotation(
      std::shared_ptr<BinaryTreeNode<T>> grandParentNode) {
    // Memorize the parent of grand-parent node.
    auto grandGrandParent = grandParentNode->parent_.lock();

    // Check what type of sibling is our grandParentNode is (left or right).
    bool grandParentNodeIsLeft = false;
    if (grandGrandParent) {
      grandParentNodeIsLeft = (grandGrandParent->left_ == grandParentNode);
    }

    // Memorize grandParentNode's right node.
    auto parentNode = grandParentNode->right_;

    // Memorize parent's left node since we're going to transfer it to
    // grand parent's right subtree.
    auto parentLeftNode = parentNode->left_;

    // Make grandParentNode to be left child of parentNode.
    parentNode->setLeft(grandParentNode);

    // Transfer all left nodes from parent to right sub-tree of grandparent.
    grandParentNode->setRight(parentLeftNode);

    // Put parentNode node in place of grandParentNode.
    if (grandGrandParent) {
      if (grandParentNodeIsLeft) {
        grandGrandParent->setLeft(parentNode);
      } else {
        grandGrandParent->setRight(parentNode);
      }
    } else {
      // Make parent node a root.
      parentNode->parent_.reset();
    }

    // Swap colors of granParent and parent nodes.
    swapNodeColors(parentNode, grandParentNode);

    // Return new root node.
    return parentNode;
  }

  std::shared_ptr<BinaryTreeNode<T>> rightLeftRotation(
      std::shared_ptr<BinaryTreeNode<T>> grandParentNode) {
    // Memorize right and right-left nodes.
    auto parentNode = grandParentNode->right_;
    auto childNode = parentNode->left_;

    // We need to memorize child right node to prevent losing
    // right child subtree. Later it will be re-assigned to
    // parent's left sub-tree.
    auto childRightNode = childNode->right_;

    // Make parentNode to be a right child of childNode.
    childNode->setRight(parentNode);

    // Move child's right subtree to parent's left subtree.
    parentNode->setLeft(childRightNode);

    // Put childNode node in place of parentNode.
    grandParentNode->setRight(childNode);

    // Now we're ready to do right-right rotation.
    return rightRightRotation(grandParentNode);
  }

  std::shared_ptr<BinaryTreeNode<T>> makeNodeRed(
      std::shared_ptr<BinaryTreeNode<T>> node) {
    node->meta_.set(COLOR, RED);

    return node;
  }

  std::shared_ptr<BinaryTreeNode<T>> makeNodeBlack(
      std::shared_ptr<BinaryTreeNode<T>> node) {
    node->meta_.set(COLOR, BLACK);

    return node;
  }

  void swapNodeColors(std::shared_ptr<BinaryTreeNode<T>> firstNode,
                      std::shared_ptr<BinaryTreeNode<T>> secondNode) {
    auto firstColor = firstNode->meta_.get(COLOR);
    auto secondColor = secondNode->meta_.get(COLOR);

    firstNode->meta_.set(COLOR, *secondColor);
    secondNode->meta_.set(COLOR, *firstColor);
  }

 public:
  class MethodNotImplementedException : public std::exception {};
};
