#pragma once

#include "application.h"
#include <SDL.h>
#include <vector>
#include "../sorting_algorithm.h"

class SdlApplication : public Application
{
public:
	SdlApplication();
	~SdlApplication();

	void run(std::unique_ptr<SortingAlgorithm> sortAlgorithm) override;

private:
	void init() override;
	void update() override;
	void render() override;
	void handleEvents() override;
	void beep(int frequency, int durationMs) override;
	void initAudio();

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Event m_event;
	int m_audioDeviceId;
	bool m_keepWindowOpen;

	float m_timeLastFrame;
	int m_barWidth;
};
