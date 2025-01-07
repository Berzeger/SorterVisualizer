#pragma once

#include <memory>
#include "../sorting_algorithm.h"

class Application
{
public:
	virtual ~Application() {};

	virtual void run(std::unique_ptr<SortingAlgorithm> sortAlgorithm) = 0;

protected:
	virtual void init() = 0;
	virtual void handleEvents() = 0;
	virtual void update() = 0;
	virtual void render() = 0;
	virtual void beep(int frequency, int durationMs) = 0;

protected:
	std::unique_ptr<SortingAlgorithm> m_sortAlgorithm;
};