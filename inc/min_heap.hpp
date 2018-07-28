#pragma once

#include <cmath>
#include <functional>
#include <numeric>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include "comparator.hpp"

template <typename T>
class MinHeap {
 public:
  explicit MinHeap(typename Comparator<T>::compare_func_t compare = nullptr)
      : comparator_(compare) {}

  const T *peek() {
    if (container_.size() == 0) {
      return nullptr;
    }

    return &container_[0];
  }

  const T *poll() {
    if (container_.size() == 0) {
      return nullptr;
    }

    if (container_.size() == 1) {
      const T *back = &container_.back();
      container_.pop_back();
      return back;
    }

    root_ = container_[0];

    // Move the last element from the end to the head.
    container_[0] = container_.back();
    container_.pop_back();
    heapifyDown();

    return &root_;
  }

  MinHeap *add(const T &item) {
    container_.push_back(item);
    heapifyUp();
    return this;
  }

  MinHeap *remove(const T &item, Comparator<T> comparator = Comparator<T>()) {
    // Find number of items to remove.
    auto customComparator = comparator ? comparator : comparator_;
    auto numberOfItemsToRemove = find(item, customComparator).size();

    for (int iteration = 0; iteration < numberOfItemsToRemove; ++iteration) {
      // We need to find item index to remove each time after removal since
      // indices are being change after each heapify process.
      auto indexToRemove = find(item, customComparator).back();

      // If we need to remove last child in the heap then just remove it.
      // There is no need to heapify the heap afterwards.
      if (indexToRemove == (container_.size() - 1)) {
        container_.pop_back();
      } else {
        // Move last element in heap to the vacant (removed) position.
        container_[indexToRemove] = container_.back();
        container_.pop_back();

        // If there is no parent or parent is less then node to delete then
        // heapify down. Otherwise heapify up.
        if (hasLeftChild(indexToRemove) &&
            (!hasParent(indexToRemove) ||
             comparator_.lessThan(parent(indexToRemove),
                                  container_[indexToRemove]))) {
          heapifyDown(indexToRemove);
        } else {
          heapifyUp(indexToRemove);
        }
      }
    }

    return this;
  }

  std::vector<int> find(const T &item,
                        Comparator<T> custom_comparator = Comparator<T>()) {
    std::vector<int> foundItemIndices;
    auto comparator = custom_comparator ? custom_comparator : comparator_;

    for (int itemIndex = 0; itemIndex < container_.size(); ++itemIndex) {
      if (comparator.equal(item, container_[itemIndex])) {
        foundItemIndices.push_back(itemIndex);
      }
    }

    return foundItemIndices;
  }

  bool isEmpty() { return container_.empty(); }

  std::string toString() {
    std::string ret =
        std::accumulate(container_.begin(), container_.end(), std::string(),
                        [](const std::string &a, const T &b) {
                          std::stringstream ss;
                          ss << a << "," << b;
                          return ss.str();
                        });

    return ret.length() ? ret.substr(1) : ret;
  }

 private:
  int getLeftChildIndex(int parentIndex) { return (2 * parentIndex) + 1; }

  int getRightChildIndex(int parentIndex) { return (2 * parentIndex) + 2; }

  int getParentIndex(int childIndex) {
    return static_cast<int>(std::floor((childIndex - 1) / 2.0));
  }

  bool hasParent(int childIndex) { return getParentIndex(childIndex) >= 0; }

  bool hasLeftChild(int parentIndex) {
    return getLeftChildIndex(parentIndex) < container_.size();
  }

  bool hasRightChild(int parentIndex) {
    return getRightChildIndex(parentIndex) < container_.size();
  }

  const T &leftChild(int parentIndex) {
    return container_[getLeftChildIndex(parentIndex)];
  }

  const T &rightChild(int parentIndex) {
    return container_[getRightChildIndex(parentIndex)];
  }

  const T &parent(int childIndex) {
    return container_[getParentIndex(childIndex)];
  }

  void swap(int indexOne, int indexTwo) {
    auto tmp = container_[indexTwo];
    container_[indexTwo] = container_[indexOne];
    container_[indexOne] = tmp;
  }

  void heapifyUp(int customStartIndex = -1) {
    // Take last element (last in array or the bottom left in a tree) in
    // a heap container and lift him up until we find the parent element
    // that is less then the current new one.
    auto currentIndex =
        (customStartIndex < 0) ? container_.size() - 1 : customStartIndex;

    while (
        hasParent(currentIndex) &&
        comparator_.lessThan(container_[currentIndex], parent(currentIndex))) {
      swap(currentIndex, getParentIndex(currentIndex));
      currentIndex = getParentIndex(currentIndex);
    }
  }

  void heapifyDown(int customStartIndex = -1) {
    // Compare the root element to its children and swap root with the smallest
    // of children. Do the same for next children after swap.
    auto currentIndex = (customStartIndex < 0) ? 0 : customStartIndex;
    int nextIndex = 0;

    while (hasLeftChild(currentIndex)) {
      if (hasRightChild(currentIndex) &&
          comparator_.lessThan(rightChild(currentIndex),
                               leftChild(currentIndex))) {
        nextIndex = getRightChildIndex(currentIndex);
      } else {
        nextIndex = getLeftChildIndex(currentIndex);
      }

      if (comparator_.lessThan(container_[currentIndex],
                               container_[nextIndex])) {
        break;
      }

      swap(currentIndex, nextIndex);
      currentIndex = nextIndex;
    }
  }

 private:
  std::vector<T> container_;
  Comparator<T> comparator_;
  T root_;
};
