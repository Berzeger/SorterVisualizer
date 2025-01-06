#pragma once

#include <stack>

template<class T>
class QuickSort : public Sort<T>
{
public:
	void assignData(const std::vector<T>& data) override
	{
		// Call the base class to store the data in m_data
		Sort<T>::assignData(data);

		// Clear any old state
		while (!m_stack.empty())
		{
			m_stack.pop();
		}

		// If there's something to sort, push the initial range
		if (this->m_data.size() > 1)
		{
			QuickRange r;
			r.low = 0;
			r.high = (int)this->m_data.size() - 1;
			r.inPartition = false; // We'll initialize partitioning when we pop it
			m_stack.push(r);
		}

		m_done = (this->m_data.size() <= 1);
	}

	std::vector<T> sort(std::vector<T>& data) override
	{
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

	// quick_sort.h
	bool sortStep(T& sortedElem) override
	{
		if (m_done)
			return false;

		if (m_stack.empty())
		{
			m_done = true;
			return false;
		}

		QuickRange& range = m_stack.top();
		std::cout << "Processing range: [" << range.low << ", " << range.high << "]\n";

		if (!range.inPartition)
		{
			range.inPartition = true;
			range.pivot = this->m_data[range.high];
			range.i = range.low - 1;
			range.j = range.low;
			std::cout << "Pivot selected: " << range.pivot << "\n";
		}

		if (range.j <= range.high - 1)
		{
			std::cout << "Comparing " << this->m_data[range.j] << " with pivot " << range.pivot << "\n";
			if (this->m_data[range.j] <= range.pivot)
			{
				range.i++;
				std::swap(this->m_data[range.i], this->m_data[range.j]);
				sortedElem = this->m_data[range.i];
				this->m_lastMovedIndex = range.i;
				std::cout << "Swapped: " << this->m_data[range.i] << " with " << this->m_data[range.j] << "\n";
			}
			range.j++;
			return true;
		}
		else
		{
			std::swap(this->m_data[range.i + 1], this->m_data[range.high]);
			sortedElem = this->m_data[range.i + 1];
			this->m_lastMovedIndex = range.i + 1;
			std::cout << "Final swap for pivot: " << this->m_data[range.i + 1] << "\n";

			int pivotIndex = range.i + 1;
			m_stack.pop();

			if (pivotIndex - 1 >= range.low)
			{
				QuickRange leftSub;
				leftSub.low = range.low;
				leftSub.high = pivotIndex - 1;
				leftSub.inPartition = false;
				m_stack.push(leftSub);
				std::cout << "Pushed left range: [" << leftSub.low << ", " << leftSub.high << "]\n";
			}

			if (pivotIndex + 1 <= range.high)
			{
				QuickRange rightSub;
				rightSub.low = pivotIndex + 1;
				rightSub.high = range.high;
				rightSub.inPartition = false;
				m_stack.push(rightSub);
				std::cout << "Pushed right range: [" << rightSub.low << ", " << rightSub.high << "]\n";
			}

			if (m_stack.empty())
			{
				m_done = true;
				std::cout << "Sorting completed.\n";
			}

			return true;
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
			}
		}

		// Put pivot to its position
		std::swap(vec[i + 1], vec[high]);

		// Return the point of partition
		return (i + 1);
	}

private:
	struct QuickRange
	{
		int low;
		int high;
		int i;       // partition index
		int j;       // partition index
		T pivot;   // pivot value
		bool inPartition; // are we currently partitioning this range?
	};

	std::stack<QuickRange> m_stack;
	bool m_done = false;
};