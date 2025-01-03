#pragma once

#include <vector>
#include <iostream>

template <class T>
class Sort {
public:
	virtual ~Sort() = default;
	virtual std::vector<T> sort(std::vector<T>& data) = 0;
	virtual void assignData(const std::vector<T>& data) = 0;
	virtual bool sortStep() = 0;
	virtual const std::vector<T>& getData() const = 0;
	virtual size_t getLastMovedIndex() const = 0;
};