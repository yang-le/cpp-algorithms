#include "gtest/gtest.h"
#include "linked_list.hpp"

TEST(LinkedListTest, create_empty) {
	LinkedList<int> list;

	EXPECT_EQ(list.toString(), "");
}


TEST(LinkedListTest, append) {
	LinkedList<int> list;

	EXPECT_EQ(list.head_, nullptr);
	EXPECT_EQ(list.tail_, nullptr);

	list.append(1);
	list.append(2);

	EXPECT_EQ(list.toString(), "1,2");
}

TEST(LinkedListTest, prepend) {
	LinkedList<int> list;

	list.prepend(2);
	EXPECT_EQ(list.head_->toString(), "2");
	EXPECT_EQ(list.tail_->toString(), "2");

	list.append(1);
	list.prepend(3);

	EXPECT_EQ(list.toString(), "3,2,1");
}

TEST(LinkedListTest, remove_by_value) {
	LinkedList<int> list;

	EXPECT_EQ(list.remove(5), nullptr);

	list.append(1);
	list.append(1);
	list.append(2);
	list.append(3);
	list.append(3);
	list.append(3);
	list.append(4);
	list.append(5);

	EXPECT_EQ(list.head_->toString(), "1");
	EXPECT_EQ(list.tail_->toString(), "5");

	auto deletedNode = list.remove(3);
	EXPECT_EQ(deletedNode->value_, 3);
	EXPECT_EQ(list.toString(), "1,1,2,4,5");

	list.remove(3);
	EXPECT_EQ(list.toString(), "1,1,2,4,5");

	list.remove(1);
	EXPECT_EQ(list.toString(), "2,4,5");

	EXPECT_EQ(list.head_->toString(), "2");
	EXPECT_EQ(list.tail_->toString(), "5");

	list.remove(5);
	EXPECT_EQ(list.toString(), "2,4");

	EXPECT_EQ(list.head_->toString(), "2");
	EXPECT_EQ(list.tail_->toString(), "4");

	list.remove(4);
	EXPECT_EQ(list.toString(), "2");

	EXPECT_EQ(list.head_->toString(), "2");
	EXPECT_EQ(list.tail_->toString(), "2");

	list.remove(2);
	EXPECT_EQ(list.toString(), "");
}

TEST(LinkedListTest, delete_tail) {
	LinkedList<int> list;

	list.append(1);
	list.append(2);
	list.append(3);

	EXPECT_EQ(list.head_->toString(), "1");
	EXPECT_EQ(list.tail_->toString(), "3");

	auto deletedNode1 = list.deleteTail();

	EXPECT_EQ(deletedNode1->value_, 3);
	EXPECT_EQ(list.toString(), "1,2");
	EXPECT_EQ(list.head_->toString(), "1");
	EXPECT_EQ(list.tail_->toString(), "2");

	auto deletedNode2 = list.deleteTail();

	EXPECT_EQ(deletedNode2->value_, 2);
	EXPECT_EQ(list.toString(), "1");
	EXPECT_EQ(list.head_->toString(), "1");
	EXPECT_EQ(list.tail_->toString(), "1");

	auto deletedNode3 = list.deleteTail();

	EXPECT_EQ(deletedNode3->value_, 1);
	EXPECT_EQ(list.toString(), "");
	EXPECT_EQ(list.head_, nullptr);
	EXPECT_EQ(list.tail_, nullptr);
}

TEST(LinkedListTest, delete_head) {
	LinkedList<int> list;

	EXPECT_EQ(list.deleteHead(), nullptr);

	list.append(1);
	list.append(2);

	EXPECT_EQ(list.head_->toString(), "1");
	EXPECT_EQ(list.tail_->toString(), "2");

	auto deletedNode1 = list.deleteHead();

	EXPECT_EQ(deletedNode1->value_, 1);
	EXPECT_EQ(list.toString(), "2");
	EXPECT_EQ(list.head_->toString(), "2");
	EXPECT_EQ(list.tail_->toString(), "2");

	auto deletedNode2 = list.deleteHead();

	EXPECT_EQ(deletedNode2->value_, 2);
	EXPECT_EQ(list.toString(), "");
	EXPECT_EQ(list.head_, nullptr);
	EXPECT_EQ(list.tail_, nullptr);
}

TEST(LinkedListTest, to_string) {
	LinkedList<std::pair<int, std::string>> list;

	auto nodeValue1 = std::make_pair(1, "key1");
	auto nodeValue2 = std::make_pair(2, "key2");

	list.append(nodeValue1)
		->prepend(nodeValue2);

	std::string result = list.toString([](const std::pair<int, std::string>& pair){
		return pair.second + ":" + std::to_string(pair.first);
	});

	EXPECT_EQ(result, "key2:2,key1:1");
}

TEST(LinkedListTest, find_by_value) {
	LinkedList<int> list;

	EXPECT_EQ(list.find(5), nullptr);

	list.append(1);
	EXPECT_NE(list.find(1), nullptr);

	list.append(2)
		->append(3);

	auto node = list.find(2);

	EXPECT_EQ(node->value_, 2);
	EXPECT_EQ(list.find(5), nullptr);
}

TEST(LinkedListTest, find_by_callback) {
	LinkedList<std::pair<int, std::string>> list;

	list.append(std::make_pair(1, "test1"))
		->append(std::make_pair(2, "test2"))
		->append(std::make_pair(3, "test3"));

	auto node = list.find([](const std::pair<int, std::string>& pair){
		return pair.second == "test2";
	});

	EXPECT_NE(node, nullptr);
	EXPECT_EQ(node->value_.first, 2);
	EXPECT_EQ(node->value_.second, "test2");

	auto result = list.find([](const std::pair<int, std::string>& pair){
		return pair.second == "test5";
	});

	EXPECT_EQ(result, nullptr);
}

TEST(LinkedListTest, find_by_custom_compare) {
	LinkedList<std::pair<int, std::string>> list([](const std::pair<int, std::string>& a, const std::pair<int, std::string>& b){
		if (a.second == b.second)
			return 0;

		return a.second < b.second ? -1 : 1;
	});

	list.append(std::make_pair(1, "test1"))
		->append(std::make_pair(2, "test2"))
		->append(std::make_pair(3, "test3"));

	auto node = list.find(std::make_pair(2, std::string("test2")));

	EXPECT_NE(node, nullptr);
	EXPECT_EQ(node->value_.first, 2);
	EXPECT_EQ(node->value_.second, "test2");
	EXPECT_EQ(list.find(std::make_pair(2, std::string("test5"))), nullptr);
}
