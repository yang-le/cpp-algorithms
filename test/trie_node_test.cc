#include "gtest/gtest.h"
#include "trie_node.hpp"

TEST(TrieNodeTest, create) {
	TrieNode trieNode('c', true);

	EXPECT_EQ(trieNode.character_, 'c');
	EXPECT_TRUE(trieNode.is_complete_word_);
	EXPECT_EQ(trieNode.toString(), "c*");
}

TEST(TrieNodeTest, add_child) {
	TrieNode trieNode('c');

	trieNode.addChild('a', true);
	trieNode.addChild('o');

	EXPECT_EQ(trieNode.toString(), "c:a,o");
}

TEST(TrieNodeTest, get_child) {
	TrieNode trieNode('c');

	trieNode.addChild('a');
	trieNode.addChild('o');

	EXPECT_EQ(trieNode.getChild('a')->toString(), "a");
	EXPECT_EQ(trieNode.getChild('o')->toString(), "o");
	EXPECT_EQ(trieNode.getChild('b'), nullptr);
}

TEST(TrieNodeTest, has_child) {
	TrieNode trieNode('c');

	trieNode.addChild('a');
	trieNode.addChild('o');

	EXPECT_TRUE(trieNode.hasChild('a'));
	EXPECT_TRUE(trieNode.hasChild('o'));
	EXPECT_FALSE(trieNode.hasChild('b'));
}

TEST(TrieNodeTest, suggest_children) {
	TrieNode trieNode('c');

	trieNode.addChild('a');
	trieNode.addChild('o');

	EXPECT_EQ(trieNode.suggestChildren(), std::unordered_set<std::string>({ "a", "o" }));
}
