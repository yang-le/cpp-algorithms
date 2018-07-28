#pragma once

#include "hash_table.hpp"

class TrieNode
{
public:
	TrieNode(char character, bool is_complete_word = false)
		: character_(character), is_complete_word_(is_complete_word) {}

	TrieNode* getChild(char character) {
		return children_.get({ character });
	}

	TrieNode* addChild(char character, bool is_complete_word = false) {
		if (!children_.has({ character })) {
			children_.set({ character }, TrieNode(character, is_complete_word));
		}

		return children_.get({ character });
	}

	bool hasChild(char character) {
		return children_.has({ character });
	}

	std::unordered_set<std::string> suggestChildren() const {
		return children_.getKeys();
	}

	std::string toString() const {
		auto children = suggestChildren();
		auto childrenAsString = std::accumulate(children.begin(), children.end(), std::string(), [](const std::string& a, const std::string& b){
			return a + "," + b;
		});

		childrenAsString = childrenAsString.size() ? std::string(":") + childrenAsString.substr(1) : "";
		auto isCompleteString = is_complete_word_ ? "*" : "";

		return std::string({ character_ }) + isCompleteString + childrenAsString;
	}

public:
	bool operator==(const TrieNode& rhs) const { return rhs.character_ == character_; }
	bool operator<(const TrieNode& rhs) const { return rhs.character_ < character_; }

public:
	char character_;
	bool is_complete_word_;

private:
	HashTable<TrieNode> children_;
};
