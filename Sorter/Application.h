#pragma once

#include <SDL.h>

class Application {
public:
	Application();
	~Application();

	void update();
	void draw();

private:
	SDL_Window* m_window;
	SDL_Surface* m_windowSurface;
	SDL_Event m_windowEvent;
};