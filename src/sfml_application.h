// SFMLApplication.h
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "sorter.h"
#include "bubble_sort.h"
#include "application.h"
#include <vector>

class SfmlApplication : public Application
{
public:
	SfmlApplication();
	~SfmlApplication() {}

	void run() override;

private:
	void init() override;
	void update() override;
	void render() override;
	void handleEvents() override;

private:
	std::unique_ptr<sf::RenderWindow> m_window;
	sf::Clock m_deltaClock;
	float m_timeSinceLastDraw;

	std::vector<int> m_data;
	Sorter<int> m_sorter;
};