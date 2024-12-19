#include "Application.h"
#include <iostream>

Application::Application() : m_window(), m_windowEvent(), m_windowSurface()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Failed to initialize SDL" << std::endl;
		return;
	}

	m_window = SDL_CreateWindow("My SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);

	if (!m_window) {
		std::cout << "Failed to create window" << std::endl;
		return;
	}

	m_windowSurface = SDL_GetWindowSurface(m_window);

	if (!m_windowSurface) {
		std::cout << "Failed to get the surface from the window" << std::endl;
		return;
	}
}

Application::~Application() {
	SDL_FreeSurface(m_windowSurface);
	SDL_DestroyWindow(m_window);
}

void Application::update() {
	bool keepWindowOpen = true;
	while (keepWindowOpen)
	{
		SDL_Event e;
		while (SDL_PollEvent(&e) > 0)
		{
			switch (e.type) {
			case SDL_QUIT:
				keepWindowOpen = false;
				break;
			}
		}

		draw();
	}
}

void Application::draw() {
	SDL_UpdateWindowSurface(m_window);
}