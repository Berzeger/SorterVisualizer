#pragma once

#include <vector>
#include <iostream>

template <class T>
class Sort
{
public:
	virtual ~Sort() = default;
	virtual std::vector<T> sort(std::vector<T>& data) = 0;
	virtual bool sortStep(T& sortedElem) = 0;
	virtual void assignData(const std::vector<T>& data)
	{
		m_data = data;
		m_lastMovedIndex = -1;
	}
	virtual const std::vector<T>& getData() const { return m_data; }
	virtual size_t getLastMovedIndex() const { return m_lastMovedIndex; }

protected:
	std::vector<T> m_data;
	size_t m_lastMovedIndex;
};