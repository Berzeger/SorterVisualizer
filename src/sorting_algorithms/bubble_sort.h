#pragma once

#include "../sorting_algorithm.h"

class BubbleSort : public SortingAlgorithm
{
public:
	BubbleSort(const std::string& name) { m_name = name; }
	std::vector<int> sort(std::vector<int>& data) override;
};
