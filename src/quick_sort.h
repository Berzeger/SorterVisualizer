#pragma once

#include "sort.h"

template<class T>
class QuickSort : public Sort<T>
{
public:
	std::vector<T> sort(std::vector<T>& data) override
	{
		m_snapshots.clear();
		m_swaps.clear();

		m_snapshots.push_back(data);
		m_swaps.push_back(0);

		int n = data.size();
		quickSort(data, 0, n - 1);
		return data;
	}

	void quickSort(std::vector<T>& vec, int low, int high)
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

	int partition(std::vector<T>& vec, int low, int high)
	{
		// Selecting last element as the pivot
		T pivot = vec[high];

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
				m_snapshots.push_back(vec);
				m_swaps.push_back(vec[j]);
			}
		}

		// Put pivot to its position
		std::swap(vec[i + 1], vec[high]);
		m_snapshots.push_back(vec);
		m_swaps.push_back(vec[high]);

		// Return the point of partition
		return (i + 1);
	}
};