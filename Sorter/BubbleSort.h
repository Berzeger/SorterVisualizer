#pragma once

#include "Sort.h"

template <class T>
class BubbleSort : public Sort<T> {
public:
	std::vector<T> sort(std::vector<T>& data) override {
		int nData = data.size();

		for (int i = nData; i >= 0; --i) {
			for (int j = 0; j < i - 1; ++j) {
				if (data[j] > data[j + 1]) {
					T swap = data[j];
					data[j] = data[j + 1];
					data[j + 1] = swap;
				}
			}
		}

		return data;
	}
};