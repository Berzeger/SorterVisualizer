#include "selection_sort.h"
#include "../sort_algorithm_registry.h"

std::vector<int> SelectionSort::sort(std::vector<int>& data)
{
	this->m_snapshots.clear();
	this->m_swaps.clear();
	int nData = data.size();
	
	for (int i = 0; i < nData - 1; ++i)
	{
		int minIdx = i;

		for (int j = i + 1; j < nData; ++j)
		{
			m_totalComparisonOperations++;
			if (data[j] < data[minIdx])
			{
				minIdx = j;
			}
		}

		m_totalMoveOperations++;
		std::swap(data[i], data[minIdx]);
		this->m_snapshots.push_back(data);
		this->m_swaps.push_back(i);
	}

	return data;
}

REGISTER_SORT_ALGORITHM(SelectionSort, "Selection Sort");
