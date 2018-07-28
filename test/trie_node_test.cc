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

#include "trie_node.hpp"
#include "gtest/gtest.h"

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

  EXPECT_EQ(trieNode.suggestChildren(),
            std::unordered_set<std::string>({"a", "o"}));
}
