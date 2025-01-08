#pragma once

#include "../sorting_algorithm.h"

class BogoSort : public SortingAlgorithm
{
public:
	std::vector<int> sort(std::vector<int>& data) override;

private:
	bool isSorted(const std::vector<int>& data) const;
	void shuffle(std::vector<int>& data);
};
