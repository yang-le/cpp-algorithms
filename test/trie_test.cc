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
