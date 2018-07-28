#pragma once

#include <memory>
#include <functional>
#include <string>
#include <sstream>

template <typename T>
class LinkedListNode
{
public:
	LinkedListNode(const T& value, std::shared_ptr<LinkedListNode> next = nullptr)
		: value_(value), next_(next) {}

	std::string toString(std::function<std::string(const T&)> callback) const {
		if (callback)
			return callback(value_);
		else
			return "LinkedListNode";
	}

	std::string toString() const {
		std::stringstream ss;
		ss << value_;
		return ss.str();
	}

public:
	T value_;
	std::shared_ptr<LinkedListNode> next_;
};