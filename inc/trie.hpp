#pragma once

#include "trie_node.hpp"

class Trie {
 public:
  const static char HEAD_CHARACTER = '*';

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
      const std::string& word) {
    auto lastCharacter = getLastCharacterNode(word);

    if (!lastCharacter) {
      return std::unordered_set<std::string>();
    }

    return lastCharacter->suggestChildren();
  }

  bool doesWordExist(const std::string& word) {
    return !!getLastCharacterNode(word);
  }

 private:
  TrieNode* getLastCharacterNode(const std::string& word) {
    auto characters = word.c_str();
    TrieNode* currentNode = &head_;
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
