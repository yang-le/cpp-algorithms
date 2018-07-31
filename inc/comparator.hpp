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
#include <functional>

template <typename T>
class Comparator {
 public:
  using compare_func_t = std::function<int(const T& a, const T& b)>;

 public:
  explicit Comparator(std::nullptr_t)
      : is_default_(true), comparator_(defaultCompare) {}

  explicit Comparator(compare_func_t compare = nullptr)
      : is_default_(!compare),
        comparator_(is_default_ ? defaultCompare : compare) {}

  bool equal(const T& a, const T& b) const { return comparator_(a, b) == 0; }

  bool lessThan(const T& a, const T& b) const { return comparator_(a, b) < 0; }

  bool greaterThan(const T& a, const T& b) const {
    return comparator_(a, b) > 0;
  }

  bool lessThanOrEqual(const T& a, const T& b) const {
    return lessThan(a, b) || equal(a, b);
  }

  bool greaterThanOrEqual(const T& a, const T& b) const {
    return greaterThan(a, b) || equal(a, b);
  }

  void reverse() {
    auto compareOriginal = comparator_;
    comparator_ = [=](const T& a, const T& b) { return compareOriginal(b, a); };
  }

 public:
  explicit operator bool() const { return !is_default_; }

 private:
  static int defaultCompare(const T& a, const T& b) {
    if (a == b) return 0;

    return a < b ? -1 : 1;
  }

 private:
  bool is_default_;
  compare_func_t comparator_;
};
