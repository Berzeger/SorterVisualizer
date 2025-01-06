#pragma once
#include "sort.h"

template<class T>
class InsertionSort : public Sort<T>
{
public:
	std::vector<T> sort(std::vector<T>& data)
	{
		getSnapshots().clear();
		getSwaps().clear();
		int nData = data.size();
		int i = 1;
		while (i < nData)
		{
			int j = i;
			while (j > 0 && data[j - 1] > data[j])
			{
				std::swap(data[j], data[j - 1]);
				getSnapshots().push_back(data);
				getSwaps().push_back(data[j - 1]);
				j--;
			}
			i++;
		}

		return data;
	}
};