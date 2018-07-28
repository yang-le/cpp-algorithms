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

  bool equal(const T& a, const T& b) { return comparator_(a, b) == 0; }

  bool lessThan(const T& a, const T& b) { return comparator_(a, b) < 0; }

  bool greaterThan(const T& a, const T& b) { return comparator_(a, b) > 0; }

  bool lessThanOrEqual(const T& a, const T& b) {
    return lessThan(a, b) || equal(a, b);
  }

  bool greaterThanOrEqual(const T& a, const T& b) {
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
