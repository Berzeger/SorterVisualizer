// SFMLApplication.h
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "application.h"
#include <vector>
#include <SFML/Audio.hpp>

class SfmlApplication : public Application
{
public:
	SfmlApplication();
	~SfmlApplication() {}

	void run(std::unique_ptr<SortingAlgorithm> sortAlgorithm) override;

private:
	void init() override;
	void update() override;
	void render() override;
	void handleEvents() override;
	void beep(int frequency, int durationMs) override;

private:
	std::unique_ptr<sf::RenderWindow> m_window;
	sf::Clock m_deltaClock;
	float m_timeSinceLastDraw;

	std::vector<int> m_data;
	sf::SoundBuffer m_soundBuffer;
	sf::Sound m_sound;

	float m_barWidth;
	int m_currentSnapshotIndex;
};