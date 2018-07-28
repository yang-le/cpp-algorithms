#pragma once

#include <algorithm>
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
