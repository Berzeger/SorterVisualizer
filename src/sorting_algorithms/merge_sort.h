#pragma once

#include "../sorting_algorithm.h"
#include <vector>

class MergeSort : public SortingAlgorithm
{
public:
	MergeSort(const std::string& name) { m_name = name; }
	std::vector<int> sort(std::vector<int>& data) override;

private:
	void mergeSort(std::vector<int>& arr, int left, int right);
	void merge(std::vector<int>& arr, int left, int mid, int right);
};
