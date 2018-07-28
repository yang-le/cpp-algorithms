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
