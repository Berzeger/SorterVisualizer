#include "quick_sort.h"
#include "../sort_algorithm_registry.h"

std::vector<int> QuickSort::sort(std::vector<int>& data)
{
	this->m_snapshots.clear();
	this->m_swaps.clear();

	this->m_snapshots.push_back(data);
	this->m_swaps.push_back(0);

	int n = data.size();
	quickSort(data, 0, n - 1);
	return data;
}

void QuickSort::quickSort(std::vector<int>& vec, int low, int high)
{
	// Base case: This part will be executed till the starting index low is lesser than the ending index high
	if (low < high)
	{
		// pi is Partitioning Index, arr[p] is now at right place
		int pi = partition(vec, low, high);

		// Separately sort elements before and after the Partition Index pi
		quickSort(vec, low, pi - 1);
		quickSort(vec, pi + 1, high);
	}
}

int QuickSort::partition(std::vector<int>& vec, int low, int high)
{
	// Selecting last element as the pivot
	int pivot = vec[high];

	// Index of element just before the last element
	// It is used for swapping
	int i = (low - 1);

	for (int j = low; j <= high - 1; j++)
	{
		// If current element is smaller than or
		// equal to pivot
		if (vec[j] <= pivot)
		{
			i++;
			std::swap(vec[i], vec[j]);
			this->m_snapshots.push_back(vec);
			this->m_swaps.push_back(j);
		}
	}

	// Put pivot to its position
	std::swap(vec[i + 1], vec[high]);
	this->m_snapshots.push_back(vec);
	this->m_swaps.push_back(high);

	// Return the point of partition
	return (i + 1);
}

REGISTER_SORT_ALGORITHM(QuickSort, "Quick Sort");
