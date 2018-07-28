#include "gtest/gtest.h"
#include "linked_list_node.hpp"
#include <tuple>

TEST(LinkedListNodeTest, create_with_value) {
	LinkedListNode<int> node(1);

	EXPECT_EQ(node.value_, 1);
	EXPECT_EQ(node.next_, nullptr);
}

TEST(LinkedListNodeTest, create_with_object) {
	auto obj = std::make_pair(1, "test");

	LinkedListNode<std::pair<int, std::string>> node(obj);

	EXPECT_EQ(node.value_.first, obj.first);
	EXPECT_EQ(node.value_.second, obj.second);
	EXPECT_EQ(node.next_, nullptr);
}

TEST(LinkedListNodeTest, link) {
	auto node2 = std::make_shared<LinkedListNode<int>>(2);
	auto node1 = std::make_shared<LinkedListNode<int>>(1, node2);

	EXPECT_NE(node1->next_, nullptr);
	EXPECT_EQ(node2->next_, nullptr);
	EXPECT_EQ(node1->value_, 1);
	EXPECT_EQ(node1->next_->value_, 2);
}

TEST(LinkedListNodeTest, to_string) {
	LinkedListNode<int> node(1);

	EXPECT_EQ(node.toString(), "1");

	node.value_ = 2;
	EXPECT_EQ(node.toString(), "2");
}

TEST(LinkedListNodeTest, to_string_with_custom_stringifier) {
	auto obj = std::make_pair(1, "test");

	LinkedListNode<std::pair<int, std::string>> node(obj);

	std::string result = node.toString([](const std::pair<int, std::string>& obj) {
		return std::string("first: ") + std::to_string(obj.first) + std::string(", second: ") + obj.second;
	});

	EXPECT_EQ(result, "first: 1, second: test");
}
