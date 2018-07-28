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
