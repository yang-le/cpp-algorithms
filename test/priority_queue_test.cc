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

#include "priority_queue.hpp"
#include "gtest/gtest.h"

TEST(PriorityQueueTest, create_empty) {
  PriorityQueue<int> priorityQueue;

  EXPECT_EQ(priorityQueue.peek(), nullptr);
  EXPECT_TRUE(priorityQueue.isEmpty());
}

TEST(PriorityQueueTest, add) {
  PriorityQueue<int> priorityQueue;

  priorityQueue.add(10, 1);
  EXPECT_EQ(*priorityQueue.peek(), 10);

  priorityQueue.add(5, 2);
  EXPECT_EQ(*priorityQueue.peek(), 10);

  priorityQueue.add(100, 0);
  EXPECT_EQ(*priorityQueue.peek(), 100);
}

TEST(PriorityQueueTest, poll) {
  PriorityQueue<int> priorityQueue;

  priorityQueue.add(10, 1);
  priorityQueue.add(5, 2);
  priorityQueue.add(100, 0);
  priorityQueue.add(200, 0);

  EXPECT_EQ(*priorityQueue.poll(), 100);
  EXPECT_EQ(*priorityQueue.poll(), 200);
  EXPECT_EQ(*priorityQueue.poll(), 10);
  EXPECT_EQ(*priorityQueue.poll(), 5);
}

TEST(PriorityQueueTest, change_priority) {
  PriorityQueue<int> priorityQueue;

  priorityQueue.add(10, 1);
  priorityQueue.add(5, 2);
  priorityQueue.add(100, 0);
  priorityQueue.add(200, 0);

  priorityQueue.changePriority(100, 10);
  priorityQueue.changePriority(10, 20);

  EXPECT_EQ(*priorityQueue.poll(), 200);
  EXPECT_EQ(*priorityQueue.poll(), 5);
  EXPECT_EQ(*priorityQueue.poll(), 100);
  EXPECT_EQ(*priorityQueue.poll(), 10);
}

TEST(PriorityQueueTest, change_priority_of_head) {
  PriorityQueue<int> priorityQueue;

  priorityQueue.add(10, 1);
  priorityQueue.add(5, 2);
  priorityQueue.add(100, 0);
  priorityQueue.add(200, 0);

  priorityQueue.changePriority(200, 10);
  priorityQueue.changePriority(10, 20);

  EXPECT_EQ(*priorityQueue.poll(), 100);
  EXPECT_EQ(*priorityQueue.poll(), 5);
  EXPECT_EQ(*priorityQueue.poll(), 200);
  EXPECT_EQ(*priorityQueue.poll(), 10);
}

TEST(PriorityQueueTest, change_priority_then_add) {
  PriorityQueue<int> priorityQueue;

  priorityQueue.add(10, 1);
  priorityQueue.add(5, 2);
  priorityQueue.add(100, 0);
  priorityQueue.add(200, 0);

  priorityQueue.changePriority(200, 10);
  priorityQueue.changePriority(10, 20);

  priorityQueue.add(15, 15);

  EXPECT_EQ(*priorityQueue.poll(), 100);
  EXPECT_EQ(*priorityQueue.poll(), 5);
  EXPECT_EQ(*priorityQueue.poll(), 200);
  EXPECT_EQ(*priorityQueue.poll(), 15);
  EXPECT_EQ(*priorityQueue.poll(), 10);
}

TEST(PriorityQueueTest, search_by_value) {
  PriorityQueue<int> priorityQueue;

  priorityQueue.add(10, 1);
  priorityQueue.add(5, 2);
  priorityQueue.add(100, 0);
  priorityQueue.add(200, 0);
  priorityQueue.add(15, 15);

  EXPECT_FALSE(priorityQueue.hasValue(70));
  EXPECT_TRUE(priorityQueue.hasValue(15));
}
