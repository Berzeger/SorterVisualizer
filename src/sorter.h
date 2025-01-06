#pragma once

#include <memory>
#include <iostream>
#include "sorting_algorithm.h"

class Sorter
{
public:
	void setSortAlgorithm(std::unique_ptr<SortingAlgorithm> sortAlgorithm)
	{
		m_sortAlgorithm = std::move(sortAlgorithm);
	}

	std::vector<int> sort(std::vector<int>& data) const
	{
		if (!m_sortAlgorithm)
		{
			return data;
		}

		return m_sortAlgorithm->sort(data);
	}

	void print(const std::vector<int>& data) const
	{
		for (int elem : data)
		{
			std::cout << elem << " ";
		}
		std::cout << std::endl;
	}

	const std::vector<std::vector<int>>& getSnapshots() const
	{
		return m_sortAlgorithm->getSnapshots();
	}

	const std::vector<int>& getSwaps() const 
	{
		return m_sortAlgorithm->getSwaps();
	}

private:
	std::unique_ptr<SortingAlgorithm> m_sortAlgorithm;
};
