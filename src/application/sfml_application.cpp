// SFMLApplication.cpp
#include "sfml_application.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include <chrono>
#include <thread>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

const float kWindowHeight = 600.f;
const float kWindowWidth = 800.f;
const int kDrawInterval = 10;

SfmlApplication::SfmlApplication() :
	m_window()
{
	m_timeSinceLastDraw = 0.f;
	m_currentSnapshotIndex = 0;
	m_data = { 67, 53, 88, 34, 61, 151, 192, 142, 66, 243,
		27, 223, 194, 223, 38, 242, 48, 21, 237, 77,
		224, 146, 101, 74, 8, 127, 119, 128, 48, 132,
		83, 15, 18, 37, 28, 8, 94, 72, 93, 217,
		56, 130, 85, 159, 202, 45, 110, 175, 59, 210,
		134, 199, 12, 89, 145, 203, 54, 176, 29, 68,
		116, 39, 162, 207, 23, 150, 91, 184, 140, 33,
		157, 121, 69, 98, 205, 84, 3, 156, 222, 115,
		178, 50, 189, 104, 11, 190, 60, 136, 197, 51,
		124, 173, 95, 182, 44, 168, 79, 153, 224, 7,
		167, 134, 146, 63, 212, 30, 108, 191, 75, 139,
		166, 124, 161, 22, 189, 49, 116, 138, 185, 64,
		214, 157, 31, 83, 196, 102, 25, 179, 71, 189,
		117, 143, 55, 126, 190, 87, 205, 20, 99, 154,
		58, 121, 189, 40, 164, 107, 13, 148, 196, 81,
		203, 34, 175, 96, 218, 49, 133, 180, 77, 161,
		5, 112, 190, 36, 207, 89, 130, 144, 61, 198,
		72, 167, 119, 29, 185, 103, 154, 46, 176, 85,
		210, 38, 141, 192, 66, 229, 14, 123, 181, 57,
		200, 82, 155, 47, 169, 109, 19, 178, 93, 140,
		65, 215, 24, 135, 187, 52, 204, 97, 173, 8,
		161, 59, 190, 43, 222, 76, 128, 116, 84, 199,
		35, 150, 209, 62, 176, 109, 17, 194, 90, 138,
		70, 213, 26, 164, 188, 53, 207, 101, 179, 32,
		145, 210, 61, 182, 111, 39, 196, 85, 175, 44,
		223, 68, 152, 114, 89, 205, 21, 133, 199, 58,
		170, 104, 16, 189, 73, 218, 49, 161, 126, 95
	};
	m_barWidth = kWindowWidth / m_data.size();
}

void SfmlApplication::run(std::unique_ptr<SortingAlgorithm> sortAlgorithm)
{
	init();
	m_sortAlgorithm = std::move(sortAlgorithm);
	m_sortAlgorithm->sort(m_data);

	if (m_text) 
	{
		prepareTextStats();
	}

	while (m_window.isOpen())
	{
		handleEvents();
		update();
		render();
	}
}

void SfmlApplication::init()
{
	m_window.create(sf::VideoMode({ static_cast<unsigned int>(kWindowWidth), static_cast<unsigned int>(kWindowHeight) }),
		"Sorting Visualization",
		sf::State::Windowed);
	
	if (!m_font.openFromFile("fonts/Arial.ttf"))
	{
		std::cout << "Error loading font.\n";
		return;
	}
	
	m_text = std::make_optional<sf::Text>(m_font);
}

void SfmlApplication::prepareTextStats()
{
	std::ostringstream oss;
	oss << m_sortAlgorithm->getName() <<
		": Total comparisons: " <<
		m_sortAlgorithm->getTotalComparisonOperations() <<
		", total moves: " <<
		m_sortAlgorithm->getTotalMoveOperations() <<
		" (" <<
		m_sortAlgorithm->getTotalOperations() <<
		" operations in total).";
	std::string text = oss.str();

	m_text->setString(text);
	m_text->setCharacterSize(18);
	m_text->setFillColor(sf::Color::White);
	sf::FloatRect bounds = m_text->getLocalBounds();
	// why can't we have a centered text?
	m_text->setPosition({ kWindowWidth - bounds.size.x - 50.f, 0.f });
}

void SfmlApplication::handleEvents()
{
	while (const std::optional event = m_window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			m_window.close();
		}
	}
}

void SfmlApplication::update()
{
	static bool finalDebugWritten = false;
	float ms = m_deltaClock.restart().asMicroseconds() / 1000.f;
	m_timeSinceLastDraw += ms;
	std::cout << "ms = " << ms << ", m_timeSinceLastDraw = " << m_timeSinceLastDraw << "\n";
	if (m_timeSinceLastDraw >= kDrawInterval)
	{
		const std::vector<std::vector<int>>& snapshots = m_sortAlgorithm->getSnapshots();
		if (m_currentSnapshotIndex < snapshots.size() - 1 && !snapshots.empty())
		{
			const std::vector<int>& currentArr = snapshots[m_currentSnapshotIndex];

			int frequency = 200 + (currentArr[m_sortAlgorithm->getSwaps()[m_currentSnapshotIndex]] * 10);
			if (frequency > 32767) frequency = 32767; // Beep max frequency
			beep(frequency, kDrawInterval);
			m_currentSnapshotIndex++;
		}

		m_timeSinceLastDraw = 0.f;
	}
}

void SfmlApplication::render()
{
	m_window.clear(sf::Color::Black);

	const std::vector<std::vector<int>>& snapshots = m_sortAlgorithm->getSnapshots();
	const std::vector<int>& data = snapshots[m_currentSnapshotIndex];
	size_t nData = data.size();

	if (snapshots.size() > 0) 
	{
		for (size_t i = 0; i < nData; ++i)
		{
			float barHeight = static_cast<float>(data[i] * 2 + 1);
			sf::RectangleShape rectangle(sf::Vector2f(m_barWidth, barHeight));

			if (m_sortAlgorithm->getSwaps()[m_currentSnapshotIndex] == i)
			{
				rectangle.setFillColor(sf::Color::Red);
			}
			else
			{
				rectangle.setFillColor(sf::Color::White);
			}

			rectangle.setPosition({ i * m_barWidth, kWindowHeight - barHeight });
			m_window.draw(rectangle);
		}
	}

	if (m_text)
	{
		m_window.draw(*m_text);
	}

	m_window.display();
}

void SfmlApplication::beep(int frequency, int durationMs)
{
	const int sampleRate = 44100;
	const int amplitude = 28000;
	const int length = (sampleRate * durationMs) / 1000;

	std::vector<std::int16_t> samples(length);
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
		samples[i] = static_cast<std::int16_t>(sampleValue);

		phase += phaseIncrement;
	}

	auto channelMap = std::vector<sf::SoundChannel>{
		sf::SoundChannel::FrontLeft,
		sf::SoundChannel::FrontRight,
	};
	if (!m_soundBuffer.loadFromSamples(samples.data(), samples.size(), channelMap.size(), sampleRate, channelMap))
	{
		std::cout << "[SFML] Failed to load sound buffer.\n";
		return;
	}

	m_sound = std::make_optional<sf::Sound>(m_soundBuffer);
	m_sound->play();
}
