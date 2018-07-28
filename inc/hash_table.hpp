#pragma once

#include <array>
#include <unordered_set>
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
