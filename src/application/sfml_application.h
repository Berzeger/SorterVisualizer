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
	void prepareTextStats();

private:
	sf::RenderWindow m_window;
	sf::Clock m_deltaClock;
	sf::SoundBuffer m_soundBuffer;
	sf::Font m_font;

	std::optional<sf::Sound> m_sound;
	std::optional<sf::Text> m_text;

	float m_barWidth;
};
