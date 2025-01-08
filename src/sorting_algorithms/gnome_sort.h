#pragma once

#include "../sorting_algorithm.h"

class GnomeSort : public SortingAlgorithm
{
public:
	GnomeSort(const std::string& name) { m_name = name; }
	std::vector<int> sort(std::vector<int>& data) override;
};
