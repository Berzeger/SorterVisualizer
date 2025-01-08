#pragma once

#include <vector>
#include <string>

class SortingAlgorithm
{
public:
	virtual ~SortingAlgorithm() = default;
	virtual std::vector<int> sort(std::vector<int>& data) = 0;
	std::vector<std::vector<int>>& getSnapshots() { return m_snapshots; }
	std::vector<int>& getSwaps() { return m_swaps; }
	int getTotalMoveOperations() const { return m_totalMoveOperations; }
	int getTotalComparisonOperations() const { return m_totalComparisonOperations; }
	int getTotalOperations() const { return m_totalComparisonOperations + m_totalMoveOperations; }
	const std::string& getName() const { return m_name; }

protected:
	// protected in order to prevent creating public instances
	SortingAlgorithm() : m_totalMoveOperations(0), m_totalComparisonOperations(0) { }

protected:
	std::vector<std::vector<int>> m_snapshots;
	std::vector<int> m_swaps;
	std::string m_name;
	int m_totalMoveOperations, m_totalComparisonOperations;
};