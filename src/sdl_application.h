#pragma once

#include "application.h"
#include <SDL.h>
#include <vector>
#include "sorter.h"

class SdlApplication : public Application
{
public:
	SdlApplication();
	~SdlApplication();

	void run() override;

private:
	void init() override;
	void update() override;
	void render() override;
	void handleEvents() override;

private:
	bool keepWindowOpen;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	SDL_Event m_event;

	std::vector<int> m_data;
	Sorter<int> m_sorter;
	float m_timeSinceLastDraw;
};