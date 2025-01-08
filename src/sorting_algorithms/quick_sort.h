#pragma once

#include "../sorting_algorithm.h"

class QuickSort : public SortingAlgorithm
{
public:
	QuickSort(const std::string& name) { m_name = name; }
	std::vector<int> sort(std::vector<int>& data) override;

private:
	void quickSort(std::vector<int>& vec, int low, int high);
	int partition(std::vector<int>& vec, int low, int high);
};
