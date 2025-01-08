#include "gnome_sort.h"
#include "../sort_algorithm_registry.h"

std::vector<int> GnomeSort::sort(std::vector<int>& data)
{
	int index = 0;
	int n = data.size();

	while (index < n) 
	{
		if (index == 0)
		{
			index++;
		}

		if (data[index] >= data[index - 1])
		{
			index++;
		}
		else
		{
			std::swap(data[index], data[index - 1]);
			m_snapshots.push_back(data);
			m_swaps.push_back(index - 1);
			index--;
		}
	}

	return data;
}


REGISTER_SORT_ALGORITHM(GnomeSort, "Gnome Sort");