#pragma once

#include "sort.h"

template <class T>
class BubbleSort : public Sort<T>
{
public:
	std::vector<T> sort(std::vector<T>& data) override
	{
		m_i = data.size();

		for (; m_i > 0; --m_i)
		{
			for (m_j = 0; m_j < m_i - 1; ++m_j)
			{
				if (data[m_j] > data[m_j + 1])
				{
					std::swap(m_data[m_j], m_data[m_j + 1]);
				}
			}
		}

		return data;
	}

	void assignData(const std::vector<T>& data) override
	{
		Sort::assignData(data);
		m_i = m_data.size();
		m_j = 0;
		m_done = (m_i <= 1);
	}

	bool sortStep(T& sortedElem)
	{
		if (m_done)
		{
			return false;
		}

		// Perform one bubble sort comparison/swapping step
		if (m_i > 0)
		{
			if (m_j < m_i - 1)
			{
				if (m_data[m_j] > m_data[m_j + 1])
				{
					std::swap(m_data[m_j], m_data[m_j + 1]);

					sortedElem = m_data[m_j + 1]; // The number we just moved upwards
					m_lastMovedIndex = m_j + 1;
				}
				m_j++;
			}
			else
			{
				m_lastMovedIndex = m_j;
				m_i--;
				m_j = 0;
			}
		}

		// Check if we are done
		if (m_i <= 1)
		{
			m_done = true;
			m_lastMovedIndex = -1;
		}

		return true;
	}

private:
	size_t m_i, m_j;
	bool m_done;
};