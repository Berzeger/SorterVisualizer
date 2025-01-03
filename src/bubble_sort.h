#pragma once

#include "sort.h"

#include <windows.h>

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
		m_data = data;
		m_i = m_data.size();
		m_j = 0;
		m_lastMovedIndex = -1;
		m_done = (m_i <= 1);
	}

	bool sortStep()
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

					int value = m_data[m_j + 1]; // The number we just moved upwards
					int frequency = 200 + (value * 20);
					if (frequency < 37) frequency = 37;   // Beep can't go below 37 Hz
					if (frequency > 32767) frequency = 32767; // Beep max frequency

					m_lastMovedIndex = m_j + 1;
					// Beep for 100 ms
					Beep(frequency, 30);
				}
				m_j++;
			}
			else
			{
				m_lastMovedIndex = m_j;

				int value = m_data[m_j]; // The number we just moved upwards
				int frequency = 200 + (value * 20);
				if (frequency < 37) frequency = 37;   // Beep can't go below 37 Hz
				if (frequency > 32767) frequency = 32767; // Beep max frequency

				// Beep for 100 ms
				Beep(frequency, 30);
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

	const std::vector<T>& getData() const override
	{
		return m_data;
	}

	size_t getLastMovedIndex() const override
	{
		return m_lastMovedIndex;
	}

private:
	std::vector<T> m_data;
	size_t m_i, m_j;
	bool m_done;
	size_t m_lastMovedIndex;
};