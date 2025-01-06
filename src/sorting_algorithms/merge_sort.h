#pragma once

#include "../sorting_algorithm.h"
#include <vector>

class MergeSort : public SortingAlgorithm
{
public:
	// The main sort function, called once
	std::vector<int> sort(std::vector<int>& data) override;

private:
	// Recursively split the array, then merge
	void mergeSort(std::vector<int>& arr, int left, int right);

	// Merge [left..mid] and [mid+1..right] subarrays
	void merge(std::vector<int>& arr, int left, int mid, int right);
};
