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

#include <array>
#include <memory>
#include <numeric>
#include <string>
#include <vector>
#include "comparator.hpp"
#include "linked_list_node.hpp"

template <typename T>
class LinkedList {
 public:
  explicit LinkedList(typename Comparator<T>::compare_func_t compare = nullptr)
      : head_(nullptr), tail_(nullptr), comparator_(compare) {}

  LinkedList* prepend(const T& value) {
    // Make new node to be a head.
    auto newNode = std::make_shared<LinkedListNode<T>>(value, head_);
    head_ = newNode;

    // If there is no tail yet let's make new node a tail.
    if (!tail_) {
      tail_ = newNode;
    }

    return this;
  }

  LinkedList* append(const T& value) {
    auto newNode = std::make_shared<LinkedListNode<T>>(value);

    // If there is no head yet let's make new node a head.
    if (!head_) {
      head_ = newNode;
      tail_ = newNode;

      return this;
    }

    // Attach new node to the end of linked list.
    tail_->next_ = newNode;
    tail_ = newNode;

    return this;
  }

  std::shared_ptr<LinkedListNode<T>> remove(const T& value) {
    if (!head_) {
      return nullptr;
    }

    std::shared_ptr<LinkedListNode<T>> deletedNode = nullptr;

    // If the head must be deleted then make 2nd node to be a head.
    while (head_ && comparator_.equal(head_->value_, value)) {
      deletedNode = head_;
      head_ = head_->next_;
    }

    auto currentNode = head_;

    if (currentNode) {
      // If next node must be deleted then make next node to be a next next one.
      while (currentNode->next_) {
        if (comparator_.equal(currentNode->next_->value_, value)) {
          deletedNode = currentNode->next_;
          currentNode->next_ = currentNode->next_->next_;
        } else {
          currentNode = currentNode->next_;
        }
      }
    }

    // Check if tail must be deleted.
    if (comparator_.equal(tail_->value_, value)) {
      tail_ = currentNode;
    }

    return deletedNode;
  }

  std::shared_ptr<LinkedListNode<T>> find(const T& value) const {
    if (!head_) {
      return nullptr;
    }

    auto currentNode = head_;

    while (currentNode) {
      // If value is specified then try to compare by value..
      if (comparator_.equal(currentNode->value_, value)) {
        return currentNode;
      }

      currentNode = currentNode->next_;
    }

    return nullptr;
  }

  std::shared_ptr<LinkedListNode<T>> find(
      std::function<bool(const T&)> callback) const {
    if (!head_) {
      return nullptr;
    }

    auto currentNode = head_;

    while (currentNode) {
      // If callback is specified then try to find node by callback.
      if (callback && callback(currentNode->value_)) {
        return currentNode;
      }

      currentNode = currentNode->next_;
    }

    return nullptr;
  }

  std::shared_ptr<LinkedListNode<T>> deleteTail() {
    if (head_ == tail_) {
      // There is only one node in linked list.
      auto deletedTail = tail_;
      head_ = nullptr;
      tail_.reset();

      return deletedTail;
    }

    // If there are many nodes in linked list...
    auto deletedTail = tail_;

    // Rewind to the last node and delete "next" link for the node before the
    // last one.
    auto currentNode = head_;
    while (currentNode->next_) {
      if (!currentNode->next_->next_) {
        currentNode->next_ = nullptr;
      } else {
        currentNode = currentNode->next_;
      }
    }

    tail_ = currentNode;

    return deletedTail;
  }

  std::shared_ptr<LinkedListNode<T>> deleteHead() {
    if (!head_) {
      return nullptr;
    }

    auto deletedHead = head_;

    if (head_->next_) {
      head_ = head_->next_;
    } else {
      head_ = nullptr;
      tail_.reset();
    }

    return deletedHead;
  }

  std::vector<LinkedListNode<T>> toArray() {
    std::vector<LinkedListNode<T>> nodes;

    auto currentNode = head_;
    while (currentNode) {
      nodes.push_back(*currentNode);
      currentNode = currentNode->next_;
    }

    return nodes;
  }

  std::string toString(std::function<std::string(const T&)> callback) {
    std::vector<LinkedListNode<T>> nodes = toArray();

    std::string ret =
        std::accumulate(nodes.begin(), nodes.end(), std::string(),
                        [&](const std::string& a, const LinkedListNode<T>& b) {
                          return a + std::string(",") + b.toString(callback);
                        });

    return ret.length() ? ret.substr(1) : ret;
  }

  std::string toString() {
    std::vector<LinkedListNode<T>> nodes = toArray();

    std::string ret =
        std::accumulate(nodes.begin(), nodes.end(), std::string(),
                        [](const std::string& a, const LinkedListNode<T>& b) {
                          return a + std::string(",") + b.toString();
                        });

    return ret.length() ? ret.substr(1) : ret;
  }

 public:
  std::shared_ptr<LinkedListNode<T>> head_;
  std::shared_ptr<LinkedListNode<T>> tail_;

 private:
  Comparator<T> comparator_;
};
