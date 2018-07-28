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

#include <map>
#include <vector>
#include "min_heap.hpp"

template <typename T>
class PriorityQueue : public MinHeap<T> {
 public:
  PriorityQueue()
      : MinHeap<T>(std::bind(&PriorityQueue::comparePriority, this,
                             std::placeholders::_1, std::placeholders::_2)) {}

  PriorityQueue *add(const T &item, int priority = 0) {
    priorities_[item] = priority;
    MinHeap<T>::add(item);

    return this;
  }

  PriorityQueue *remove(const T &item, Comparator<T> comparator = nullptr) {
    MinHeap<T>::remove(item, comparator);
    priorities_.erase(item);

    return this;
  }

  PriorityQueue *changePriority(const T &item, int priority) {
    remove(item, Comparator<T>(std::bind(&PriorityQueue::compareValue, this,
                                         std::placeholders::_1,
                                         std::placeholders::_2)));
    add(item, priority);

    return this;
  }

  std::vector<int> findByValue(const T &item) {
    return this->find(item, Comparator<T>(std::bind(
                                &PriorityQueue::compareValue, this,
                                std::placeholders::_1, std::placeholders::_2)));
  }

  bool hasValue(const T &item) { return findByValue(item).size() > 0; }

 private:
  int comparePriority(const T &a, const T &b) {
    if (priorities_[a] == priorities_[b]) return 0;

    return priorities_[a] < priorities_[b] ? -1 : 1;
  }

  int compareValue(const T &a, const T &b) {
    if (a == b) return 0;

    return a < b ? -1 : 1;
  }

 private:
  std::map<T, int> priorities_;
};
