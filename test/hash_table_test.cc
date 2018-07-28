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

#include "hash_table.hpp"
#include "gtest/gtest.h"

TEST(HashTableTest, create) {
  HashTable<int> defaultHashTable;
  EXPECT_EQ(defaultHashTable.buckets_.size(), 32);

  HashTable<int, 64> biggerHashTable;
  EXPECT_EQ(biggerHashTable.buckets_.size(), 64);
}

TEST(HashTableTest, hash) {
  HashTable<int> hashTable;

  EXPECT_EQ(hashTable.hash("a"), 1);
  EXPECT_EQ(hashTable.hash("b"), 2);
  EXPECT_EQ(hashTable.hash("abc"), 6);
}

TEST(HashTableTest, collisions) {
  HashTable<std::string, 3> hashTable;

  EXPECT_EQ(hashTable.hash("a"), 1);
  EXPECT_EQ(hashTable.hash("b"), 2);
  EXPECT_EQ(hashTable.hash("c"), 0);
  EXPECT_EQ(hashTable.hash("d"), 1);

  hashTable.set("a", "sky-old");
  hashTable.set("a", "sky");
  hashTable.set("b", "sea");
  hashTable.set("c", "earth");
  hashTable.set("d", "ocean");

  EXPECT_FALSE(hashTable.has("x"));
  EXPECT_TRUE(hashTable.has("b"));
  EXPECT_TRUE(hashTable.has("c"));

  auto stringifier = [](const std::pair<std::string, std::string>& pair) {
    return pair.first + ":" + pair.second;
  };

  EXPECT_EQ(hashTable.buckets_[0].toString(stringifier), "c:earth");
  EXPECT_EQ(hashTable.buckets_[1].toString(stringifier), "a:sky,d:ocean");
  EXPECT_EQ(hashTable.buckets_[2].toString(stringifier), "b:sea");

  EXPECT_EQ(*hashTable.get("a"), "sky");
  EXPECT_EQ(*hashTable.get("d"), "ocean");
  EXPECT_EQ(hashTable.get("x"), nullptr);

  hashTable.remove("a");

  EXPECT_EQ(hashTable.remove("not-existing"), nullptr);

  EXPECT_EQ(hashTable.get("a"), nullptr);
  EXPECT_EQ(*hashTable.get("d"), "ocean");

  hashTable.set("d", "ocean-new");
  EXPECT_EQ(*hashTable.get("d"), "ocean-new");
}

TEST(HashTableTest, add_objects) {
  HashTable<std::pair<std::string, std::string>> hashTable;

  hashTable.set("objectKey", std::make_pair("a", "b"));

  auto object = hashTable.get("objectKey");
  EXPECT_NE(object, nullptr);
  EXPECT_EQ(object->first, "a");
  EXPECT_EQ(object->second, "b");
}

TEST(HashTableTest, keys) {
  HashTable<std::string, 3> hashTable;

  hashTable.set("a", "sky-old");
  hashTable.set("a", "sky");
  hashTable.set("b", "sea");
  hashTable.set("c", "earth");
  hashTable.set("d", "ocean");

  EXPECT_EQ(hashTable.getKeys(),
            std::unordered_set<std::string>({"a", "b", "c", "d"}));
  EXPECT_TRUE(hashTable.has("a"));
  EXPECT_FALSE(hashTable.has("x"));

  hashTable.remove("a");

  EXPECT_FALSE(hashTable.has("a"));
  EXPECT_TRUE(hashTable.has("b"));
  EXPECT_FALSE(hashTable.has("x"));
}
