#pragma once

#include "application.h"
#include <SDL.h>

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
	SDL_Surface* m_windowSurface;
	SDL_Event m_event;
};