#include "trie.hpp"
#include "gtest/gtest.h"

TEST(TrieTest, create) {
  Trie trie;

  EXPECT_EQ(trie.head_.toString(), "*");
}

TEST(TrieTest, add) {
  Trie trie;

  trie.addWord("cat");

  EXPECT_EQ(trie.head_.toString(), "*:c");
  EXPECT_EQ(trie.head_.getChild('c')->toString(), "c:a");

  trie.addWord("car");
  EXPECT_EQ(trie.head_.toString(), "*:c");
  EXPECT_EQ(trie.head_.getChild('c')->toString(), "c:a");
  EXPECT_EQ(trie.head_.getChild('c')->getChild('a')->toString(), "a:t,r");
  EXPECT_EQ(trie.head_.getChild('c')->getChild('a')->getChild('t')->toString(),
            "t*");
}

TEST(TrieTest, suggest) {
  Trie trie;

  trie.addWord("cat");
  trie.addWord("cats");
  trie.addWord("car");
  trie.addWord("caption");

  EXPECT_EQ(trie.suggestNextCharacters("ca"),
            std::unordered_set<std::string>({"t", "r", "p"}));
  EXPECT_EQ(trie.suggestNextCharacters("cat"),
            std::unordered_set<std::string>({"s"}));
  EXPECT_EQ(trie.suggestNextCharacters("cab"),
            std::unordered_set<std::string>());
}

TEST(TrieTest, exist) {
  Trie trie;

  trie.addWord("cat");
  trie.addWord("cats");
  trie.addWord("car");
  trie.addWord("caption");

  EXPECT_TRUE(trie.doesWordExist("cat"));
  EXPECT_TRUE(trie.doesWordExist("cap"));
  EXPECT_FALSE(trie.doesWordExist("call"));
}
