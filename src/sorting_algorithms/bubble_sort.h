#pragma once

#include "../sorting_algorithm.h"
#include "../sort_algorithm_registry.h"

class BubbleSort : public SortingAlgorithm
{
public:
	std::vector<int> sort(std::vector<int>& data) override
	{
		int nData = data.size();
		this->m_snapshots.clear();
		this->m_swaps.clear();

		for (; nData > 0; --nData)
		{
			for (int j = 0; j < nData - 1; ++j)
			{
				if (data[j] > data[j + 1])
				{
					std::swap(data[j], data[j + 1]);
					this->m_snapshots.push_back(data);
					this->m_swaps.push_back(j + 1);
				}
			}
		}

		return data;
	}
};

REGISTER_SORT_ALGORITHM(BubbleSort, "Bubble Sort");