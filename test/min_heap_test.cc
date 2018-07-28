#include "gtest/gtest.h"
#include "min_heap.hpp"

TEST(MinHeapTest, create_empty) {
	MinHeap<int> heap;

	EXPECT_EQ(heap.peek(), nullptr);
	EXPECT_TRUE(heap.isEmpty());
}

TEST(MinHeapTest, add) {
	MinHeap<int> minHeap;

	minHeap.add(5);
	EXPECT_FALSE(minHeap.isEmpty());
	EXPECT_EQ(*minHeap.peek(), 5);
	EXPECT_EQ(minHeap.toString(), "5");

	minHeap.add(3);
	EXPECT_EQ(*minHeap.peek(), 3);
	EXPECT_EQ(minHeap.toString(), "3,5");

	minHeap.add(10);
	EXPECT_EQ(*minHeap.peek(), 3);
	EXPECT_EQ(minHeap.toString(), "3,5,10");

	minHeap.add(1);
	EXPECT_EQ(*minHeap.peek(), 1);
	EXPECT_EQ(minHeap.toString(), "1,3,10,5");

	minHeap.add(1);
	EXPECT_EQ(*minHeap.peek(), 1);
	EXPECT_EQ(minHeap.toString(), "1,1,10,5,3");

	EXPECT_EQ(*minHeap.poll(), 1);
	EXPECT_EQ(minHeap.toString(), "1,3,10,5");

	EXPECT_EQ(*minHeap.poll(), 1);
	EXPECT_EQ(minHeap.toString(), "3,5,10");

	EXPECT_EQ(*minHeap.poll(), 3);
	EXPECT_EQ(minHeap.toString(), "5,10");
}

TEST(MinHeapTest, poll) {
	MinHeap<int> minHeap;

	minHeap.add(5);
	minHeap.add(3);
	minHeap.add(10);
	minHeap.add(11);
	minHeap.add(1);

	EXPECT_EQ(minHeap.toString(),"1,3,10,11,5");

	EXPECT_EQ(*minHeap.poll(), 1);
	EXPECT_EQ(minHeap.toString(), "3,5,10,11");

	EXPECT_EQ(*minHeap.poll(), 3);
	EXPECT_EQ(minHeap.toString(), "5,11,10");

	EXPECT_EQ(*minHeap.poll(), 5);
	EXPECT_EQ(minHeap.toString(), "10,11");

	EXPECT_EQ(*minHeap.poll(), 10);
	EXPECT_EQ(minHeap.toString(), "11");

	EXPECT_EQ(*minHeap.poll(), 11);
	EXPECT_EQ(minHeap.toString(), "");

	EXPECT_EQ(minHeap.poll(), nullptr);
	EXPECT_EQ(minHeap.toString(), "");
}

TEST(MinHeapTest, heapify_down_right) {
	MinHeap<int> minHeap;

	minHeap.add(3);
	minHeap.add(12);
	minHeap.add(10);

	EXPECT_EQ(minHeap.toString(),"3,12,10");

	minHeap.add(11);
	EXPECT_EQ(minHeap.toString(),"3,11,10,12");

	EXPECT_EQ(*minHeap.poll(),3);
	EXPECT_EQ(minHeap.toString(),"10,11,12");
}

TEST(MinHeapTest, find) {
	MinHeap<int> minHeap;

	minHeap.add(3);
	minHeap.add(12);
	minHeap.add(10);
	minHeap.add(11);
	minHeap.add(11);

	EXPECT_EQ(minHeap.toString(), "3,11,10,12,11");

	EXPECT_EQ(minHeap.find(5), std::vector<int>());
	EXPECT_EQ(minHeap.find(3), std::vector<int>({ 0 }));
	EXPECT_EQ(minHeap.find(11), std::vector<int>({ 1, 4 }));
}

TEST(MinHeapTest, remove_heapify_down) {
	MinHeap<int> minHeap;

	minHeap.add(3);
	minHeap.add(12);
	minHeap.add(10);
	minHeap.add(11);
	minHeap.add(11);

	EXPECT_EQ(minHeap.toString(), "3,11,10,12,11");

	EXPECT_EQ(minHeap.remove(3)->toString(), "10,11,11,12");
	EXPECT_EQ(*minHeap.remove(3)->peek(), 10);
	EXPECT_EQ(minHeap.remove(11)->toString(), "10,12");
	EXPECT_EQ(*minHeap.remove(3)->peek(), 10);
}

TEST(MinHeapTest, remove_heapify_up) {
	MinHeap<int> minHeap;

	minHeap.add(3);
	minHeap.add(10);
	minHeap.add(5);
	minHeap.add(6);
	minHeap.add(7);
	minHeap.add(4);
	minHeap.add(6);
	minHeap.add(8);
	minHeap.add(2);
	minHeap.add(1);

	EXPECT_EQ(minHeap.toString(), "1,2,4,6,3,5,6,10,8,7");
	EXPECT_EQ(minHeap.remove(8)->toString(), "1,2,4,6,3,5,6,10,7");
	EXPECT_EQ(minHeap.remove(7)->toString(), "1,2,4,6,3,5,6,10");
	EXPECT_EQ(minHeap.remove(1)->toString(), "2,3,4,6,10,5,6");
	EXPECT_EQ(minHeap.remove(2)->toString(), "3,6,4,6,10,5");
	EXPECT_EQ(minHeap.remove(6)->toString(), "3,5,4,10");
	EXPECT_EQ(minHeap.remove(10)->toString(), "3,5,4");
	EXPECT_EQ(minHeap.remove(5)->toString(), "3,4");
	EXPECT_EQ(minHeap.remove(3)->toString(), "4");
	EXPECT_EQ(minHeap.remove(4)->toString(), "");
}

TEST(MinHeapTest, remove_with_custom_comparator) {
	MinHeap<std::string> minHeap;
	minHeap.add("dddd");
	minHeap.add("ccc");
	minHeap.add("bb");
	minHeap.add("a");

	EXPECT_EQ(minHeap.toString(), "a,bb,ccc,dddd");

	minHeap.remove("hey", Comparator<std::string>([](const std::string& a, const std::string& b){
		if (a.length() == b.length())
			return 0;
		return a.length() < b.length() ? -1 : 1;
	}));
	EXPECT_EQ(minHeap.toString(), "a,bb,dddd");
}
