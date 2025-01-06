template<class T>
class MergeSort : public Sort<T>
{
public:
	void assignData(const std::vector<T>& data) override
	{
		// Store the data in m_data
		Sort<T>::assignData(data);

		// Reset sorting state
		currentSize = 1;
		left = 0;
		mid = 0;
		right = 0;
		m_done = (this->m_data.size() <= 1);

		// Initialize temporary vector
		tempData = this->m_data;

		// Prepare the first merge if necessary
		if (!m_done)
		{
			prepareNextMerge();
		}
	}

	std::vector<T> sort(std::vector<T>& data) override
	{
		int n = data.size();
		mergeSort(data, 0, n - 1);
		return data;
	}

	void mergeSort(std::vector<T>& vec, int left, int right)
	{
		if (left < right)
		{
			int mid = left + (right - left) / 2;

			// Sort first and second halves
			mergeSort(vec, left, mid);
			mergeSort(vec, mid + 1, right);

			// Merge the sorted halves
			merge(vec, left, mid, right);
		}
	}

	bool sortStep(T& sortedElem) override
	{
		if (m_done)
			return false;

		// If no current merge is in progress, prepare the next one
		if (!currentMerge.inProgress)
		{
			if (!prepareNextMerge())
			{
				m_done = true;
				return false;
			}
		}

		// Perform one step of the current merge
		if (currentMerge.leftIndex <= currentMerge.mid && currentMerge.rightIndex <= currentMerge.right)
		{
			if (this->m_data[currentMerge.leftIndex] <= this->m_data[currentMerge.rightIndex])
			{
				tempData[currentMerge.index] = this->m_data[currentMerge.leftIndex];
				sortedElem = this->m_data[currentMerge.leftIndex];
				currentMerge.leftIndex++;
			}
			else
			{
				tempData[currentMerge.index] = this->m_data[currentMerge.rightIndex];
				sortedElem = this->m_data[currentMerge.rightIndex];
				currentMerge.rightIndex++;
			}
			currentMerge.index++;
			return true;
		}
		else if (currentMerge.leftIndex <= currentMerge.mid)
		{
			tempData[currentMerge.index] = this->m_data[currentMerge.leftIndex];
			sortedElem = this->m_data[currentMerge.leftIndex];
			currentMerge.leftIndex++;
			currentMerge.index++;
			return true;
		}
		else if (currentMerge.rightIndex <= currentMerge.right)
		{
			tempData[currentMerge.index] = this->m_data[currentMerge.rightIndex];
			sortedElem = this->m_data[currentMerge.rightIndex];
			currentMerge.rightIndex++;
			currentMerge.index++;
			return true;
		}
		else
		{
			// Merge completed for current range, copy back to original array
			for (int i = currentMerge.left; i <= currentMerge.right; i++)
			{
				this->m_data[i] = tempData[i];
			}

			// Merge completed, prepare for the next merge
			currentMerge.inProgress = false;
			if (!prepareNextMerge())
			{
				m_done = true;
			}

			return true;
		}
	}

private:
	struct MergeRange
	{
		int left;
		int mid;
		int right;
		int leftIndex;
		int rightIndex;
		int index;
		bool inProgress;

		MergeRange() : left(0), mid(0), right(0), leftIndex(0), rightIndex(0), index(0), inProgress(false) {}
		MergeRange(int l, int m, int r)
			: left(l), mid(m), right(r), leftIndex(l), rightIndex(m + 1), index(l), inProgress(true)
		{
		}
	};

	bool prepareNextMerge()
	{
		if (left >= this->m_data.size())
			return false;

		mid = std::min(left + currentSize - 1, (int)this->m_data.size() - 1);
		right = std::min(left + 2 * currentSize - 1, (int)this->m_data.size() - 1);

		if (mid < right)
		{
			currentMerge = MergeRange(left, mid, right);
			left += 2 * currentSize;
			return true;
		}
		else
		{
			// No more pairs to merge in this pass, increase the size
			currentSize *= 2;
			left = 0;

			// Check if the entire array has been processed
			if (currentSize >= this->m_data.size())
			{
				// Final pass completed
				return false;
			}

			// Prepare for the next pass
			mid = std::min(left + currentSize - 1, (int)this->m_data.size() - 1);
			right = std::min(left + 2 * currentSize - 1, (int)this->m_data.size() - 1);

			if (mid < right)
			{
				currentMerge = MergeRange(left, mid, right);
				left += 2 * currentSize;
				return true;
			}
			else
			{
				// Only one subarray left, nothing to merge in this pass
				currentSize *= 2;
				left = 0;
				return prepareNextMerge();
			}
		}
	}

	std::vector<T> tempData;
	int currentSize = 1;
	int left = 0;
	int mid = 0;
	int right = 0;
	MergeRange currentMerge;
	bool m_done = false;

	// Full merge sort implementation for the `sort` method
	void merge(std::vector<T>& vec, int l, int m, int r)
	{
		int n1 = m - l + 1;
		int n2 = r - m;

		// Create temp arrays
		std::vector<T> L(n1);
		std::vector<T> R(n2);

		// Copy data to temp arrays
		for (int i = 0; i < n1; i++)
			L[i] = vec[l + i];
		for (int j = 0; j < n2; j++)
			R[j] = vec[m + 1 + j];

		// Merge the temp arrays back into vec[l..r]
		int i = 0; // Initial index of first subarray
		int j = 0; // Initial index of second subarray
		int k = l; // Initial index of merged subarray

		while (i < n1 && j < n2)
		{
			if (L[i] <= R[j])
			{
				vec[k] = L[i];
				i++;
			}
			else
			{
				vec[k] = R[j];
				j++;
			}
			k++;
		}

		// Copy the remaining elements of L[], if there are any
		while (i < n1)
		{
			vec[k] = L[i];
			i++;
			k++;
		}

		// Copy the remaining elements of R[], if there are any
		while (j < n2)
		{
			vec[k] = R[j];
			j++;
			k++;
		}
	}
};