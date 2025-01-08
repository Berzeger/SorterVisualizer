#pragma once
#include "../sorting_algorithm.h"

class SelectionSort : public SortingAlgorithm
{
public:
	SelectionSort(const std::string& name) { m_name = name; }
	std::vector<int> sort(std::vector<int>& data) override;
};
