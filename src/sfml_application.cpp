// SFMLApplication.cpp
#include "sfml_application.h"
#include <iostream>

const float kBarWidth = 20.f;
const float kWindowHeight = 600.f;
const float kWindowWidth = 800.f;
const float kDrawInterval = 0.03f;

SfmlApplication::SfmlApplication() :
	m_window(),
	m_timeSinceLastDraw(0.f),
	m_data{ 67, 53, 88, 34, 61, 151, 192, 142, 66, 243, 27, 223, 194, 223, 38, 242, 48, 21, 237, 77, 224, 146, 101, 74, 8, 127, 119, 128, 48, 132, 83, 15, 18, 37, 28, 8, 94, 72, 93, 217 }
{
	// Initialize sorter with BubbleSort algorithm
	m_sorter.setSortAlgorithm(std::make_unique<BubbleSort<int>>());
	m_sorter.assignData(m_data);
}

void SfmlApplication::run()
{
	init();

	while (m_window->isOpen())
	{
		handleEvents();
		update();
		render();
	}

	// Optionally print sorted data
	m_sorter.print(m_sorter.getData());
}

void SfmlApplication::init()
{
	m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(static_cast<unsigned int>(kWindowWidth), static_cast<unsigned int>(kWindowHeight)), "Sorting Visualization");
}

void SfmlApplication::handleEvents()
{
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window->close();
		}
	}
}

void SfmlApplication::update()
{
	m_timeSinceLastDraw += m_deltaClock.restart().asSeconds();

	if (m_timeSinceLastDraw >= kDrawInterval)
	{
		m_sorter.sortStep();
		m_timeSinceLastDraw = 0.f;
	}
}

void SfmlApplication::render()
{
	m_window->clear(sf::Color::Black);

	const auto& data = m_sorter.getData();
	size_t nData = data.size();
	for (size_t i = 0; i < nData; ++i)
	{
		float barHeight = static_cast<float>(data[i] * 2 + 1);
		sf::RectangleShape rectangle(sf::Vector2f(kBarWidth, barHeight));

		if (m_sorter.getLastMovedIndex() == i)
		{
			rectangle.setFillColor(sf::Color::Red);
		}
		else
		{
			rectangle.setFillColor(sf::Color::White);
		}

		rectangle.setPosition(i * kBarWidth, kWindowHeight - barHeight);
		m_window->draw(rectangle);
	}

	m_window->display();
}
