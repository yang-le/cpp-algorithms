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
#include "trie_node.hpp"

class Trie {
 public:
  static const char HEAD_CHARACTER = '*';

  Trie() : head_(HEAD_CHARACTER) {}

  void addWord(const std::string& word) {
    auto characters = word.c_str();
    TrieNode* currentNode = &head_;
    for (int charIndex = 0; charIndex < word.length(); ++charIndex) {
      auto isComplete = (charIndex == word.length() - 1);
      currentNode = currentNode->addChild(characters[charIndex], isComplete);
    }
  }

  std::unordered_set<std::string> suggestNextCharacters(
      const std::string& word) const {
    auto lastCharacter = getLastCharacterNode(word);

    if (!lastCharacter) {
      return std::unordered_set<std::string>();
    }

    return lastCharacter->suggestChildren();
  }

  bool doesWordExist(const std::string& word) const {
    return !!getLastCharacterNode(word);
  }

 private:
  const TrieNode* getLastCharacterNode(const std::string& word) const {
    auto characters = word.c_str();
    const TrieNode* currentNode = &head_;
    for (int charIndex = 0; charIndex < word.length(); ++charIndex) {
      if (!currentNode->hasChild(characters[charIndex])) {
        return nullptr;
      }
      currentNode = currentNode->getChild(characters[charIndex]);
    }

    return currentNode;
  }

 public:
  TrieNode head_;
};
