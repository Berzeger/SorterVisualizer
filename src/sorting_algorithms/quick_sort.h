#pragma once

#include "../sorting_algorithm.h"

class QuickSort : public SortingAlgorithm
{
public:
	std::vector<int> sort(std::vector<int>& data) override;

	void quickSort(std::vector<int>& vec, int low, int high);

	int partition(std::vector<int>& vec, int low, int high);
};
