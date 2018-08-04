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
#include "binary_search_tree_node.hpp"

template <typename T>
class BinarySearchTree {
 public:
  explicit BinarySearchTree(typename Comparator<T>::compare_func_t
                                nodeValueCompareFunction = nullptr) {
    root_ = std::make_shared<BinarySearchTreeNode<T>>(nodeValueCompareFunction);
  }

  BinarySearchTreeNode<T>& insert(const T& value) {
    return root_->insert(value);
  }

  bool contains(const T& value) const { return root_->contains(value); }

  bool remove(const T& value) { return root_->remove(value); }

  std::string toString() const { return root_->toString(); }

 public:
  std::shared_ptr<BinarySearchTreeNode<T>> root_;
};
