#pragma once

#include <vector>
#include <iostream>

template <class T>
class Sort
{
public:
	virtual ~Sort() = default;
	virtual std::vector<T> sort(std::vector<T>& data) = 0;
	virtual std::vector<std::vector<T>>& getSnapshots() { return m_snapshots; }
	virtual std::vector<int>& getSwaps() { return m_swaps; }

protected:
	std::vector<std::vector<T>> m_snapshots;
	std::vector<int> m_swaps;
};