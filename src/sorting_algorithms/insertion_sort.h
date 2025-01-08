#pragma once
#include "../sorting_algorithm.h"

class InsertionSort : public SortingAlgorithm
{
public:
	InsertionSort(const std::string& name) { m_name = name; }
	std::vector<int> sort(std::vector<int>& data) override;
};
