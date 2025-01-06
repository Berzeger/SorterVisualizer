#pragma once

#include "sort.h"

template <class T>
class BubbleSort : public Sort<T>
{
public:
	std::vector<T> sort(std::vector<T>& data) override
	{
		int nData = data.size();
		getSnapshots().clear();
		getSwaps().clear();

		for (; nData > 0; --nData)
		{
			for (int j = 0; j < nData - 1; ++j)
			{
				if (data[j] > data[j + 1])
				{
					std::swap(data[j], data[j + 1]);
					getSnapshots().push_back(data);
					getSwaps().push_back(j + 1);
				}
			}
		}

		return data;
	}
};