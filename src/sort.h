#pragma once

#include <vector>

class Sort
{
public:
	virtual ~Sort() = default;
	virtual std::vector<int> sort(std::vector<int>& data) = 0;
	std::vector<std::vector<int>>& getSnapshots() { return m_snapshots; }
	std::vector<int>& getSwaps() { return m_swaps; }

protected:
	std::vector<std::vector<int>> m_snapshots;
	std::vector<int> m_swaps;
};