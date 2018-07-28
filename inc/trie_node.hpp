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

#include <string>
#include <unordered_set>
#include "hash_table.hpp"

class TrieNode {
 public:
  explicit TrieNode(char character, bool is_complete_word = false)
      : character_(character), is_complete_word_(is_complete_word) {}

  TrieNode* getChild(char character) { return children_.get({character}); }

  TrieNode* addChild(char character, bool is_complete_word = false) {
    if (!children_.has({character})) {
      children_.set({character}, TrieNode(character, is_complete_word));
    }

    return children_.get({character});
  }

  bool hasChild(char character) { return children_.has({character}); }

  std::unordered_set<std::string> suggestChildren() const {
    return children_.getKeys();
  }

  std::string toString() const {
    auto children = suggestChildren();
    auto childrenAsString = std::accumulate(
        children.begin(), children.end(), std::string(),
        [](const std::string& a, const std::string& b) { return a + "," + b; });

    childrenAsString = childrenAsString.size()
                           ? std::string(":") + childrenAsString.substr(1)
                           : "";
    auto isCompleteString = is_complete_word_ ? "*" : "";

    return std::string({character_}) + isCompleteString + childrenAsString;
  }

 public:
  bool operator==(const TrieNode& rhs) const {
    return rhs.character_ == character_;
  }
  bool operator<(const TrieNode& rhs) const {
    return rhs.character_ < character_;
  }

 public:
  char character_;
  bool is_complete_word_;

 private:
  HashTable<TrieNode> children_;
};
