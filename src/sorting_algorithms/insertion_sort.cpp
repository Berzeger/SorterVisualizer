#include "insertion_sort.h"
#include "../sort_algorithm_registry.h"

std::vector<int> InsertionSort::sort(std::vector<int>& data)
{
	this->m_snapshots.clear();
	this->m_swaps.clear();
	int nData = data.size();
	int i = 1;
	while (i < nData)
	{
		int j = i;
		while (j > 0 && data[j - 1] > data[j])
		{
			std::swap(data[j], data[j - 1]);
			this->m_snapshots.push_back(data);
			this->m_swaps.push_back(j - 1);
			j--;
		}
		i++;
	}

	return data;
}

REGISTER_SORT_ALGORITHM(InsertionSort, "Insertion Sort");
