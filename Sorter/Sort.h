#pragma once

#include <vector>
#include <iostream>

template <class T>
class Sort {
public:
	virtual ~Sort() = default;
	virtual std::vector<T> sort(std::vector<T>& data) = 0;
};