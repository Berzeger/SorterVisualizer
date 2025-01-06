#pragma once

#include "sort.h"

template <class T>
class Sorter
{
public:
	void setSortAlgorithm(std::unique_ptr<Sort<T>> sortAlgorithm)
	{
		m_sortAlgorithm = std::move(sortAlgorithm);
	}

	std::vector<T> sort(std::vector<T>& data) const
	{
		if (!m_sortAlgorithm)
		{
			return data;
		}

		return m_sortAlgorithm->sort(data);
	}

	void print(const std::vector<T>& data) const
	{
		for (T elem : data)
		{
			std::cout << elem << " ";
		}
		std::cout << std::endl;
	}

	const std::vector<std::vector<T>>& getSnapshots() const 
	{
		return m_sortAlgorithm->getSnapshots();
	}

	const std::vector<int>& getSwaps() const 
	{
		return m_sortAlgorithm->getSwaps();
	}

private:
	std::unique_ptr<Sort<T>> m_sortAlgorithm;
};
