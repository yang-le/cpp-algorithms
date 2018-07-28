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

#include "queue.hpp"
#include "gtest/gtest.h"

TEST(QueueTest, create_empty) {
  Queue<int> queue;

  EXPECT_EQ(queue.toString(), "");
}

TEST(QueueTest, enqueue_value) {
  Queue<int> queue;

  queue.enqueue(1);
  queue.enqueue(2);

  EXPECT_EQ(queue.toString(), "1,2");
}

TEST(QueueTest, enqueue_dequeue_objects) {
  Queue<std::pair<std::string, std::string>> queue;

  queue.enqueue(std::make_pair("test1", "key1"));
  queue.enqueue(std::make_pair("test2", "key2"));

  std::string result =
      queue.toString([](const std::pair<std::string, std::string>& pair) {
        return pair.second + ":" + pair.first;
      });

  EXPECT_EQ(result, "key1:test1,key2:test2");
  EXPECT_EQ(queue.dequeue().first, "test1");
  EXPECT_EQ(queue.dequeue().first, "test2");
}

TEST(QueueTest, peak) {
  Queue<int> queue;

  EXPECT_EQ(queue.peek(), nullptr);

  queue.enqueue(1);
  queue.enqueue(2);

  EXPECT_EQ(*queue.peek(), 1);
  EXPECT_EQ(*queue.peek(), 1);
}

TEST(QueueTest, is_empty) {
  Queue<int> queue;

  EXPECT_TRUE(queue.isEmpty());

  queue.enqueue(1);

  EXPECT_FALSE(queue.isEmpty());
}

TEST(QueueTest, dequeue) {
  Queue<int> queue;

  queue.enqueue(1);
  queue.enqueue(2);

  EXPECT_EQ(queue.dequeue(), 1);
  EXPECT_EQ(queue.dequeue(), 2);
  // EXPECT_EQ(queue.dequeue(), nullptr);
  EXPECT_TRUE(queue.isEmpty());
}
