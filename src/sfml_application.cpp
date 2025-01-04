// SFMLApplication.cpp
#include "sfml_application.h"
#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

const float kBarWidth = 20.f;
const float kWindowHeight = 600.f;
const float kWindowWidth = 800.f;
const int kDrawInterval = 10;

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
	float ms = m_deltaClock.restart().asMicroseconds() / 1000.f;
	m_timeSinceLastDraw += ms;
	std::cout << "ms = " << ms << ", m_timeSinceLastDraw = " << m_timeSinceLastDraw << "\n";
	if (m_timeSinceLastDraw >= kDrawInterval)
	{
		int sortedElem;
		if (m_sorter.sortStep(sortedElem))
		{
			int frequency = 200 + (sortedElem * 20);
			if (frequency > 32767) frequency = 32767; // Beep max frequency
			beep(frequency, kDrawInterval);
		}
		
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

void SfmlApplication::beep(int frequency, int durationMs)
{
	const int sampleRate = 44100;
	const int amplitude = 28000;
	const int length = (sampleRate * durationMs) / 1000;

	std::vector<sf::Int16> samples(length);
	double phaseIncrement = (2.f * M_PI * frequency) / sampleRate;
	double phase = 0.f;
	int fadeSamples = sampleRate / 200; // 5 ms fade, prevents crackling
	if (fadeSamples * 2 > length)
	{
		fadeSamples = length / 4;
	}

	for (int i = 0; i < length; ++i)
	{
		double envelope = 1.f;

		// fade in
		if (i < fadeSamples)
		{
			envelope = i / static_cast<double>(fadeSamples);
		}
		// fade out
		else if (i > length - fadeSamples)
		{
			envelope = (length - i) / static_cast<double>(fadeSamples);
		}

		double sampleValue = envelope * amplitude * std::sin(phase);
		samples[i] = static_cast<sf::Int16>(sampleValue);

		phase += phaseIncrement;
	}

	if (!m_soundBuffer.loadFromSamples(samples.data(), samples.size(), 1, sampleRate))
	{
		std::cout << "[SFML] Failed to load sound buffer.\n";
		return;
	}

	m_sound.setBuffer(m_soundBuffer);
	m_sound.play();
}
