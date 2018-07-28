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
#include <string>
#include <unordered_set>
#include <utility>
#include "linked_list.hpp"

template <typename T, std::size_t N = 32>
class HashTable {
 public:
  int hash(std::string key) {
    auto hash = std::accumulate(key.begin(), key.end(), 0);

    // Reduce hash number so it would fit hash table size.
    return hash % buckets_.size();
  }

  void set(std::string key, const T& value) {
    auto& bucketLinkedList = buckets_[hash(key)];
    auto node =
        bucketLinkedList.find([&](const std::pair<std::string, T>& elem) {
          return elem.first == key;
        });

    if (!node) {
      // Insert new node.
      bucketLinkedList.append(std::make_pair(key, value));
    } else {
      // Update value of existing node.
      node->value_.second = value;
    }
  }

  std::shared_ptr<LinkedListNode<std::pair<std::string, T>>> remove(
      std::string key) {
    auto& bucketLinkedList = buckets_[hash(key)];
    auto node =
        bucketLinkedList.find([&](const std::pair<std::string, T>& elem) {
          return elem.first == key;
        });

    if (node) {
      return bucketLinkedList.remove(node->value_);
    }

    return nullptr;
  }

  T* get(std::string key) {
    auto& bucketLinkedList = buckets_[hash(key)];
    auto node =
        bucketLinkedList.find([&](const std::pair<std::string, T>& elem) {
          return elem.first == key;
        });

    return node ? &node->value_.second : nullptr;
  }

  bool has(std::string key) { return get(key) != nullptr; }

  std::unordered_set<std::string> getKeys() const {
    std::unordered_set<std::string> keys;

    for (auto bucket : buckets_) {
      for (auto node = bucket.head_; node; node = node->next_) {
        keys.insert(node->value_.first);
      }
    }

    return keys;
  }

 public:
  std::array<LinkedList<std::pair<std::string, T>>, N> buckets_;
};
