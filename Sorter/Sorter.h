#pragma once

#include "Sort.h"

template <class T>
class Sorter {
public:
	void setSortAlgorithm(std::unique_ptr<Sort<T>> sortAlgorithm) {
		m_sortAlgorithm = std::move(sortAlgorithm);
	}

	std::vector<T> sort(std::vector<T>& data) const {
		return m_sortAlgorithm->sort(data);
	}

	void print(const std::vector<T>& data) const {
		for (T elem : data) {
			std::cout << elem << " ";
		}
		std::cout << std::endl;
	}

private:
	std::unique_ptr<Sort<T>> m_sortAlgorithm;
};
