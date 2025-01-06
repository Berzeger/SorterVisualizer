#pragma once

#include "sort.h"
#include "sort_algorithm_registry.h"
#include <vector>

class MergeSort : public Sort
{
public:
	// The main sort function, called once
	std::vector<int> sort(std::vector<int>& data) override
	{
		this->m_snapshots.clear();
		this->m_swaps.clear();

		mergeSort(data, 0, static_cast<int>(data.size()) - 1);

		return data;
	}

private:
	// Recursively split the array, then merge
	void mergeSort(std::vector<int>& arr, int left, int right)
	{
		if (left < right)
		{
			int mid = (left + right) / 2;
			mergeSort(arr, left, mid);
			mergeSort(arr, mid + 1, right);
			merge(arr, left, mid, right);
		}
	}

	// Merge [left..mid] and [mid+1..right] subarrays
	void merge(std::vector<int>& arr, int left, int mid, int right)
	{
		int n1 = mid - left + 1;
		int n2 = right - mid;

		// Temp vectors for left and right subarray
		std::vector<int> L(n1);
		std::vector<int> R(n2);

		// Copy data to temp arrays
		for (int i = 0; i < n1; i++)
		{
			L[i] = arr[left + i];
		}

		for (int j = 0; j < n2; j++)
		{
			R[j] = arr[mid + 1 + j];
		}

		// Merge them back into arr
		int i = 0;     // index for L
		int j = 0;     // index for R
		int k = left;  // index for main arr

		while (i < n1 && j < n2)
		{
			if (L[i] <= R[j])
			{
				arr[k] = L[i];
				i++;
			}
			else
			{
				arr[k] = R[j];
				j++;
			}

			this->m_swaps.push_back(k);
			this->m_snapshots.push_back(arr);

			k++;
		}

		// Copy remaining elements of L[] if any
		while (i < n1)
		{
			arr[k] = L[i];
			i++;

			this->m_swaps.push_back(k);
			this->m_snapshots.push_back(arr);

			k++;
		}

		// Copy remaining elements of R[] if any
		while (j < n2)
		{
			arr[k] = R[j];
			j++;

			this->m_swaps.push_back(k);
			this->m_snapshots.push_back(arr);

			k++;
		}
	}
};

REGISTER_SORT_ALGORITHM(MergeSort, "Merge Sort");