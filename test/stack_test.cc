#include "gtest/gtest.h"
#include "stack.hpp"

TEST(StackTest, create_empty) {
	Stack<int> stack;

	EXPECT_EQ(stack.toString(), "");
}

TEST(StackTest, push_value) {
	Stack<int> stack;

	stack.push(1);
	stack.push(2);

	EXPECT_EQ(stack.toString(), "1,2");
}

TEST(StackTest, push_pop_objects) {
	Stack<std::pair<std::string, std::string>> stack;

	stack.push(std::make_pair("test1", "key1"));
	stack.push(std::make_pair("test2", "key2"));

	std::string result = stack.toString([](const std::pair<std::string, std::string>& pair){
		return pair.second + ":" + pair.first;
	});

	EXPECT_EQ(result, "key1:test1,key2:test2");
	EXPECT_EQ(stack.pop().first, "test2");
	EXPECT_EQ(stack.pop().first, "test1");
}

TEST(StackTest, peak) {
	Stack<int> stack;

	EXPECT_EQ(stack.peek(), nullptr);

	stack.push(1);
	stack.push(2);

	EXPECT_EQ(*stack.peek(), 2);
	EXPECT_EQ(*stack.peek(), 2);
}

TEST(StackTest, is_empty) {
	Stack<int> stack;

	EXPECT_TRUE(stack.isEmpty());

	stack.push(1);

	EXPECT_FALSE(stack.isEmpty());
}

TEST(StackTest, pop) {
	Stack<int> stack;

	stack.push(1);
	stack.push(2);

	EXPECT_EQ(stack.pop(), 2);
	EXPECT_EQ(stack.pop(), 1);
	//EXPECT_EQ(stack.pop(), nullptr);
	EXPECT_TRUE(stack.isEmpty());
}

TEST(StackTest, to_array) {
	Stack<int> stack;

	EXPECT_EQ(stack.peek(), nullptr);

	stack.push(1);
	stack.push(2);
	stack.push(3);

	EXPECT_EQ(stack.toArray(), std::vector<int>({3, 2, 1}));
}
