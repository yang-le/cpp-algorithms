#pragma once

#include <string>
#include "linked_list.hpp"

template <typename T>
class Queue {
 public:
  bool isEmpty() { return !linked_list_.tail_; }

  const T* peek() {
    if (!linked_list_.head_) {
      return nullptr;
    }

    return &linked_list_.head_->value_;
  }

  void enqueue(const T& value) { linked_list_.append(value); }

  T dequeue() {
    auto removedHead = linked_list_.deleteHead();
    return removedHead ? removedHead->value_ : T();
  }

  std::string toString(std::function<std::string(const T&)> callback) {
    return linked_list_.toString(callback);
  }

  std::string toString() { return linked_list_.toString(); }

 private:
  LinkedList<T> linked_list_;
};
