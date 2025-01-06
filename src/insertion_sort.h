#pragma once

template<class T>
class InsertionSort : public Sort<T>
{
public:
	InsertionSort() :
		m_i(1),
		m_j(1),
		m_done(false)
	{
	}

	std::vector<T> sort(std::vector<T>& data)
	{
		int nData = data.size();
		int i = 1;
		while (i < nData)
		{
			int j = i;
			while (j > 0 && data[j - 1] > data[j])
			{
				std::swap(data[j], data[j - 1]);
				j--;
			}
			i++;
		}

		return data;
	}

	bool sortStep(T& sortedElem)
	{
		if (m_i < m_data.size())
		{
			if (m_j > 0 && m_data[m_j - 1] > m_data[m_j])
			{
				std::swap(m_data[m_j], m_data[m_j - 1]);
				sortedElem = m_data[m_j];
				m_lastMovedIndex = m_j;
				m_j--;
				return true;
			}
			m_i++;
			m_j = m_i;
		}

		m_lastMovedIndex = -1;
		return false;
	}

private:
	size_t m_i, m_j;
	bool m_done;
};