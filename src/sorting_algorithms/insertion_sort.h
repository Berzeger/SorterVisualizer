#pragma once
#include "../sorting_algorithm.h"

class InsertionSort : public SortingAlgorithm
{
public:
	std::vector<int> sort(std::vector<int>& data) override;
};
