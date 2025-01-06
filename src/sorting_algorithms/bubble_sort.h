#pragma once

#include "../sorting_algorithm.h"

class BubbleSort : public SortingAlgorithm
{
public:
	std::vector<int> sort(std::vector<int>& data) override;
};
