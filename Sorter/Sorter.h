#pragma once

#include "Sort.h"

template <class T>
class Sorter {
public:
	void setSortAlgorithm(std::unique_ptr<Sort<T>> sortAlgorithm) {
		m_sortAlgorithm = std::move(sortAlgorithm);
	}

	std::vector<T> sort(std::vector<T>& data) const {
		if (m_sortAlgorithm == nullptr) {
			return data;
		}

		return m_sortAlgorithm->sort(data);
	}

	void print(const std::vector<T>& data) const {
		for (T elem : data) {
			std::cout << elem << " ";
		}
		std::cout << std::endl;
	}

	void assignData(const std::vector<T>& data) const {
		if (m_sortAlgorithm == nullptr) {
			return;
		}

		m_sortAlgorithm->assignData(data);
	}

	void sortStep() {
		if (m_sortAlgorithm == nullptr) {
			return;
		}

		m_sortAlgorithm->sortStep();
	}

	const std::vector<T>& getData() const {
		return m_sortAlgorithm->getData();
	}

	int getLastMovedIndex() const {
		if (m_sortAlgorithm == nullptr) {
			return -1;
		}

		return m_sortAlgorithm->getLastMovedIndex();
	}

private:
	std::unique_ptr<Sort<T>> m_sortAlgorithm;
};