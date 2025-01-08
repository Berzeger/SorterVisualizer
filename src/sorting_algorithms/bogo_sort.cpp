#include "bogo_sort.h"
#include "../sort_algorithm_registry.h"

std::vector<int> BogoSort::sort(std::vector<int>& data)
{
	int nData = data.size();
	this->m_snapshots.clear();
	this->m_swaps.clear();

	while (!isSorted(data) && m_snapshots.size() < 1000000) 
	{
		shuffle(data);
	}

	return data;
}

bool BogoSort::isSorted(const std::vector<int>& data) const
{
	int size = data.size();
	for (int i = 0; i < size - 1; i++) {
		if (data[i] > data[i + 1]) {
			return false;
		}
	}
	return true;
}

void BogoSort::shuffle(std::vector<int>& data)
{
	int size = data.size();
	int random;
	for (int i = 0; i < size; i++)
	{
		random = (int)((double)rand() / ((double)RAND_MAX + 1) * size);
		std::swap(data[random], data[i]);
	}

	this->m_snapshots.push_back(data);
	this->m_swaps.push_back(0);
}

REGISTER_SORT_ALGORITHM(BogoSort, "Bogo Sort (this is a random-based sort, might never finish, iteration count limited to 1 million!)");
