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
#include <string>
#include <vector>
#include "linked_list.hpp"

template <typename T>
class Stack {
 public:
  bool isEmpty() { return !linked_list_.tail_; }

  const T* peek() {
    if (isEmpty()) {
      return nullptr;
    }

    return &linked_list_.tail_->value_;
  }

  void push(const T& value) { linked_list_.append(value); }

  T pop() {
    auto removedTail = linked_list_.deleteTail();
    return removedTail ? removedTail->value_ : T();
  }

  std::vector<T> toArray() {
    std::vector<LinkedListNode<T>> nodes = linked_list_.toArray();
    std::vector<T> result(nodes.size());

    std::transform(nodes.begin(), nodes.end(), result.begin(),
                   [](LinkedListNode<T>& node) { return node.value_; });

    std::reverse(result.begin(), result.end());

    return result;
  }

  std::string toString(std::function<std::string(const T&)> callback) {
    return linked_list_.toString(callback);
  }

  std::string toString() { return linked_list_.toString(); }

 private:
  LinkedList<T> linked_list_;
};
